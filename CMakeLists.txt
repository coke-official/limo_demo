cmake_minimum_required(VERSION 3.0.2)
project(limo_demo)

find_package(catkin REQUIRED COMPONENTS
  roscpp
  rospy
  std_msgs
  limo_base
  sound_play
)

catkin_package(
  INCLUDE_DIRS include
  LIBRARIES limo_demo
  CATKIN_DEPENDS roscpp rospy std_msgs limo_base sound_play
  DEPENDS system_lib
)

include_directories(
  include
  ${catkin_INCLUDE_DIRS}
)
add_executable(battery src/battery.cpp)
add_dependencies(battery ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})
target_link_libraries(battery
  ${catkin_LIBRARIES}
)
