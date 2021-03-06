#include "ros/ros.h"
#include "std_msgs/String.h"

void chatterCallback(const std_msgs::String::ConstPtr& msg);

int main (int argc,char** argv){
    //ros init
    ros::init(argc,argv,"listener");
    //
    ros::NodeHandle n;

    ros::Subscriber sub =n.subscribe("chatter_x",1000,chatterCallback);

    ros::spin();
    //add new comment
    

    return 0;
}

void chatterCallback(const std_msgs::String::ConstPtr& msg) {
    ROS_INFO("I heard: [%s]", msg->data.c_str());
}
     