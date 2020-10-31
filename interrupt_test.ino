/*OpneCR code for M-wheel control

   by Brian Tu

   2020/10/31
*/

#include "motor.h"

#include "ros.h"
#include <std_msgs/Float64.h>

//ros node handler
ros::NodeHandle  nh;

void fr_A();
void fr_B();
void set(const std_msgs::Float64&);

ros::Subscriber<std_msgs::Float64> sub("pwm", set);
Motor mot_fr;

void setup() {
  Serial.begin(9600);

  mot_fr = Motor(6, 7, 8, 0, 1, fr_A, fr_B);
  
  nh.initNode();
  nh.subscribe(sub);
}

void loop() {
  mot_fr.update();
  nh.spinOnce();
  delay(100);
}

void fr_A() {
  change(mot_fr.enc, 0);
}

void fr_B() {
  change(mot_fr.enc, 1);
}


void set(const std_msgs::Float64& msg)
{
  mot_fr.setSpeed(msg.data);
}
