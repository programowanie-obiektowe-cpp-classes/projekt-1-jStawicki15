#include <iostream>
#include <cstdlib>
#include <string>
#include "RandomNameGenerator.hpp"

class Worker
{
    public:
    virtual void print()
    {
        std::cout<<"Pracownik "<<name_<<"\n";
    }

    Worker()
    {
        name_ = getRandomName();
    }
    
    protected:
    std::string name_;
};



class Inz : public Worker
{
    public:
    Inz() : Worker{}
    {
        //DODAĆ TWORZENIE WYDZIAŁÓW XD
        wydzial_ = "MEL";
    }
    void print() override
    {
        std::cout<<"Inz "<<name_<<" po wydziale "<<wydzial_<<".\n";
    }
    private:
    std::string wydzial_;
};

class Mkt : public Worker
{
    public:
    Mkt() : Worker{}
    {
        follows_ = rand()%500000;
    }
    void print() override
    {
        std::cout<<"Mkt "<<name_<<" z obserwujacymi "<<follows_<<".\n";
    }
    private:
    int follows_;
};

class Mag : public Worker
{
    public:
    Mag() : Worker{}
    {
        if(rand()%2==0)
            forkliftCertified_ = true;
        else
            forkliftCertified_ = false;
    }

    void print() override
    {
        if (forkliftCertified_)
        {
            std::cout<<"Mag "<<name_<<" z pozwoleniem na wozek\n";
        }
        else
        {
            std::cout<<"Mag "<<name_<<" bez pozwolenia na wozek\n";
        }
        
    }
    private:
    bool forkliftCertified_;
};

class Rob : public Worker
{
    public:
    Rob() : Worker{}
    {
        but_ = 25 + 0.5*static_cast<double>(rand()%51);
    }

    void print() override
    {
        std::cout<<"Rob "<<name_<<" z rozmiarem buta "<<but_<<"\n";
    }
    private:
    double but_;
};