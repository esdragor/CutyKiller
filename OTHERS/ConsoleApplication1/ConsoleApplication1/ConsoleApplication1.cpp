
#include "Pomme.h"
#include "poire.h"

int main(int argc, char* argv[])
{
    // Pomme pomme;
    // pomme.PrintPomme();
    // pomme.poi->PrintPoire();

for (int i = 1; i <= 100; i++)
{
    if (i % 3 == 0)
        std::cout << "Fizz";
    if (i % 5 == 0)
    {
        std::cout << "Buzz"; 
    }
    if (i % 5 != 0 && i % 3 != 0)
    {
        std::cout << i;
    }
    std::cout << std::endl;
}
    return 0;
}
