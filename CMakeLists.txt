cmake_minimum_required(VERSION 3.0.2)
project(gps_conversion_pkg)

find_package(catkin REQUIRED COMPONENTS
  roscpp
  sensor_msgs
  std_msgs
)

catkin_package(
 INCLUDE_DIRS include
 LIBRARIES gps_conversion_pkg
 CATKIN_DEPENDS roscpp sensor_msgs std_msgs
 DEPENDS system_lib
)

include_directories(
  include
  ${catkin_INCLUDE_DIRS}
)

add_library(gps_conversion src/gps_conversion.cpp)
add_executable(gps_node src/gps_node.cpp)
target_link_libraries(gps_node gps_conversion ${catkin_LIBRARIES})

