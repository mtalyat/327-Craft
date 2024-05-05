#ifndef __PLAYER_H__
#define __PLAYER_H__

#include "Character.h"
#include "World.h"
#include "Selector.h"

// The Character that the user controls.
class Player
    : public Character
{
private:
    enum Action
    {
        None,
        Break,
        Place
    };

private:
    Point actionDirection;
    Action action;
    bool performAction;

    Selector selector;

    bool cheatSpeeding;

    static Player *activePlayer;

    static const int REACH = 6;

private:
    Point getClosestBlock() const;
    Point getFurthestEmpty() const;

    void setActionDirection(Point point);

protected:
    bool onInput(EngineData &data) override;
    bool onUpdate(EngineData &data) override;

public:
    Player();
    ~Player();

    static void setActive(Player *p) { activePlayer = p; }
    static Player *getActive() { return activePlayer; }
};

#endif // __PLAYER_H__