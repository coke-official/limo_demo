#include "unistd.h"
#include "ros/ros.h"
#include "ros/package.h"
#include "std_msgs/Header.h"
#include "sound_play/sound_play.h"
#include "limo_base/LimoStatus.h" 
float threshold;

void batteryCallback(const limo_base::LimoStatus& msg)
{
	//std::string path = ros::package::getPath("limo_demo");
	std::string path = "/home/agilex/catkin_ws/src/limo_demo/voice/juuden.wav";
	sound_play::SoundClient sound_client;
	float voltage = msg.battery_voltage;
	ROS_INFO("battery_voltage: %f", voltage);
	if (voltage < threshold)
	{
		sound_client.playWave(path, 1.0);
		sleep(3);
	}
}

int main(int argc, char **argv)
{
	ros::init(argc, argv, "battery");
	sound_play::SoundClient sound_client;
	ros::NodeHandle n;
	ros::NodeHandle pnh("~");
	pnh.getParam("threshold", threshold);
	ros::Subscriber sub = n.subscribe("limo_status", 10, batteryCallback);
	ros::spin();

	return 0;
}
