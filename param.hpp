#pragma once

#include "./my_header/constant.hpp"
class Param
{
public:
    Const CC;
    const double n0 = 10000; // cm^-3
    const double te = 1; // eV ~1e4K
    const double Te = te*1.6e-12; // erg = g cm^2 s^-2
    const double V0 = 1e8; // cm/s

    const double tau = sqrt(CC.M_e/(4*CC.PI*n0*CC.E*CC.E)); //s, 1/tau:plasma frequency 
    const double lambda = sqrt(Te/(4*CC.PI*n0*CC.E*CC.E)); // cm debye length 

    const double c = CC.C*tau/lambda; // lambda/tau
    const double e = CC.E*tau/sqrt(CC.M_e*lambda*lambda*lambda);
    const double me = 1;
    const double mp = CC.M_p/CC.M_e;

    const double sigma_th = 1;       // lambda/tau
    const double v0 = V0*tau/lambda; // lambda/tau

    
};

