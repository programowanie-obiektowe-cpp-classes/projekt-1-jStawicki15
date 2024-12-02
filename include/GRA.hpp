#include <iostream>
#include <memory>
#include "Firma.hpp"

class Gra
{
    public:
    Gra(double startPieniadze, double wartoscDocelowa): stanGry_{true}, wartoscDocelowa_{wartoscDocelowa}
    {
        f_ = std::make_unique<Firma>(startPieniadze);
    }

    void akcjaGracza()
    {
        std::string currAkcja;
        printAkcje();
        std::cin>>currAkcja;

        switch (str2int(currAkcja))
        {
        case 1:
            f_->drukujPracownikow();
            break;
        case 2:

            f_->zatrudnij(1);
            break;
        case 3:
            f_->zatrudnij(2);
            break;
        case 4:
            f_->zatrudnij(3);
            break;
        case 5:
            f_->zatrudnij(4);
            break;
        case 6:
            double wartoscKredytu;
            int lata;
            std::cout<<"Podaj ilosc pieniedzy\n";
            std::cin>>wartoscKredytu;
            std::cout<<"Podaj ilosc lat na splacenie\n";
            std::cin>>lata;
            f_->wezKredyt(wartoscKredytu,lata);
            break;
        case 7:
            f_->otrzymajPrzychod();
            f_->zaplacWynagrodzenia();
            f_->splacRaty();

            if(f_->getStanKonta()<0)
            {
                std::cout<<"Firma bankrutuje\n";
                stanGry_ = false;
            }

            if(f_->wartoscFirmy()>=wartoscDocelowa_)
            {
                std::cout<<"WYGRALES!!!\n";
                stanGry_ = false;
            }

            std::cout<<"#################################################\n";
            std::cout<<"RAPORT MIESIECZNY\n";
            f_->getStanFirmy();
            std::cout<<"#################################################\n";
            break;
        default:
        std::cout<<"Podano nieprawidlowa komende!!!\n";
            break;
        }
    }

    
    bool getStan()
    {
        return stanGry_;
    }

    private:
    bool stanGry_;
    double wartoscDocelowa_;
    std::unique_ptr<Firma> f_;
    
    int str2int(std::string s)
    {
        if(s=="lp")
            return 1;
        else if(s=="zinz")
            return 2;
        else if(s=="zmag")
            return 3;
        else if(s=="zmkt")
            return 4;
        else if(s=="zrob")
            return 5;
        else if(s=="kred")
            return 6;
        else if(s=="kt")
            return 7;
        else
            return -1;
    }

    void printAkcje()
    {
        std::cout<<"Dostepne akcje:\n";
        std::cout<<"lp - lista pracownikow\n";
        std::cout<<"zinz - zatrudnij inz\n";
        std::cout<<"zmag - zatrudnij magazyniera\n";
        std::cout<<"zmkt - zatrudnij marketera\n";
        std::cout<<"zrob - zatrudnij robotnika\n";
        std::cout<<"kred - wez kredyt\n";
        std::cout<<"kt - zakoncz ture\n";
    }
};