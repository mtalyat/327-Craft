#include "Entity.h"
Entity::Entity()
    : flying(false), collides(true), movement(Point())
{
}

Entity::~Entity()
{
}

bool Entity::update(EngineData &data)
{
    // do collisions
    Point position = getPosition();
    Point s = size();

    if (s.x > 0 && s.y > 0)
    {
        // gravity
        if (!flying)
        {
            movement += Point::down();
        }

        if (collides)
        {

            World *world = World::getInstance();

            if (world)
            {
                Chunk *c = world->getChunkFromPosition(position);

                if (c->getEnabled() && c->isGenerated())
                {
                    int moveX = 0, moveY = 0;
                    bool good;

                    Point p;
                    Point localPos;

                    // check y
                    if (movement.y > 0)
                    {
                        good = true;
                        for (int y = 1; y <= movement.y; y++)
                        {
                            for (int x = 0; x < s.x; x++)
                            {
                                p = Point(x, y + s.y - 1) + position;
                                c = world->getActiveChunkFromPosition(p);
                                localPos = Chunk::localizePosition(p);
                                if (!c->isGenerated() || data.getBlock(c->getBlockID(localPos.x, localPos.y))->hasCollisions())
                                {
                                    good = false;
                                    break;
                                }
                            }

                            if (good)
                            {
                                moveY = y;
                            }
                        }
                    }
                    else if (movement.y < 0)
                    {
                        good = true;
                        for (int y = -1; y >= movement.y; y--)
                        {
                            for (int x = 0; x < s.x; x++)
                            {
                                p = Point(x, y) + position;
                                c = world->getActiveChunkFromPosition(p);
                                localPos = Chunk::localizePosition(p);
                                if (!c->isGenerated() || data.getBlock(c->getBlockID(localPos.x, localPos.y))->hasCollisions())
                                {
                                    good = false;
                                    break;
                                }
                            }

                            if (good)
                            {
                                moveY = y;
                            }
                        }
                    }

                    // move y
                    position.y += moveY;

                    // check x
                    if (movement.x > 0)
                    {
                        good = true;
                        for (int x = 1; x <= movement.x && good; x++)
                        {
                            for (int y = 0; y < s.y; y++)
                            {
                                p = Point(x + s.x - 1, y) + position;
                                c = world->getActiveChunkFromPosition(p);
                                localPos = Chunk::localizePosition(p);
                                if (!c->isGenerated() || data.getBlock(c->getBlockID(localPos.x, localPos.y))->hasCollisions())
                                {
                                    // if not air, cannot move this way
                                    good = false;
                                    break;
                                }
                            }

                            if (good)
                            {
                                moveX = x;
                            }
                        }
                    }
                    else if (movement.x < 0)
                    {
                        good = true;
                        for (int x = -1; x >= movement.x && good; x--)
                        {
                            for (int y = 0; y < s.y; y++)
                            {
                                p = Point(x, y) + position;
                                c = world->getActiveChunkFromPosition(p);
                                localPos = Chunk::localizePosition(p);
                                if (!c->isGenerated() || data.getBlock(c->getBlockID(localPos.x, localPos.y))->hasCollisions())
                                {
                                    good = false;
                                    break;
                                }
                            }

                            if (good)
                            {
                                moveX = x;
                            }
                        }
                    }

                    // now move
                    position.x += moveX;

                    // update actual position
                    setPosition(position);
                }
            }
        }
        else
        {
            // no collisions, just move
            setPosition(position + movement);
        }
    }

    // then normal update
    return GameObject::update(data);
}
