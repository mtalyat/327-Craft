#include "Player.h"

Player *Player::activePlayer = nullptr;

Player::Player()
    : actionDirection(Point()), action(Action::Break), performAction(false), cheatSpeeding(false)
{
    if (!activePlayer)
    {
        activePlayer = this;
    }

    // set sprite to @ signs for now
    Sprite *sprite = getSprite();
    if (sprite)
        delete sprite;

    sprite = new Sprite(1, 2);
    sprite->setDisplay(0, 0, L'@');
    sprite->setDisplay(0, 1, Pixel::full);
    sprite->setColor(0, 0, 8);
    sprite->setColor(0, 1, 8);

    setSprite(sprite);

    // selector
    selector.setParent(this);
    selector.disable(); // disable for now
}

Player::~Player()
{
    if (this == activePlayer)
    {
        setActive(nullptr);
    }
}

bool Player::onInput(EngineData &data)
{
    Point position = getPosition();

    switch (data.getInput())
    {
    case 'W':
    case 'w': // up
        movement = Point::up();
        break;
    case 'A':
    case 'a': // left
        movement = Point::left();
        // try to move up if block in the way (auto jump)
        if (isColliding() && World::getInstance())
        {
            Point s = size();
            if (World::getInstance()->getBlockIDFromPosition(Point(position.x - 1, position.y + s.y - 1)) != 0)
            {
                // also try to move up
                movement += Point::up() * (isFlying() ? 1 : 2);
            }
        }
        break;
    case 'S':
    case 's': // down
        movement = Point::down();
        break;
    case 'D':
    case 'd': // right
        movement = Point::right();
        // try to move up if block in the way (auto jump)
        if (isColliding() && World::getInstance())
        {
            Point s = size();
            if (World::getInstance()->getBlockIDFromPosition(Point(position.x + s.x, position.y + s.y - 1)) != 0)
            {
                // also try to move up
                movement += Point::up() * (isFlying() ? 1 : 2);
            }
        }
        break;
    case '1': // action down left
        setActionDirection(Point::down() + Point::left());
        break;
    case '2': // action break down
        setActionDirection(Point::down());
        break;
    case '3': // action down right
        setActionDirection(Point::down() + Point::right());
        break;
    case '4': // action left
        setActionDirection(Point::left());
        break;
    case '5': // perform action
        performAction = true;
        break;
    case '6': // action right
        setActionDirection(Point::right());
        break;
    case '7': // action up left
        setActionDirection(Point::up() + Point::left());
        break;
    case '8': // action break up
        setActionDirection(Point::up());
        break;
    case '9': // action up right
        setActionDirection(Point::up() + Point::right());
        break;
    case '0': // reset action
        actionDirection = Point();
        break;
    case '\n': // TEMP: toggle action
        action = action == Action::Break ? Action::Place : Action::Break;
        actionDirection = Point();
        break;
        // CHEATS
    case 'G': // god mode
        if (isColliding())
        {
            setFlying(true);
            setCollisions(false);
        }
        else
        {
            setFlying(false);
            setCollisions(true);
            cheatSpeeding = false;
        }
        break;
    case 'F': // fast mode
        // can only enable if in god mode
        if (!isColliding())
        {
            cheatSpeeding = !cheatSpeeding;
        }
    default:
        movement = Point();
        return false;
    }

    // check for sprinting
    switch (data.getInput())
    {
    case 'A':
    case 'W':
    case 'S':
    case 'D':
        movement *= 2;
        break;
    }

    // check for super speed
    if (cheatSpeeding)
    {
        movement *= 10;
    }

    return true;
}

