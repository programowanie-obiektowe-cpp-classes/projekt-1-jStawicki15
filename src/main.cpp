#include <iostream>
#include<memory>
#include "Gra.hpp"
//#include "Workers.hpp"

int main()
{   
    double pieniadzePoczatkowe, wartoscWygrana;
    std::unique_ptr<Gra> g;
    std::cout<<"Podaj pieniadze na start\n";
    std::cin>>pieniadzePoczatkowe;
    std::cout<<"Podaj wartosc wygrana\n";
    std::cin>>wartoscWygrana;

    g = std::make_unique<Gra>(pieniadzePoczatkowe,wartoscWygrana);
    
    while(g->getStan())
    {
        g->akcjaGracza();
    }
};
