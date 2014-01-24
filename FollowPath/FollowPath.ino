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


void setup(){
  Serial.begin(9600);
  rightServo.attach(9);
  leftServo.attach(10);
}

// high is white
// low is black
void loop(){
  Serial.print("left sensor: "); // white: 153 black: 91
  Serial.println(analogRead(leftSensor));
  Serial.print("right sensor: "); // white: 211 black: 113
  Serial.println(analogRead(rightSensor));
  
  // left sensor reads white - turn right
  if (analogRead(leftSensor) > 125) {
    rightServo.write(95);
  } else { // stay on course
    rightServo.write(85);
  }
  
  
  // right sensor reads white - turn right
  if (analogRead(rightSensor) > 180) {
    leftServo.write(85);
  } else { // stay on course
    leftServo.write(95);
  }
  
}
