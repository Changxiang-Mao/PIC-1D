#pragma once
#include<string>
using namespace std;

class Property
{
private:
    double mass;
    double charge;
    double weight;
    string name;
public:
    Property(){}
    void set(double m,double q,double w,string n)
    {
        mass = m;
        charge = q;
        weight = w;
        name = n;
    }
    void operator=(Property& pp)
    {
        mass = pp.getmass();
        charge = pp.getcharge();
        weight = pp.getweight();
        name = pp.getname();
    }
    double getmass()
    {
        return mass;
    }
    double getcharge()
    {
        return charge;
    }
    double getweight()
    {
        return weight;
    }
    string getname()
    {
        return name;
    }
};
