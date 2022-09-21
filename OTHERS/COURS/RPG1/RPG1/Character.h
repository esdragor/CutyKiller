#pragma once

class Character
{
public:
    Character();
    ~Character();
    virtual void TakeAHit(int value);
    bool IsDead();
    int atk = 10;
    int GetLife() {return life;}
protected:
    int life = 100;

    
};
