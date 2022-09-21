#include <iostream>
#include "Enemy.h"
#include "Hero.h"

int main(int argc, char* argv[])
{
    Enemy enemy;
    Hero heros;
int nbTurn = 0;
    while (!heros.IsDead())
    {
        heros.TakeAHit(enemy.atk);
        std::cout << heros.GetLife() << std::endl;
        nbTurn++;
    }

    std::cout << "You Survived " << nbTurn << " turns :)" << std::endl;
    return 0;
}
