#include <iostream>
class Kredyt
{
    public:
    void splacRate(double& pieniadze,int& liczbaKredytow)
    {
        if (pozostaleRaty_>1)
        {
            pieniadze = pieniadze - rata_;
            dlug_ = dlug_ - rata_;
            pozostaleRaty_--;
            std::cout<<"Pozostalo "<<pozostaleRaty_<<" rat do splacenia\n";
        }
        else if(pozostaleRaty_ == 1)
        {
            pieniadze = pieniadze - rata_;
            dlug_ = dlug_ - rata_;
            pozostaleRaty_--;
            czySplacony_ = true;
            liczbaKredytow--;
            std::cout<<"Kredyt splacony\n";
        }
    }

    double getRata()
    {
        return rata_;
    }

    bool getSplacenie()
    {
        return czySplacony_;
    }

    Kredyt(double pozyczka, int czas, int& liczbaKredytow): czySplacony_{false}, oprocentowanie_{czas}
    {
            pozostaleRaty_ = czas*12;
            dlug_ = (1.0+oprocentowanie_/100)*pozyczka;
            rata_ = dlug_/pozostaleRaty_;
            liczbaKredytow++;
            std::cout<<"Kredyt zaciagniety na "<<czas<<" lat, miesieczna rata = "<<rata_<<"\n"; 
    }

    Kredyt() = default;

    private:
    double dlug_{};
    int pozostaleRaty_{};
    int oprocentowanie_{};
    double rata_{};
    bool czySplacony_ = true;
};