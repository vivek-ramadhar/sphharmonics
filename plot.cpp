#include "nittygritty.h"
#include <iostream>
#include <vector>
#include <polyscope/polyscope.h>
#include <polyscope/point_cloud.h>
#include <polyscope/standardize_data_array.h>

int main() {
    polyscope::init();

    int sqrt_n_samples = 100;
    int n_samples = sqrt_n_samples * sqrt_n_samples;
    int n_bands = 4;

    // parentheses initialize (size is n_samples and filled with initialized default val SHSamples)
    std::vector<SHSample> samples(n_samples);
    // fill sample vector with jittered samples over the sphere
    SH_setup_spherical_samples(samples, sqrt_n_samples, n_bands);

    // create vector container to extract vec3 components from each SHSample
    std::vector<vec3> sample_points;
    sample_points.reserve(n_samples);

    // apply lambda to each element of samples
    std::transform(
        samples.begin(),
        samples.end(),
        std::back_inserter(sample_points ),
        [](const SHSample& ss) {return ss.vec;} // access vec3 member
        );

    // plot vector of vec3 points with polyscope
    polyscope::registerPointCloud("SH Sample Points", sample_points);
    polyscope::getPointCloud("SH Sample Points")->setPointRadius(0.005);
    polyscope::show();


    return 0;
};

