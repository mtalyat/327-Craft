#ifndef __GAMEOBJECT_H__
#define __GAMEOBJECT_H__

#include <vector>
#include "Object.h"
#include "EngineData.h"
#include "Point.h"
#include "Sprite.h"

// GameObjects are the base of all objects that function within the game. They all are provided with an interface to use for common events during gameplay.
class GameObject
    : public Object
{
private:
    bool enabled;
    std::vector<GameObject *> children;
    GameObject *parent;
    Point localPosition;
    Sprite *sprite;

private:
    void addChild(GameObject *go);
    bool removeChild(GameObject *go);

protected:
    // Called when this GameObject receives input.
    virtual bool onInput(EngineData &data) { return false; }
    // Called when the Scene containing this GameObject has been entered.
    virtual void onEnter(EngineData &data) {}
    // Called during the update loop.
    virtual bool onUpdate(EngineData &data) { return false; }
    // Called when the Scene containing this GameObject has been exited.
    virtual void onExit(EngineData &data) {}
    // Called when during the draw call at the end of the update loop.
    virtual void onDraw(EngineData &data) {}

    Sprite *getSprite() const { return sprite; }
    void setSprite(Sprite *const s);

public:
    GameObject();
    GameObject(Sprite *s);
    virtual ~GameObject();

    virtual bool input(EngineData &data);
    virtual void enter(EngineData &data);
    virtual bool update(EngineData &data);
    virtual void exit(EngineData &data);
    virtual void draw(EngineData &data);

    void setLocalPosition(Point const &pos);
    Point &getLocalPosition();
    void setPosition(Point const &pos);
    virtual Point getPosition() const;

    void setParent(GameObject *p, bool const savePosition = true);
    GameObject *getParent() const;

    size_t getChildCount() const { return children.size(); }
    GameObject *getChild(int const index) const { return children.at(index); }

    void setEnabled(bool e) { enabled = e; }
    bool getEnabled() const { return enabled; }
    void enable() { setEnabled(true); }
    void disable() { setEnabled(false); }

    Point size() const;
    bool contains(Point const &pos) const;
    bool containsLocal(Point const &pos) const;
};

#endif // __GAMEOBJECT_H__