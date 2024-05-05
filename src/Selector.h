#ifndef __SELECTOR_H__
#define __SELECTOR_H__

#include "GameObject.h"

// The block selector used when breaking/placing blocks.
class Selector
    : public GameObject
{
private:
    int state;

    static const int STATES = 8;
    static const int STATE_SIZE = 100;

private:
    wchar_t getPixel() const;

protected:
    bool onUpdate(EngineData &data) override;

public:
    Selector();
    ~Selector();
};

#endif // __SELECTOR_H__