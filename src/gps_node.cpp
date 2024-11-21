#include "ros/ros.h"
#include "gps_conversion_pkg/gps_conversion.h"
#include "geometry_msgs/Point.h"
#include "sensor_msgs/NavSatFix.h"
#include "geographic_msgs/GeoPointStamped.h"

geographic_msgs::GeoPointStamped geo_origin;
bool geo_origin_received = false;

ros::Publisher* enu_pub_ptr = nullptr;

void geoOriginCallback(const geographic_msgs::GeoPointStamped::ConstPtr& msg) {
    geo_origin = *msg;
    geo_origin_received = true;
}

void gpsCallback(const sensor_msgs::NavSatFix::ConstPtr& msg) {
    if (!geo_origin_received) {
        return;
    }

    GPS pointA = {geo_origin.position.latitude, geo_origin.position.longitude, geo_origin.position.altitude};
    GPS pointB = {msg->latitude, msg->longitude, msg->altitude};

    ECEF ecefA = gpsToECEF(pointA);
    ECEF ecefB = gpsToECEF(pointB);

    ENU enuB = ecefToENU(ecefA, ecefB, pointA);

    geometry_msgs::Point enu;
    enu.x = enuB.east;
    enu.y = enuB.north - 2.0;

    enu_pub_ptr->publish(enu);
}

int main(int argc, char** argv) {
    ros::init(argc, argv, "gps_conversion_node");
    ros::NodeHandle nh;

    ros::Subscriber geo_origin_sub = nh.subscribe<geographic_msgs::GeoPointStamped>(
        "/mavros/global_position/gp_origin", 10, geoOriginCallback);
    
    ros::Publisher enu_pub = nh.advertise<geometry_msgs::Point>("station_enu", 10);
    enu_pub_ptr = &enu_pub;
    
    ros::Subscriber gps_sub = nh.subscribe<sensor_msgs::NavSatFix>(
        "/navsat/fix", 10, gpsCallback);

    ros::spin();

    return 0;
}

