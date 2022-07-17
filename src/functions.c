#include "config.h"


// Funkcia na vypocet vzdialenosti dvoch GPS suradnic.
double distance(const GPS gps1, const GPS gps2) {
    double d, z, u, v;

    // konverzia na radiany
    double phi1 = deg2rad(gps1.lat);
    double phi2 = deg2rad(gps2.lat);
    double lambda1 = deg2rad(gps1.lon);
    double lambda2 = deg2rad(gps2.lon);

    // predvypocet sinusov, ktore sa potom umocnia na druhu
    u = sin((phi2 - phi1) / 2.0);
    v = sin((lambda2 - lambda1) / 2.0);

    // vypocet vnutornej casti vzorca
    z = sqrt(u * u + cos(phi1) * cos(phi2) * v * v);
    // finalizacia
    d = 2.0 * RADIUS_EARTH_KM * asin(z);

    return d;
}