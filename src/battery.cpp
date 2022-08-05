#include "unistd.h"
#include "ros/ros.h"
#include "ros/package.h"
#include "std_msgs/Header.h"
#include "std_msgs/Bool.h"
#include "sound_play/sound_play.h"
#include "limo_base/LimoStatus.h" 

class BATTERY_CHECK{
	public:
		ros::NodeHandle n;
		void batteryCallback(const limo_base::LimoStatus& msg);
		ros::Subscriber sub = n.subscribe("limo_status", 10, &BATTERY_CHECK::batteryCallback, this);
		ros::Publisher charge_pub = n.advertise<std_msgs::Bool>("charge",1000);
		ros::Rate rate_;
		
	
	
		BATTERY_CHECK() :
			rate_(0.3)
		{
			ros::NodeHandle pnh("~");
			pnh.param("threshold", threshold, 12.0);
			pnh.param("file_path", file_path, std::string(""));


		}
		~BATTERY_CHECK(){}
	private:
		double threshold;
		std::vector<int> charging_threshold;
		std::string file_path;

};

void BATTERY_CHECK::batteryCallback(const limo_base::LimoStatus& msg)
{
	std_msgs::Bool charge;
	sound_play::SoundClient sound_client;
	float voltage = msg.battery_voltage;
	ROS_INFO("battery_voltage: %f", voltage);
	if (voltage < threshold)
	{
		charging_threshold.push_back(1);
	}else{
		charging_threshold.clear();
		charge.data = false;
	}

	if(charging_threshold.size()>20){
		sound_client.playWave(file_path, 1.0);
		charge.data = true;
	}
	charge_pub.publish(charge);
	rate_.sleep();
}


int main(int argc, char **argv)
{
	ros::init(argc, argv, "battery");
	BATTERY_CHECK btc;
	ros::spin();

	return 0;
}
