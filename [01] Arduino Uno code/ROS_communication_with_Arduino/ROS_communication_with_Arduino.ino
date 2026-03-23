#include <ros.h>
#include <std_msgs/Int32.h>

//here is our Node handle
ros::NodeHandle nh;
//this message is sent back
std_msgs::Int32 outputMessage;
//The publisher from arduino side. It publishes a topic named "info_back". The python subscriber subscribes to this "info_back"
//topic and shows the output. 
ros::Publisher pub("info_back", &outputMessage);

void callBackFunction(const std_msgs::Int32 &inputMessage) {
  outputMessage.data = 2*inputMessage.data; 
  pub.publish(&outputMessage); 
}



//the arduino subscriber which subscribes to the "information" topic. 
ros::Subscriber<std_msgs::Int32> sub("information", &callBackFunction); 




void setup() {
  nh.initNode(); 
  nh.advertise(pub); 
  nh.subscribe(sub);
}

void loop() {

  nh.spinOnce(); 
  delay(1); 
  
}
