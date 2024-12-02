#include <iostream>
#include <memory>
#include "Workers.hpp"
#include "Kredyt.hpp"

class Firma
{
    public:
    Firma(double kasaPoczatkowa): stanKonta_{kasaPoczatkowa}, nKredytow_{0}, nPracownikow_{4}
    {
        pracownicy_[0] = std::make_unique<Inz>();
        pracownicy_[1] = std::make_unique<Mkt>();
        pracownicy_[2] = std::make_unique<Mag>();
        pracownicy_[3] = std::make_unique<Rob>();

        for(int i=0; i<nMiesWartoscFirmy_;i++)
        {
            historiaPrzychodow_[i] = 0.0;
        }
    }

    void drukujPracownikow()
    {
        std::cout<<"Liczba pracownikow: "<<nPracownikow_<<"\n";
        for(int i=0;i<nPracownikow_;i++)
        {
            pracownicy_[i]->print();
        }
    }

    void wezKredyt(double kwota, int czasSplaty)
    {
        if(kwota>maxKredyt_)
        {
            std::cout<<"Podana Kwota wieksza od maksymalnej\n";
        }
        else if(czasSplaty>maxCzasKredyt_)
        {
            std::cout<<"Podany czas dluzszy od maksymalnego\n";
        }
        else
        {
            for(int i=0;i<=maxNKredytow_;i++)
            {
                if(kredyty_[i].getSplacenie())
                    {
                        kredyty_[i] = Kredyt(kwota,czasSplaty,nKredytow_);
                        stanKonta_+=kwota;
                        break;
                    }
                if(i==maxNKredytow_)
                {
                    std::cout<<"Splac ktorys z kredytow!\n";
                }
            }  
        }
    }

    void zatrudnij(int pracownik)
    {
        if(nPracownikow_>=maxNPracownikow_)
        {
            std::cout<<"Liczba pracownikow nie moze być zwiekszona\n";
        }
        else
        {
            switch (pracownik)
            {
            case 1:
                pracownicy_[nPracownikow_+1] = std::make_unique<Inz>();
                nInz_++;
                nPracownikow_++;
                break;
            case 2:
                pracownicy_[nPracownikow_+1] = std::make_unique<Mag>();
                nMag_++;
                nPracownikow_++;
                break;
            case 3:
                pracownicy_[nPracownikow_+1] = std::make_unique<Mkt>();
                nMkt_++;
                nPracownikow_++;
                break;
            case 4:
                pracownicy_[nPracownikow_+1] = std::make_unique<Rob>();
                nRob_++;
                nPracownikow_++;
                break;  
            }
        }
    }

    void zaplacWynagrodzenia()
    {
        double wynagrodzenia;
        wynagrodzenia = nInz_*payInz_+nMkt_*payMkt_+nMag_*payMag_+nRob_*payRob_;
        stanKonta_ = stanKonta_- wynagrodzenia;
    }

    void otrzymajPrzychod()
    {
        stanKonta_+=obliczPrzychod();
    }

    void splacRaty()
    {
        std::cout<<"\n#################################################\n";
        std::cout<<"STAN KREDYTOW\n";
        for(int i=0;i<maxNKredytow_;i++)
        {   
            if(kredyty_[i].getSplacenie()==false)
            {
                kredyty_[i].splacRate(stanKonta_,nKredytow_);
            }
        }
    }

    double getWydatki()
    {
        double w;
        w = nInz_*payInz_+nMkt_*payMkt_+nMag_*payMag_+nRob_*payRob_;

        for(int i =0;i<maxNKredytow_;i++)
        {
            if (kredyty_[i].getSplacenie() == false)
            {
                w += kredyty_[i].getRata();
            }
        }

        return w;
    }

    double getStanKonta()
    {
        return stanKonta_;
    }

    void getStanFirmy()
    {
        std::cout<<"Pieniadze na kacie = "<<stanKonta_<<"\t Wartosc firmy = "<<wartoscFirmy()<<"\n";
        std::cout<<"Ostatni przychod = "<<historiaPrzychodow_[0]<<"\tWydatki = "<<getWydatki()<<"\n";
        std::cout<<"Liczba kredytow = "<<nKredytow_<<"\n";
        std::cout<<"Liczba produktow w magazynie = "<<ileWMagazynie_<<"\n";
        std::cout<<"Ilosc pracownikow = "<<nPracownikow_<<" w tym:\n";
        std::cout<<"Inz = "<<nInz_<<"\nMkt = "<<nMkt_<<"\nMag = "<<nMag_<<"\nRob = "<<nRob_<<"\n";
    }

    double wartoscFirmy()
    {
        double temp = 0;
        for(int i=0;i<nMiesWartoscFirmy_;i++)
        {
            temp = temp + historiaPrzychodow_[i];
        }
        temp = temp/nMiesWartoscFirmy_;
        return temp;
    }

    double obliczPrzychod()
    {
        int produkcja;
        int nSprzedanych;
        int produkcjaMax= nRob_*CR_;
        int pojemnoscMagazynu = nMag_*CMag_;
        
        double przychod;
        double cenaProduktu = nInz_*CI_;
        double popyt = nMkt_*CMkt_;

        if(produkcjaMax<=pojemnoscMagazynu-ileWMagazynie_)
        {
            produkcja = produkcjaMax;
            ileWMagazynie_+=produkcja;
        }
        else
        {
            ileWMagazynie_ = pojemnoscMagazynu;
        }

        if(ileWMagazynie_<=popyt)
        {
            nSprzedanych = ileWMagazynie_;
            ileWMagazynie_ = 0;
        }
        else
        {
            nSprzedanych = popyt;
            ileWMagazynie_-=popyt;
        }

        przychod = nSprzedanych*cenaProduktu;

        for(int k=1;k<=nMiesWartoscFirmy_;k++)
        {
            historiaPrzychodow_[k] = historiaPrzychodow_[k-1];
        }
        historiaPrzychodow_[0] = przychod;

        return przychod;
    }


    private:
    double stanKonta_;
    int nKredytow_;
    int nPracownikow_;
    int nInz_ = 1;
    int nMkt_ = 1;
    int nMag_ = 1;
    int nRob_ = 1;
    int ileWMagazynie_ = 0;

    const double payInz_ = 9000;
    const double payMkt_ = 12000;
    const double payMag_ = 4500;
    const double payRob_ = 6000;

    const double maxKredyt_ = 5000000;
    const int maxCzasKredyt_ = 30;
    static const int maxNPracownikow_ = 1000;
    static const int maxNKredytow_ = 20;
    static const int nMiesWartoscFirmy_ = 12;
   
    const double CI_ = 40;
    const double CMag_ = 300;
    const double CMkt_ = 200;
    const double CR_ = 150;
    
    std::unique_ptr<Worker> pracownicy_[maxNPracownikow_];
    std::unique_ptr<Kredyt[]> kredyty_ = std::make_unique<Kredyt[]>(maxNKredytow_);
    std::unique_ptr<double[]> historiaPrzychodow_ = std::make_unique<double[]>(nMiesWartoscFirmy_);
};