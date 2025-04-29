#include "nittygritty.h"
#include <iostream>

int main() {
    int sqrt_n_samples = 100;
    int n_bands = 4;
    SHSample samples[sqrt_n_samples * sqrt_n_samples];

    SH_setup_spherical_samples(samples, sqrt_n_samples, n_bands);

    for(int i=0; i < sqrt_n_samples*sqrt_n_samples; i++) {
        std::cout << samples[i].vec
                  << std::endl;
    };


    return 0;
};

