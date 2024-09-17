#pragma once
using namespace std;
#include<random>

// sample Gaussian distribution double //
double gaussian_distribution(double mean,double sigma)
{  
    random_device rd;
    mt19937 generator(rd());
    std::normal_distribution<double> distribution(mean,sigma);
    double r = distribution(generator);
    return distribution(generator);
}

// sample uniform distribution double //
double uniform_distribution(double xmin,double xmax)
{
    random_device rd;
    mt19937 generator(rd());
    uniform_real_distribution<double> distribution(xmin,xmax);
    double r = distribution(generator);
    return r;
}

// //Lorentz factor from u,u=gamma*v
// double Lorentz_factor(vector<double>& p,double c)
// {
//     double gamma = 0;
//     gamma = sqrt(1+p/(c*c));
//     return gamma;  
// }

// void Boris_push(Vec3& v,Vec3& ep,Vec3& bp,Species& pi,double dt)
// {
//     double charge = pi.getcharge();
//     double mass = pi.getmass();
//     double A = charge/mass*dt/2;
//     Vec3 aE,t,s;
//     Vec3 v_minus,v_prime,v_plus;
//     aE = ep*A;
//     t = bp*A;
//     s = t*(2/(1+t.L2()));
//     v_minus = v + aE;
//     v_prime = v_minus + v_minus.cross(t);
//     v_plus = v_minus + v_prime.cross(s);
//     v = v_plus + aE;
// }

// void Vay_push(Vec3& p,const Vec3& ep,const Vec3& bp,const Species& pi,double dt,double c)
// {
//     double charge = pi.getcharge();
//     double mass = pi.getmass();
//     double A = charge*dt/(2*mass);
//     double gamma_m = Lorentz_factor(p,c);
//     Vec3 v;
//     v = p*(1/gamma_m);
//     Vec3 u_i,u_prime,u_p,tau,t;
//     double u_star,gamma_prime2,sigma,gammap,s;
//     double tau2,u2,sigma2;
//     u_i = p + (ep+v.cross(bp))*A;
//     u_prime = u_i + ep*A;
//     tau = bp*A;
//     tau2 = tau.L2();
//     u_star = u_prime*tau/c;
//     u2 = u_star*u_star;
//     gamma_prime2 = 1 + u_prime.L2()/(c*c);
//     sigma = gamma_prime2 - tau2;
//     sigma2 = sigma*sigma;
//     u2 = 0;///////
//     if(sigma<0 && sigma2/tau2>1e10)
//     {
//         gammap = sqrt(tau2/fabs(sigma));
//     }
//     else
//     {
//         gammap = sqrt(( sigma + sqrt(sigma2+4*(tau2+u2)) )/2.);
//     }
//     // if(pp==7440 && pi.getname() == "e-")
//     // {
//     //     cout << "gamma'2 = " << gamma_prime2 << endl;
//     //     cout << "sigma = " << sigma << endl;
//     //     cout << "tau2 = " << tau2 << endl;
//     //     cout << "u2 = " << u2 << endl;
//     //     cout << "gammap = " << gammap << endl;
//     // }
//     t = tau*(1/gammap);
//     s = 1/(1+t.L2());
//     p = (u_prime + t*(u_prime*t) + u_prime.cross(t) )*s;
// }

