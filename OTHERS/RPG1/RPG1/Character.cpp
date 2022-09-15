#include "Character.h"

Character::Character()
{
}

Character::~Character()
{
}

void Character::TakeAHit(int value)
{
    life -= value;
}

bool Character::IsDead()
{
    return life <= 0;
}
