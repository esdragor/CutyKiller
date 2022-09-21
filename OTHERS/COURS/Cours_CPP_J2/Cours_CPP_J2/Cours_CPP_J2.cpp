
#include <iostream>

class poire
{
public:
    int nb;
    
};

#define printt(x) std::cout << x << std::endl;

void reinteffzsjifj(poire *_po)
{
    _po->nb -= 12;
    printt(_po->nb);
}

int main(int argc, char* argv[])
{
int nbPoire = 123;
int* nb_poire_P = &nbPoire;
int& nb_poire_R = nbPoire;

    poire po;
    po.nb = 34;

    printt(nbPoire);
    printt(nb_poire_P);
    printt(nb_poire_R);
    


    reinteffzsjifj(&po);
    printt(po.nb);
    return 0;
}
