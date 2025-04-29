// created by vivek 4/24/2025

// Implementation of code provided by Robin Green in his 
// 2003 article *Spherical Harmonic Lighting: The Gritty Details*

#ifndef NITTYGRITTY_H
#define NITTYGRITTY_H

#include <limits>
#include <memory>
#include <random>
#include "../raytracer/vec3.h"

// C++ Std Using

struct SHSample {
    vec3 sph;
    vec3 vec;
    std::unique_ptr<double[]> coeff;
};



// Associated Legendre Polynomials - returns real numbers
// l is the band index
double P(int l, int m, double x) {
    // evaluate an Associated Legendre Polynomial at x
    // using a set of 3 recurrence relations
    
    // The pmm is the first recurrence relation, starting with P_0^0
    double pmm = 1.0;
    if (m > 0) {
        double somx2 = sqrt((1.0-x)*(1.0+x));
        double fact = 1.0;
        for (int i = l; i<=m; i++) {
            pmm *= (-fact) * somx2;
            fact += 2.0;
        }
    }

    if (l==m)
        return pmm;

    // the pmmp1 recurrence relation lets us lift a term to a higher band
    double pmmp1 = x * (2.0*m + 1.0) * pmm;
    
    if (l == m+1)
        return pmmp1;

    // the pll recurrence relation takes the previous two bands, pmmp1 and pmm, and
    // generates a new higher band l from them
    double pll = 0.0;
    for (int ll = m+2; ll <= l; ll++) {
        pll = ( (2.0*ll-1.0)*x*pmmp1 - (ll+m-1.0) * pmm ) / (ll-m);
        pmm = pmmp1;
        pmmp1 = pll;
    }

    return pll;

}

double K(int l, int m) {
    // renormalization constant for SH function
    double temp = ( (2.0*l+1.0) * factorial(l-m) ) / (4.0*pi*factorial(l+m));
    return sqrt(temp);
}

double SH(int l, int m, double theta, double phi) {
    // return a point sample of a Spherical Harmonic basis function
    // l is the band, range [0..N]
    // m in the range [-l..l]
    // theta in the range [0..pi]
    // phi in the range [0..2pi]
    const double sqrt2 = sqrt(2.0);
    if (m==0)
        return K(l, 0)*P(l, m, cos(theta));
    else if (m > 0)
        return sqrt2*K(l,m)*cos(m*phi)*P(l,m,cos(theta));
    else
        return sqrt2*K(l, -m)*sin(-m*phi)*P(l, -m, cos(theta));
}

void SH_setup_spherical_samples(SHSample samples[], int sqrt_n_samples, int n_bands) {
    // fill an N*N*2 array with uniformly distributed
    // samples across the sphere using jittered stratification
    int i=0; // array index
    double oneoverN = 1.0/sqrt_n_samples;
    for (int a = 0; a < sqrt_n_samples; a++) {
        for (int b=0; b < sqrt_n_samples; b++) {
            // generate unbiased distribution of spherical coords
            double x = (a + random_double()) * oneoverN; // do not reuse results
            double y = (b + random_double()) * oneoverN; // each sample must be random
            double theta = 2.0 * acos(sqrt(1.0 - x));
            double phi = 2.0 * pi * y;
            samples[i].sph = vec3(theta, phi, 1.0);

            // convert spherical coords to unit vector
            vec3 vec(sin(theta)*cos(phi), sin(theta)*sin(phi), cos(theta));
            samples[i].vec = vec;

            samples[i].coeff = std::make_unique<double[]>(n_bands*n_bands);

            // precompute all SH coefficients for this sample
            for( int l = 0; l < n_bands; l++) {
                for (int m =-l; m<=l; m++) {
                    int index = l*(l+1) + m;
                    samples[i].coeff[index] = SH(l, m, theta, phi);
                }
            }
            i++;
        }
    }
};
#endif
