#pragma once

class Grid
{
private:
    int Nx;
    double Xmin;
    double Xmax;
    double Dt;
    double Dx;
public:
    Grid(int nx,double xmin,double xmax,double dt)
    {
        Nx = nx;
        Xmin = xmin;
        Xmax = xmax;
        Dt = dt;
        Dx = (Xmax-Xmin)/(Nx-1);
    }
    double getXmin(){return Xmin;}
    double getXmax(){return Xmax;}
    double getDx(){return Dx;}
    double getDt(){return Dt;}
    int getNx(){return Nx;}
};
