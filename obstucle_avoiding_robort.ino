// include the libraries
#include "AFMotor.h"
#include <Servo.h>

// Define the pins of the ultrasonic

#define echopin A1 // echo pin
#define trigpin A0 // Trigger pin

//Create servo object

Servo myservo;

// Initilize the object

const int MOTOR_1 = 1;  //back left
const int MOTOR_2 = 2;  //back right
const int MOTOR_3 = 3;  //front right
const int MOTOR_4 = 4;  //front left

AF_DCMotor motor1(MOTOR_1, MOTOR12_64KHZ); // create motor object, 64KHz pwm
AF_DCMotor motor2(MOTOR_2, MOTOR12_64KHZ); // create motor object, 64KHz pwm
AF_DCMotor motor3(MOTOR_3, MOTOR12_64KHZ); // create motor object, 64KHz pwm
AF_DCMotor motor4(MOTOR_4, MOTOR12_64KHZ); // create motor object, 64KHz pwm

// Define the variables
int distance_L, distance_F, distance_R;
long distance;

int set = 20;
 
void setup() {
  Serial.begin(9600);           // Initialize serial port
  Serial.println("Start");

  myservo.attach(10);
  myservo.write(90);

  pinMode (trigpin, OUTPUT);
  pinMode (echopin, INPUT );
  
  motor1.setSpeed(180);          // set the motor speed to 0-255
  motor2.setSpeed(180);
  motor3.setSpeed(180);
  motor4.setSpeed(180);
}

//  Main

void loop() {
 distance_F = data();
 Serial.print(distance_F);
 Serial.println(distance_F);
  if (distance_F > set){
   Serial.println("Forward");
  motor1.run(FORWARD);    // Robort is going forward
  motor2.run(FORWARD); 
  motor3.run(FORWARD); 
  motor4.run(FORWARD);
    }
    else{detect_obstucle();}
}


long data(){
  digitalWrite(trigpin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigpin, HIGH);
  delayMicroseconds(10);
  distance = pulseIn (echopin, HIGH);
  return distance / 29 / 2;
}


void compareDistance(){
  if (distance_L > distance_R){
  motor1.run(BACKWARD);   // Robort is goin left
  motor2.run(FORWARD);
  motor3.run(FORWARD); 
  motor4.run(BACKWARD); 
    delay(350);
  }
  else if (distance_R > distance_L){
  motor1.run(FORWARD);  // Robort is going Right
  motor2.run(BACKWARD); 
  motor3.run(BACKWARD); 
  motor4.run(FORWARD);
    delay(350);
  }
  else{
  motor1.run(BACKWARD);  // Robort is going backwards
  motor2.run(BACKWARD);
  motor3.run(BACKWARD); 
  motor4.run(BACKWARD); 
   delay(300);
  motor1.run(BACKWARD);   // Robort is going Left
  motor2.run(FORWARD);
  motor3.run(FORWARD); 
  motor4.run(BACKWARD); 
    delay(500);
  }
}

void detect_obstucle(){
    Serial.println("Stop");
    motor1.run(RELEASE);         // Robort is stop
    motor2.run(RELEASE);
    motor3.run(RELEASE);
    motor4.run(RELEASE);
   
    myservo.write(0);
    delay(300);
    distance_R = data();
    delay(100);
    myservo.write(170);
    delay(500);
    distance_L = data();
    delay(100);
    myservo.write(90);
    delay(300);
    compareDistance();
}
