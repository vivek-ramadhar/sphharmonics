// // Created by vivek on 2/6/2025. //
#ifndef VEC3_H
#define VEC3_H

#include <cmath>
#include <ostream>

// Constants
const double infinity = std::numeric_limits<double>::infinity();
const double pi =  3.1415926535897932385;
constexpr double FACTORIAL_TABLE[] = {
    1.0, // 0!
    1.0, // 1!
    2.0, // 2!
    6.0, // 3!
    24.0,                           // 4!
    120.0,                          // 5!
    720.0,                          // 6!
    5040.0,                         // 7!
    40320.0,                        // 8!
    362880.0,                       // 9!
    3628800.0,                      // 10!
    39916800.0,                     // 11!
    479001600.0,                    // 12!
    6227020800.0,                   // 13!
    87178291200.0,                  // 14!
    1307674368000.0,                // 15!
    20922789888000.0,               // 16!
    355687428096000.0,              // 17!
    6402373705728000.0,             // 18!
    121645100408832000.0,           // 19!
    2432902008176640000.0,          // 20!
    51090942171709440000.0,         // 21!
    1124000727777607680000.0,       // 22!
    25852016738884976640000.0,      // 23!
    620448401733239439360000.0,     // 24!
    15511210043330985984000000.0,   // 25!
    403291461126605635584000000.0,  // 26!
    10888869450418352160768000000.0, // 27!
    304888344611713860501504000000.0, // 28!
    8841761993739701954543616000000.0, // 29!
    265252859812191058636308480000000.0, // 30!
    8222838654177922817725562880000000.0, // 31!
    263130836933693530167218012160000000.0, // 32!
    8683317618811886495518194401280000000.0 // 33!
};

// Utility Functions

inline double factorial(unsigned int n) {
    return (n<=33) ? FACTORIAL_TABLE[n] : infinity;
}

inline double degrees_2_radians(double degrees) {
    return degrees * pi / 180.0;
}

inline double radians_2_degrees(double radians) {
    return radians * 180.0 / pi;
}

inline double random_double() {
    // Return random x in range [0,1)
    return std::rand() / (RAND_MAX + 1.0);
}

inline double random_double(double min, double max) {
    // Returns a random real in [min,max)
    return min + (max-min)*random_double();
}

inline int random_int(int min, int max) {
    // Returns a random integer in [min,max].
    return int(random_double(min, max+1));
}

class vec3 {
    public:
        double e[3];

        vec3() : e{0,0,0} {}
        vec3(double e0, double e1, double e2) : e{e0,e1,e2} {}

        double x() const {return e[0]; }
        double y() const {return e[1]; }
        double z() const {return e[2]; }

        vec3 operator-() const { return vec3(-e[0], -e[1], -e[2]); }
        double operator[](int i) const { return e[i]; }
        double& operator[](int i) { return e[i]; }

        vec3& operator+=(const vec3& v) {
            e[0] += v.e[0];
            e[1] += v.e[1];
            e[2] += v.e[2];

            return *this;
        }

        vec3& operator*=(double t) {
            e[0] *= t;
            e[1] *= t;
            e[2] *= t;

            return *this;
        }

        vec3& operator/=(double t) {
            return *this *= 1/t;
        }

        double length() const {
            return std::sqrt(length_squared());
        }

        double length_squared() const {
            return e[0]*e[0] + e[1]*e[1] + e[2]*e[2];
        }

        bool near_zero() const {
            // Return true if the vector is close to zero in all dimensions
            auto s = 1e-8;
            return (std::fabs(e[0]) < s) && (std::fabs(e[1]) < s) && (std::fabs(e[2]) < s);
        }

        static vec3 random() {
            return vec3(random_double(),random_double(),random_double());
        }

        static vec3 random(double min, double max) {
            return vec3(random_double(min,  max), random_double( min,  max), random_double( min,  max));
        }



};

//  point3 is just an alias for vec3, useful for geometric clarity in code
using point3 = vec3;

// Vector Utility Functions

inline std::ostream& operator<<(std::ostream& out, const vec3& v) {
    return out << v.e[0] << ' ' << v.e[1] << ' ' << v.e[2];
}

inline vec3 operator+(const vec3& u, const vec3& v) {
    return vec3(u.e[0] + v.e[0], u.e[1] + v.e[1], u.e[2] + v.e[2]);
}

inline vec3 operator-(const vec3& u, const vec3& v) {
    return vec3(u.e[0]-v.e[0], u.e[1]-v.e[1], u.e[2]-v.e[2]);
}

inline vec3 operator*(const vec3& u, const vec3& v) {
    return vec3(u.e[0] * v.e[0], u.e[1] * v.e[1], u.e[2] * v.e[2]);
}

inline vec3 operator*(double t, const vec3& v) {
    return vec3(t*v.e[0], t*v.e[1], t*v.e[2]);
}

inline vec3 operator*(const vec3& v, double t) {
    return t*v;
}

inline vec3 operator/( const vec3& v, double t) {
    return (1/t)*v;
}

inline double dot(const vec3& u, const vec3& v) {
    return u.e[0]*v.e[0] + u.e[1]*v.e[1] + u.e[2]*v.e[2];
}

inline vec3 cross(const vec3& u, const vec3& v) {
    return vec3(u.e[1]*v.e[2] - u.e[2]*v.e[1],
                u.e[2]*v.e[0] - u.e[0]*v.e[2],
                u.e[0]*v.e[1] - u.e[1]*v.e[0]);
}

inline vec3 unit_vector(const vec3& v) {
    return v / v.length();
}

inline vec3 random_in_unit_disk() {
    while (true) {
        auto p = vec3(random_double(-1,1), random_double(-1,1), 0);
        if (p.length_squared() < 1)
            return p;
    }
}

inline vec3 random_unit_vector() {
    while (true) {
        auto p = vec3::random(-1,1);
        auto lensq = p.length_squared();
        if (1e-160 < lensq && lensq <= 1)
            return p/sqrt(lensq);
    }
}

inline vec3 random_on_hemisphere(const vec3& normal) {
    vec3 on_unit_sphere = random_unit_vector();
    if (dot(on_unit_sphere, normal) > 0.0) // In the same hemisphere as the normal
        return on_unit_sphere;
    else
        return -on_unit_sphere; // Invert vector so in the right hemisphere
}

inline vec3 random_cosine_direction() {
    auto r1 = random_double();
    auto r2 = random_double();

    auto phi = 2*pi*r1;
    auto x = std::cos(phi) * std::sqrt(r2);
    auto y = std::sin(phi) * std::sqrt(2);
    auto z = std::sqrt(1-r2);

    return vec3(x, y , z);

}

inline vec3 reflect(const vec3& v, const vec3& n) {
    return v - 2*dot(v,n)*n;
}

inline vec3 refract(const vec3& uv, const vec3& n, double etai_over_etat) {
    auto cos_theta = std::fmin(dot(-uv,n), 1.0);
    vec3 r_out_perp = etai_over_etat * (uv + cos_theta*n);
    vec3 r_out_parallel = -std::sqrt(std::fabs(1.0-r_out_perp.length_squared())) * n;
    return r_out_perp + r_out_parallel;
}

#endif //VEC3_H


