#pragma once
#include<cmath>
#include<string>
#include<iostream>
#include<fstream>
using namespace std;

#include "species.hpp"



class Parts
{
private:
    int Ns;
    vector<Species> parts;
public:
    ~Parts(){}
    Parts(){Ns = 0;}
    int getNs() {return Ns;}
    void add_particle(Species&& sp)
    {
        parts.push_back(sp);
        Ns += 1;
    }
    Species& operator[] (int i)
    {
        return parts[i];
    }
    void Scatter(Grid& grid)
    {
        for(int ns=0;ns<Ns;ns++)
        {
            parts[ns].scatter_density(grid); 
        }
    }
    void Gather(Grid& grid,EM_field& em)
    {
        for(int ns=0;ns<Ns;ns++)
        {
            parts[ns].GatherE(grid,em);
        }
    }
    void Advance(Grid& grid)
    {
        for(int ns=0;ns<Ns;ns++)
        {
            parts[ns].advance(grid);
        }
    }
    void Initial_set(Grid& grid)
    {
        for(int ns=0;ns<Ns;ns++)
        {
            parts[ns].initial_set(grid);
        }
    }
};
