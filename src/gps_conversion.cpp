#include "gps_conversion_pkg/gps_conversion.h"
#include <cmath>

const double a = 6378137.0;
const double b = 6356752.3142;
const double e_sq = 1 - (b * b) / (a * a);

ECEF gpsToECEF(const GPS& gps) {
    double lat = gps.latitude * M_PI / 180.0;
    double lon = gps.longitude * M_PI / 180.0;
    double h = gps.altitude;

    double N = a / sqrt(1 - e_sq * sin(lat) * sin(lat));

    ECEF ecef;
    ecef.x = (N + h) * cos(lat) * cos(lon);
    ecef.y = (N + h) * cos(lat) * sin(lon);
    ecef.z = (N * (1 - e_sq) + h) * sin(lat);

    return ecef;
}

ENU ecefToENU(const ECEF& ref, const ECEF& target, const GPS& refGPS) {
    double lat = refGPS.latitude * M_PI / 180.0;
    double lon = refGPS.longitude * M_PI / 180.0;

    double dx = target.x - ref.x;
    double dy = target.y - ref.y;
    double dz = target.z - ref.z;

    ENU enu;
    enu.east  = -sin(lon) * dx + cos(lon) * dy;
    enu.north = -cos(lon) * sin(lat) * dx - sin(lat) * sin(lon) * dy + cos(lat) * dz;
    enu.up    =  cos(lat) * cos(lon) * dx + cos(lat) * sin(lon) * dy + sin(lat) * dz;

    return enu;
}
