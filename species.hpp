#pragma once
using namespace std;
#include<cmath>
#include<fstream>
#include<string>

#include "my_fun.hpp"
#include "param.hpp"
#include "EM_field.hpp"

class Species
{
private:
    Param PP;
    int Nsim;
    Property pro;
    Point<Vec3> pos; // at t = i
    Point<Vec3> vel; // at t = i-1/2
    Point<Vec3> Ep;  // at t=i
    Point<double> phip;
    Field<double> num_den; //at i
public:
    Species(){}
    ~Species(){}
    Species(double m,double q,double w,string n,int nsim,Grid& grid)
    {
        this->ini(m,q,w,n,nsim,grid);
    }
    void ini(double m,double q,double w,string n,int nsim,Grid& grid)
    {
        Nsim = nsim;
        pro.set(m,q,w,n);
        pos.ini(Nsim);
        vel.ini(Nsim);
        Ep.ini(Nsim);
        phip.ini(Nsim);
        int Nx = grid.getNx();
        num_den.ini(Nx);
    }

    int getNsim() {return Nsim;}
    Point<Vec3>& getpos(){
        return pos;
    }
    Point<Vec3>& getvel(){
        return vel;
    }
    Point<Vec3>& getEp(){
        return Ep;
    }
    Property& getProperty(){
        return pro;
    }
    Field<double>& getNumberDensity()
    {
        return num_den;
    }

    void scatter_density(Grid& grid)
    {
        double weight = pro.getweight();
        num_den = 0.;
        double dx = grid.getDx();
        double xmin = grid.getXmin();
        int Nx = grid.getNx();   
        for(int p=0;p<Nsim;p++)
        {
            int x_index=int( (pos[p][0]-xmin)/dx );
            double di = (pos[p][0]-(xmin+x_index*dx))/dx;
            if(x_index==Nx-1) 
            {
                x_index = Nx-2;
                di=1;
            }
            num_den[x_index] += (1-di)*weight;
            num_den[x_index+1] += (di)*weight;   
        }
        for(int i=0;i<Nx;i++)
        {
            num_den[i] = num_den[i]/dx;
        }
        double nn = num_den[0]+num_den[Nx-1];
        num_den[0] = nn;
        num_den[Nx-1] = nn;
    }

    void GatherE(Grid& grid,EM_field& em)
    {
        Field<Vec3> ef = em.getE();
        Field<double> phif = em.getphi();
        Gather_grid_centered(Ep,grid,pos,ef);
        Gather_grid_centered(phip,grid,pos,phif);
        // if(pro.getname() == "electron")
        //     cout << "Ep = " << Ep[0][0] << ",";
    }
    

    void advance(Grid& grid)
    {
        double dt = grid.getDt();
        int Nsim = pos.getNp();
        // if(pro.getname() == "electron")
        //     cout << "v = " << vel[0][0] <<  endl;
        for(int p=0;p<Nsim;p++)
        {
            NR_noB_push(vel[p],Ep[p],pro,dt);
            pos[p] += vel[p]*dt;
        }
        applyboundary(grid);
    }

    void applyboundary(Grid& grid)
    {
        double xmax = grid.getXmax();
        double xmin = grid.getXmin();
        int Nsim = pos.getNp();
        for(int p=0;p<Nsim;p++)
        {
            if(pos[p][0] > xmax)
            {
                pos[p][0] = xmin + (pos[p][0] - xmax);
            }
            if(pos[p][0] < xmin)
            {
                pos[p][0] = xmax - (xmin - pos[p][0]);
            }
        }
    }

    void operator=(Species& sp)
    {
        Nsim = sp.getNsim();
        pos = sp.getpos();
        vel = sp.getvel();
        Ep = sp.getEp();
        pro = sp.getProperty();
        num_den = sp.getNumberDensity();
    }

    void initial_set(Grid& grid)
    {
        double x,vx;
        double xmin = grid.getXmin();
        double xmax = grid.getXmax();
        int Nsim = pos.getNp();
        double dl;
        for(int p=0;p<Nsim;p++)
        {
            dl = (xmax-xmin)/Nsim;
            x = xmin + (p+0.5)*dl;
            pos[p] = Vec3(x,0,0);
            if(pro.getname() == "electron")
            {
                if(x < 0.5*(xmin+xmax) )
                {
                    vx = gaussian_distribution(PP.v0,PP.sigma_th);
                    // vx = PP.v0;
                }
                else
                {
                    vx = gaussian_distribution(-PP.v0,PP.sigma_th);
                    // vx = -PP.v0;
                }
            }
            else
            {
                if(x < 0.5*(xmin+xmax) )
                {
                    vx = gaussian_distribution(PP.v0,PP.sigma_th);
                    // vx = PP.v0;
                }
                else
                {
                    vx = gaussian_distribution(-PP.v0,PP.sigma_th);
                    // vx = -PP.v0;
                }
            }
            vel[p] = Vec3(vx,0,0);
        }
    }

    double kinetic_energy(Grid& grid)
    {
        double dt = grid.getDt();
        double Ek = 0;
        Vec3 vi;
        double q = pro.getcharge();
        double m = pro.getmass();
        for(int p=0;p<Nsim;p++)
        {
            vi = vel[p] + Ep[p]*(q/m*dt/2);
            Ek += 0.5*m*vi.L2();
        }
        return Ek;
    }

    double potential_energy()
    {
        double q = pro.getcharge();
        double Ep = 0;
        for(int p=0;p<Nsim;p++)
        {
            Ep += q*phip[p];
        }
        return Ep;
    }

    double vmax()
    {
        double vv;
        vv = vel[0][0];
        for(int p=1;p<Nsim;p++)
        {
            if(vv<vel[p][0])
            {
                vv = vel[p][0];
            }
        }
        return vv;
    }
};
