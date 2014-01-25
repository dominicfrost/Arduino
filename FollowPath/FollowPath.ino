/* Motor Core

  This code for the Arduino Robot's motor board
  is the stock firmware. program the motor board with 
  this sketch whenever you want to return the motor
  board to its default state.
  
*/

#include <Servo.h> 

Servo rightServo;
Servo leftServo;

int leftSensor = A0;
int rightSensor = A1;
int pingPin = 11;

int inches = 0;
int duration = 0;

int rightWheelForward = 1440;
int rightWheelStop = 1497;
int rightWheelSlow = 1472;

int leftWheelForward = 1530;
int leftWheelStop = 1482;
int leftWheelSlow = 1505;

int rightWhiteThreshold = 200;
int leftWhiteThreshold = 130;

int leftValIn;
int rightValIn;

boolean trackState = false; // left

void setup(){
  Serial.begin(9600);
  rightServo.attach(9);
  leftServo.attach(10);
}

// high is white
// low is black
void loop(){
  leftValIn = analogRead(leftSensor);
  rightValIn = analogRead(rightSensor);
  
  Serial.print("left sensor: "); // white: 148 black: 118
  Serial.println(leftValIn);
  Serial.print("right sensor: "); // white: 218 black: 165
  Serial.println(rightValIn);
  
  pinMode(pingPin, OUTPUT);
  digitalWrite(pingPin, LOW);
  delayMicroseconds(2);
  digitalWrite(pingPin, HIGH);
  delayMicroseconds(5);
  digitalWrite(pingPin, LOW);
  
  pinMode(pingPin, INPUT);
  duration = pulseIn(pingPin, HIGH);

  // convert the time into a distance
  inches = microsecondsToInches(duration);
  
  //only move if there is nothing in front of the PING
//  if(inches > 2) {
    
//    leftValIn = 0;
//    rightValIn = 999;
    if (leftValIn > rightWhiteThreshold && rightValIn < rightWhiteThreshold) { 
      // left sensor reads white, right sensor reads black - turn right
      Serial.println("Turn Right");
      trackState = false; // on left side of track
      leftServo.writeMicroseconds(leftWheelForward);
      rightServo.writeMicroseconds(rightWheelSlow);
    } else if (rightValIn > rightWhiteThreshold && leftValIn < rightWhiteThreshold) { 
      // right sensor reads white, left sensor reads black - turn left
      Serial.println("Turn Left");
      trackState = true; // on right side of track
      leftServo.writeMicroseconds(leftWheelSlow);
      rightServo.writeMicroseconds(rightWheelForward);
    } else if (rightValIn > rightWhiteThreshold && leftValIn > rightWhiteThreshold) { 
      // right sensor reads white, left sensor reads white
      if(!trackState) { // turn right
        leftServo.writeMicroseconds(leftWheelForward);
        rightServo.writeMicroseconds(rightWheelStop);
      } else { // turn left
        leftServo.writeMicroseconds(leftWheelStop);
        rightServo.writeMicroseconds(rightWheelForward);
      }
    } else if (rightValIn < rightWhiteThreshold && leftValIn < rightWhiteThreshold) { 
      // right sensor reads black, left sensor reads black got straight
      leftServo.writeMicroseconds(leftWheelForward);
      rightServo.writeMicroseconds(rightWheelForward);
    }
//  } else {
//      rightServo.writeMicroseconds(rightWheelStop);
//      leftServo.writeMicroseconds(leftWheelStop);
//  }
  
}

int microsecondsToInches(int microseconds)
{
  return microseconds / 74 / 2;
}
