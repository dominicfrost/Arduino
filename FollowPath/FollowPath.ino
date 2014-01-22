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


void setup(){
  Serial.begin(9600);
  rightServo.attach(9);
  leftServo.attach(10);
}

// high is white
// low is black
void loop(){
  Serial.println(analogRead(leftSensor));
  if (analogRead(leftSensor) > 120) {
    //turn back onto black line
    leftServo.write(10);
    rightServo.write(170);
  } else {
     //stay on course
     leftServo.write(170);
     rightServo.write(10); 
  }

}
