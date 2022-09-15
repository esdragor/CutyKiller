#include "Hero.h"

#include <cstdlib>

void Hero::TakeAHit(int value)
{
    Character::TakeAHit(value);
    TakePotion(value * 2);
}

void Hero::TakePotion(int value)
{
    if (rand() % 100 + 1 <= 30)
    {
        life += value;
    }
}
