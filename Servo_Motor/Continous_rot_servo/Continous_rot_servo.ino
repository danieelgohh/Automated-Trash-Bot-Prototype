//This code is to demonstrate the use of a continuous rotation servo motor with its different functions
























































































































































































































































































































































//Refer to surtrtech.com to understand further

#include <Servo.h> //Servo library

Servo Rservo;  //Servo name is Rservo and Lservo
Servo Lservo;  

void setup() {
  Rservo.attach(13);  // attaches the servo signal pin on pin D6
  Lservo.attach(12);
}
  
void loop() {
  Serial.begin(9600);
  Serial.println("Going up");// display on the serial the signal value
  Rservo.write(130); //Turn clockwise at high speed
  Lservo.write(50);
  delay(400);
  Serial.println("Gonna stop");
  Rservo.detach();//Stop. You can use detach function or use write(x), as x is the middle of 0-180 which is 90, but some lack of precision may change this value
  Lservo.detach();
  delay(2000);
  Serial.println("Going back in");
  delay(2000);
  Rservo.attach(13);//Always use attach function after detach to re-connect your servo with the board
  Lservo.attach(12);
  Serial.println("Going down");//turn left with high speed
  Rservo.write(50);
  Lservo.write(130);
  delay(400);
  Serial.println("stopping forever");
  Rservo.detach();//Stop
  Lservo.detach();
  delay(2000);
  Serial.println("Going back in the second time");
  delay(2000);
  Rservo.attach(13);
  Lservo.attach(12);
  Serial.println("Going up for the second time");
  Rservo.write(130);
  Lservo.write(50);
  delay(400);
  Serial.println("Gonna stop");
  Rservo.detach();
  Lservo.detach();
  delay(2000);
  Serial.println("Going back in again");
  delay(2000);
  Rservo.attach(13);
  Lservo.attach(12);
  Serial.println("Going down for the last time");
  Rservo.write(50);
  Lservo.write(130);
  delay(400);
  Serial.println("Stopping forever AGAIN");
  Rservo.detach();
  Lservo.detach();
  delay(20000000000000);
  


//myservo.write(92); //Used in the tutorial video, 92 was my stop value 
      
}
