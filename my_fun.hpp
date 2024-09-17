#pragma once
#include<cassert>

#include "./my_header/header.hpp"


template<typename T>
void Gather_grid_centered(Point<T>& fp,Grid& grid,Point<Vec3>& pos,Field<T>& field)
{
    int Nx = grid.getNx();
    double dx = grid.getDx();
    double xmin = grid.getXmin();
    int Nsim = pos.getNp();
    int x_index;
    double di;
    for(int p=0;p<Nsim;p++)
    {
        x_index =int( (pos[p][0] - xmin)/dx );
        di = (pos[p][0] - (xmin+x_index*dx))/dx;
        if(x_index == Nx-1) 
        {
            x_index = Nx-2;
            di=1;
        }
        fp[p] = field[x_index]*(1-di) + field[x_index+1]*(di);
    }
}

void NR_noB_push(Vec3& v,Vec3& Ep,Property& pro,double dt)
{
    double m = pro.getmass();
    double q = pro.getcharge();
    v += Ep*(q/m*dt);
}



