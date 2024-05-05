#ifndef __ENTITY_H__
#define __ENTITY_H__

#include "GameObject.h"
#include "World.h"

// Entities are GameObjects that are affected by gravity, and collide with the World.
class Entity
    : public GameObject
{
private:
    bool flying;
    bool collides;

protected:
    Point movement;

public:
    Entity();
    virtual ~Entity();

    void setFlying(bool const f) { flying = f; }
    bool isFlying() const { return flying; }

    void setCollisions(bool const c) { collides = c; }
    bool isColliding() const { return collides; }

    virtual bool update(EngineData &data) override;
};

#endif // __ENTITY_H__