bool Player::onUpdate(EngineData &data)
{
    Point position = getPosition();

    // perform action
    if (performAction)
    {
        switch (action)
        {
        case Action::Break:
        {
            Point p = getClosestBlock();

            // get the id/block
            unsigned char id = World::getInstance()->getBlockIDFromPosition(p);
            if (id == 0)
            {
                // block itself is nothing
                break;
            }
            BlockData *block = data.getBlock(id);

            if (block->getDropID() != 0 && block->getDropAmount() > 0)
            {
                // drops something

                // add drops to inventory
                Inventory &inv = getInventory();
                inv.add(block->getDropID(), block->getDropAmount());
            }

            // clear block in space
            World::getInstance()->setBlockFromPosition(p, *data.getBlock(0));
        }
        break;
        case Action::Place:
        {
            // selector must be over something
            if (!selector.getEnabled())
            {
                break;
            }

            Point p = selector.getPosition();

            // get the id
            unsigned char id = World::getInstance()->getBlockIDFromPosition(p);

            // if it is a space, place a block
            if (id == 0)
            {
                World::getInstance()->setBlockFromPosition(p, *data.getBlock(5));
            }
        }
        break;
        default: // none
            break;
        }

        performAction = false;
    }
    else
    {
        // preview action?
        switch (action)
        {
        case Action::Break:
        {
            Point p = getClosestBlock();

            if (p == position)
            {
                selector.disable();
                break;
            }

            // set selector to block
            selector.enable();
            selector.setPosition(p);
        }
        break;
        case Action::Place:
        {
            // selector is local
            if (containsLocal(actionDirection))
            {
                selector.disable();
            }
            else
            {
                selector.enable();
                selector.setLocalPosition(actionDirection);
            }
        }
        break;
        default: // none
            break;
        }
    }

    // move camera to reflect player pos
    if (data.getCameraPos())
    {
        *data.getCameraPos() = position - Point(Chunk::WIDTH / 2, Chunk::HEIGHT / 2);
    }

    return true;
}

Point Player::getClosestBlock() const
{
    Point position = getPosition();
    World *world = World::getInstance();

    if (!world)
    {
        // no world?
        return position;
    }

    if (actionDirection.x == 0 && actionDirection.y == 0)
    {
        // no direction
        return position;
    }

    Point s = size();
    Point p;
    unsigned char blockId;

    // reach out in the action direction and check for blocks
    int diagonalAdjustment = 0;

    if (actionDirection.x != 0 && actionDirection.y != 0)
    {
        // if mining in a diagonal direction, increase y size by one
        s.y++;
        diagonalAdjustment--;
    }

    bool yDirectionBottomToTop = actionDirection.y > 0;

    int xOffset = actionDirection.x > 0 ? s.x - 1 : 0;
    int yOffset = actionDirection.y > 0 ? s.y - 1 : 0;

    int x, y;
    for (int i = 0; i <= REACH; i++)
    {
        x = i * actionDirection.x;
        y = i * actionDirection.y;

        // if x not changing, only check y dir
        if (actionDirection.x != 0)
        {
            if (yDirectionBottomToTop)
            {
                for (int j = 0; j < s.y; j++)
                {
                    p = Point(position.x + x + xOffset, position.y + y + j + diagonalAdjustment);
                    blockId = world->getBlockIDFromPosition(p);
                    if (blockId > 0 && blockId != INVALID_BLOCK)
                    {
                        return p;
                    }
                }
            }
            else
            {
                for (int j = s.y - 1; j >= 0; j--)
                {
                    p = Point(position.x + x + xOffset, position.y + y + j + diagonalAdjustment);
                    blockId = world->getBlockIDFromPosition(p);
                    if (blockId > 0 && blockId != INVALID_BLOCK)
                    {
                        return p;
                    }
                }
            }
        }

        // if y not changing, only check x dir
        if (actionDirection.y != 0)
        {
            for (int j = 0; j < s.x; j++)
            {
                p = Point(position.x + x + j, position.y + y + yOffset + diagonalAdjustment);
                blockId = world->getBlockIDFromPosition(p);
                if (blockId > 0 && blockId != INVALID_BLOCK)
                {
                    return p;
                }
            }
        }
    }

    // nothing found
    return position;
}

Point Player::getFurthestEmpty() const
{
    Point position = getPosition();
    return position;
}

void Player::setActionDirection(Point point)
{
    if (action == Action::Break)
    {
        if (actionDirection == point)
        {
            performAction = true;
        }
        else
        {
            actionDirection = point;
        }
    }
    else if (action == Action::Place)
    {
        // clamp inside of reach
        int reach = REACH;
        Point s = size();
        actionDirection = Point(std::min(std::max(actionDirection.x + point.x, -reach), reach + s.x - 1),
                                std::min(std::max(actionDirection.y + point.y, -reach), reach + s.y - 1));
    }
}
