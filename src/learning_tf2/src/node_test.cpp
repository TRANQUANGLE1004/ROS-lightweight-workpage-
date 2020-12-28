#include<ros/ros.h>
#include<std_msgs/String.h>
#include<turtlesim/Pose.h>

void callBack(const turtlesim::PoseConstPtr& msg){
    ROS_INFO("Node receive data x %f",msg->x);
}

int main(int argc, char** argv){

    ros::init(argc,argv,"test_node");

    ros::NodeHandle n;
    
    ros::Subscriber sub = n.subscribe("turtle1/pose",10,&callBack);

    ros::spin();
    return 0;
}


