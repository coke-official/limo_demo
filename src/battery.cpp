#include "unistd.h"
#include "ros/ros.h"
#include "ros/package.h"
#include "std_msgs/Header.h"
#include "std_msgs/Bool.h"
#include "sound_play/sound_play.h"
#include "limo_base/LimoStatus.h" 
float threshold;
class BATTERY_CHECK{

	BATTERY_CHECK(){
		ros::NodeHandle n;
		ros::NodeHandle pnh("~");
		pnh.getParam("threshold", threshold, 12);
		sound_play::SoundClient sound_client;
		ros::Subscriber sub = n.subscribe("limo_status", 10, batteryCallback);
		ros::Publisher charge_pub = n.advertise<std_msgs::Bool>("charge",1000);
	}
	~BATTERY_CHECK(){}

	void batteryCallback(const limo_base::LimoStatus& msg)
	{
		std::string path = "/home/agilex/catkin_ws/src/limo_demo/voice/juuden.wav";
		std_msgs::Bool charge;
		float voltage = msg.battery_voltage;
		ROS_INFO("battery_voltage: %f", voltage);
		if (voltage < threshold)
		{
			sound_client.playWave(path, 1.0);
			sleep(3);
			charge.data = true;
		}else{
			charge.data = false;
		}
		charge_pub.publish(charge);
	}


};


int main(int argc, char **argv)
{
	ros::init(argc, argv, "battery");
	BATTERY_CHECK btc;
	ros::spin();

	return 0;
}
