#include "GameObject.h"

GameObject::GameObject()
    : enabled(true), children(), parent(nullptr), localPosition(Point()), sprite(nullptr)
{
}

GameObject::GameObject(Sprite *s)
    : enabled(true), children(), parent(nullptr), localPosition(Point()), sprite(s)
{
}

GameObject::~GameObject()
{
    if (sprite)
    {
        delete sprite;
    }

    if (children.size() > 0)
    {
        for (size_t i = children.size() - 1; i >= 0; i--)
        {
            delete children.at(0);
        }
    }
}

bool GameObject::input(EngineData &data)
{
    bool input = onInput(data);

    // children
    for (GameObject *const &child : children)
    {
        if (child->getEnabled())
        {
            input = child->input(data) || input;
        }
    }

    return input;
}

void GameObject::enter(EngineData &data)
{
    onEnter(data);

    // children
    for (GameObject *const &child : children)
    {
        if (child->getEnabled())
        {
            child->enter(data);
        }
    }
}

bool GameObject::update(EngineData &data)
{
    bool update = onUpdate(data);

    // children
    for (GameObject *const &child : children)
    {
        if (child->getEnabled())
        {
            update = child->update(data) || update;
        }
    }

    return update;
}

void GameObject::exit(EngineData &data)
{
    onExit(data);

    // children
    for (GameObject *const &child : children)
    {
        if (child->getEnabled())
        {
            child->exit(data);
        }
    }
}

void GameObject::draw(EngineData &data)
{
    // draw sprite, if able
    if (sprite)
    {
        Point position = getPosition();

        if (data.getCameraPos())
        {
            // offset by camera
            sprite->print(position.x - data.getCameraPos()->x, position.y - data.getCameraPos()->y, data.console);
        }
        else
        {
            sprite->print(position.x, position.y, data.console);
        }
    }

    // draw self
    onDraw(data);

    // draw children
    for (GameObject *const &child : children)
    {
        if (child->getEnabled())
        {
            child->draw(data);
        }
    }
}

void GameObject::setLocalPosition(Point const &pos)
{
    localPosition = pos;
}

Point &GameObject::getLocalPosition()
{
    return localPosition;
}

void GameObject::setPosition(Point const &pos)
{
    // if a parent, base it off of that
    if (parent)
    {
        localPosition = pos - parent->getPosition();
    }
    else
    {
        localPosition = pos;
    }
}

Point GameObject::getPosition() const
{
    if (parent)
    {
        // if a parent, go off of that
        return parent->getPosition() + localPosition;
    }
    else
    {
        // if no parent, go off of local pos alone
        return localPosition;
    }
}

void GameObject::setParent(GameObject *p, bool const savePosition)
{
    if (parent && parent == p)
    {
        // already on that parent
        return;
    }

    // get position from before
    Point pos = getPosition();

    // remove self from parent children
    if (parent)
    {
        parent->removeChild(this);
    }

    // set new parent
    parent = p;

    // add to new parent's children
    if (parent)
    {
        parent->addChild(this);
    }

    // set position again so it is updated and does not move
    if (savePosition)
    {
        setPosition(pos);
    }
}

GameObject *GameObject::getParent() const
{
    return parent;
}

Point GameObject::size() const
{
    if (sprite)
    {
        // there is a sprite, use its width and height
        return Point(sprite->getWidth(), sprite->getHeight());
    }
    else
    {
        // no sprite, no size at all
        return Point();
    }
}

bool GameObject::contains(Point const &pos) const
{
    Point local = pos - getPosition();

    return containsLocal(local);
}

bool GameObject::containsLocal(Point const &pos) const
{
    Point s = size();

    return pos.x >= 0 && pos.x < s.x && pos.y >= 0 && pos.y < s.y;
}

void GameObject::addChild(GameObject *go)
{
    children.push_back(go);
}

bool GameObject::removeChild(GameObject *go)
{
    for (size_t i = children.size() - 1; i >= 0; i--)
    {
        if (children.at(i) == go)
        {
            children.erase(children.begin() + i);
            return true; // found, and removed
        }
    }

    // not found
    return false;
}

void GameObject::setSprite(Sprite *const s)
{
    if (sprite && sprite != s)
    {
        delete sprite;
    }

    sprite = s;
}
