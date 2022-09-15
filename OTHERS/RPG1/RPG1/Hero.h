#pragma once
#include "Character.h"

class Hero : public Character
{
public:
    virtual void TakeAHit(int value) override;

protected:
    void TakePotion(int value);
};
