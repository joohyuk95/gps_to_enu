#ifndef GPS_CONVERSION_H
#define GPS_CONVERSION_H

// Structure for GPS coordinates
struct GPS {
    double latitude;
    double longitude;
    double altitude;
};

// Structure for ECEF coordinates
struct ECEF {
    double x;
    double y;
    double z;
};

// Structure for ENU coordinates
struct ENU {
    double east;
    double north;
    double up;
};

// Function declarations
ECEF gpsToECEF(const GPS& gps);
ENU ecefToENU(const ECEF& ref, const ECEF& target, const GPS& refGPS);

#endif // GPS_CONVERSION_H
