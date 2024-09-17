#pragma once
using namespace std;
#include<cmath>

#include "./my_header/header.hpp"

class EM_field
{
private:
    Field<Vec3> E;
    Field<double> phi;
    int Nx;
    Const CC;
public:
    EM_field(Grid& grid)
    {
        Nx = grid.getNx();
        phi.ini(Nx);
        phi = 0.;
        E.ini(Nx);
    }
    int getNx() {return Nx;}

    Field<Vec3>& getE()
    {
        return E;
    }

    Field<double>& getphi()
    {
        return phi;
    }


    void potential_solver(Grid& grid,Field<double>& rhoe,double tol)
    {
        // phi = 0.;
        double dx = grid.getDx();
        int ite=0;
        double rhoe_mean = 0;
        for(int i=0;i<Nx;i++)
        {
            rhoe_mean += rhoe[i]*rhoe[i];
        }
        rhoe_mean = sqrt(rhoe_mean)/Nx;
        double g;
        while(1)
        {

            for(int i=1;i<Nx-1;i++)
            {
                g = 0.5*(phi[i+1]+phi[i-1]+4*CC.PI*rhoe[i]*dx*dx);
                phi[i] = phi[i] + 1.4*(g-phi[i]);
            }
            ite += 1;
            if(ite%100==0)
            {
                double R = 0;
                double R2 = 0;
                for(int i=1;i<Nx-1;i++)
                {
                    R = (phi[i+1] + phi[i-1] - 2*phi[i])/(dx*dx)+4*CC.PI*rhoe[i];
                    R2 += R*R;
                }
                if(rhoe_mean!=0)
                    R2 = sqrt(R2)/Nx/(4*CC.PI*rhoe_mean);
                else
                    R2 = sqrt(R2)/Nx;
                //cout << R2 << ",";
                if(R2 < tol)
                {
                    break;
                }
            }
        }
    }

    void E_field(Grid& grid)
    {
        double dx = grid.getDx();
        for(int i=0;i<Nx;i++)
        {
            double Ex;
            if(i==0 || i==Nx-1)
            {
                Ex = -(phi[1]-phi[Nx-2])/(2*dx);
            }
            else
            {
                Ex = -(phi[i+1]-phi[i-1])/(2*dx);
            }
            E[i] = Vec3(Ex,0,0);
        }
    }

    double E_field_energy(Grid& grid)
    {
        double E_E = 0;
        double dx = grid.getDx();
        for(int i=0;i<Nx-1;i++)
        {
            E_E += E[i]*E[i]/(8*CC.PI)*dx;
        }
        return E_E;
    }
};
