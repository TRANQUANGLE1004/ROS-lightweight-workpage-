#include <ros/ros.h>
#include <tf2/LinearMath/Quaternion.h>
#include <tf2_ros/transform_broadcaster.h>
#include <geometry_msgs/TransformStamped.h>
#include <turtlesim/Pose.h>

std::string turtle_name;

void poseCallBack(const turtlesim::PoseConstPtr& msg);

int main(int argc, char** argv){

    // init ros 
    ros::init(argc,argv,"my_tf2_broadcaster");
    // create node
    ros::NodeHandle private_node("~");

    //checking parameter
    if(! private_node.hasParam("turtle")){
        if(argc != 2){
            ROS_ERROR("need turtle name as argument");
            return -1;
        }
        turtle_name = argv[1];
    }
    else {
        private_node.getParam("turtle",turtle_name);
    }

    ros::NodeHandle node;
    ros::Subscriber sub = node.subscribe(turtle_name+"/pose",10,&poseCallBack);

    ros::spin();
    return 0;
}

void poseCallBack(const turtlesim::PoseConstPtr& msg){
    static tf2_ros::TransformBroadcaster _br;
    geometry_msgs::TransformStamped _transform_stamped;

    _transform_stamped.header.stamp = ros::Time::now();
    _transform_stamped.header.frame_id = "world";
    _transform_stamped.child_frame_id = turtle_name;
    _transform_stamped.transform.translation.x = msg->x;
    _transform_stamped.transform.translation.y = msg->y;
    _transform_stamped.transform.translation.z = 0.0;
    
    tf2::Quaternion q;
    q.setRPY(0,0,msg->theta);
    _transform_stamped.transform.rotation.x = q.x();
    _transform_stamped.transform.rotation.y = q.y();
    _transform_stamped.transform.rotation.z = q.z();
    _transform_stamped.transform.rotation.w = q.w();

    _br.sendTransform(_transform_stamped);
}