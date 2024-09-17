#pragma once

#include "particle.hpp"
class World
{
private:
    Field<double> rhoe;
    Const CC;
    Param param;
    int Nx;
public:
    World(Grid& grid)
    {
        Nx = grid.getNx();
        rhoe.ini(Nx);
    }
    void calculate_rhoe(Parts& parts)
    {
        rhoe = 0;
        Field<double> num_den;
        num_den.ini(Nx);
        int Ns = parts.getNs();
        double q;
        for(int ns=0;ns<Ns;ns++)
        {
            q = parts[ns].getProperty().getcharge();
            num_den = parts[ns].getNumberDensity();
            for(int i=0;i<Nx-1;i++)
            {
                rhoe[i] += num_den[i]*q;
            }
        }
    }
    Field<double>& getrhoe()
    {
        return rhoe;
    }
};

