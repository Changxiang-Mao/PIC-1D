#include<iostream>
#include<fstream>
using namespace std;
#include<vector>

#include "save.hpp"
#include "world.hpp"

int main()
{
    // int nx,double xmin,double xmax,double dt
    Grid grid(10001,0,1000,1e-2);
    Param PP;
    World world(grid);
    EM_field em(grid);
    double N_real = PP.n0*(grid.getXmax()-grid.getXmin())*PP.lambda*PP.lambda*PP.lambda;
    int Nsim = 1e4;
    double weight = N_real/double(Nsim);
    Parts parts;
    parts.add_particle(Species(PP.me,-PP.e,weight,"electron",Nsim,grid));
    parts.add_particle(Species(PP.mp,PP.e,weight,"proton",Nsim,grid));
    parts.Initial_set(grid);

    // parts.Scatter(grid);
    // world.calculate_rhoe(parts);
    // em.potential_solver(grid,world.getrhoe(),1e-3);
    // em.E_field(grid);


    // double Ek_e,Ek_i,Ep_e,Ep_i;
    // fstream file;
    // file.open("D:\\VScode\\Cpp\\1D\\data\\energy.txt",ios::out);
    // file << "Eke\tEki\tEpe\tEpi\tEt\n";
    for(int t_step=0;t_step<3000;t_step++)
    {
        cout << t_step << ",";
        parts.Scatter(grid);
        if(t_step%50 == 0)
        {
            saveField0(parts[0].getNumberDensity(),grid,"ne"+to_string(t_step));
            saveField0(parts[1].getNumberDensity(),grid,"np"+to_string(t_step));
            saveField3(em.getE(),grid,"E"+to_string(t_step));
        }
        world.calculate_rhoe(parts);
        em.potential_solver(grid,world.getrhoe(),1e-3);
        em.E_field(grid);

        // Ek_e = parts[0].kinetic_energy(grid);
        // Ek_i = parts[1].kinetic_energy(grid);
        // Ep_e = parts[0].potential_energy();
        // Ep_i = parts[1].potential_energy();
        // // E_E = em.E_field_energy(grid);
        // file << Ek_e << "\t" << Ek_i << "\t" << Ep_e << "\t" << Ep_i << "\t" << Ek_e+Ek_i+Ep_e+Ep_i << endl;

        parts.Gather(grid,em);
        parts.Advance(grid);
    }
    // file.close();
    return 0;
}

