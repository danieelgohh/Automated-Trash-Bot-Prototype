//defines variables for IR sensor
  int val_container;          // store analog value read from IR sensor inside the bin
  int distance_container;     // returns distance inside bin calculated in cm
  int sum_container = 0;      // variable used for calculations


// defines pin numbers for ultrasound
  int trigPin = 9;
  int echoPin = 10;

// defines variables for ultrasound
  long duration;            //time between send a receive signal
  int distance_proximity;   //returns proximity distance calculated in cm


//Pin declaration for line tracker
  int RightEn = 5;
  int RightDir = 4;
  int LeftEn = 6;
  int LeftDir = 7;          //these four variables are used for the pins connected to the movement of the DC motors during in the line tracker sequence

  int LeftSen = A1;
  int LeftMSen = A2;
  int MidSen = A3;
  int RightMSen = A4;
  int RightSen = A5;        //these five variables are for the readings from the IR sensors of the line tracker; one for each sensor


#include <Servo.h> //Servo library
#include "Shield2AMotor.h" // library for reverse DC motor movement when making a 180 degrees rotation


Shield2AMotor motor(SIGNED_MAGNITUDE); //creating the object for the DC motors that will be needed to make one of them move in reverse


Servo Rservo;  //naming servo motors for rising platform
Servo Lservo;



void setup() {

  pinMode(trigPin, OUTPUT);   // Sets the trigPin as an Output.
  pinMode(echoPin, INPUT);   // Sets the echoPin as an Input. The pair are used to calculate the time between the sent and recieved ultrasonic signal 

  //DC Motor Driver Pin Setup
  pinMode(RightEn,OUTPUT);
  pinMode(RightDir,OUTPUT);
  pinMode(LeftEn,OUTPUT);
  pinMode(LeftDir,OUTPUT);
  
  digitalWrite(RightDir,HIGH);  //as the DC motors are placed opposite each other, one is facing forward and the other is facing backwards. 
  digitalWrite(LeftDir,LOW);    //one pin is set to high and one is set to low to make them rotate in opposite directions, effectively making the wheels rotate in one direction
  
  //Auto-Calibrating Line Sensor Pin Setup
  pinMode(LeftSen,INPUT);
  pinMode(LeftMSen,INPUT);
  pinMode(MidSen,INPUT);
  pinMode(RightMSen,INPUT);
  pinMode(RightSen,INPUT);


  Serial.begin(9600);
}

void loop() {
  container_distance();            //run the function to check if the bin is full
  if (distance_container < 19) {
    delay(7000);                  //waits for a few seconds to make sure that it wasn't just detecting someone's hand or object being thrown in
    container_distance();
    if (distance_container < 19) {
      movement_to_dispose();      //if required distance is still met the bin starts moving
    }
  else
    delay(2000); //waits a few seconds before checking the distance again
  }
}

void container_distance() {                    //function that detects and calculates distance (cm) from IR sensor inside the bin to the nearest object
  // sample 10 readings
  for (int i = 0; i <= 10; i++) {
    val_container = analogRead(0);            // read the value from the IR sensor connected to pin 0
    distance_container = 12343.85 * pow(val_container, -1.15);    // calculation to convert distance to cm
    sum_container = sum_container + distance_container;
    delay(10);   // sampling interval
  }
  
  // average the 10 readings
  distance_container = sum_container/10;
  if (distance_container < 0) {
    distance_container = 1000;  //error check, cannot have negative value, the calculation will rarely calculate a negative value when the distance is too large
  }
  sum_container = 0;    // reset the value of the sum
  Serial.print("internal distance: " );    //Use print out to check sensor functionality
  Serial.print(distance_container);
  Serial.println();  
}

void movement_to_dispose() {
  analogWrite(RightEn, 200);  
  analogWrite(LeftEn, 200);      //begin moving in a straight line for a moment before running the line tracker
  delay(500);
  line_tracker();                //run the fuction for the line-tracking movement
  dispose();                     //run the fuction for the platform disposal
  digitalWrite(RightDir,HIGH);   //resetting the DC motors as using the "motor" function when rotating 180 degrees messes up the configuration and makes them move in reverse.
  digitalWrite(LeftDir,LOW);
  analogWrite(LeftEn, 0);
  analogWrite(RightEn, 0); 
  line_tracker();                //after the bot has disposed and rotated, run the line tracker function again
  motor.control(100,100);        //180 degrees rotation after making it back to the starting position
  delay(4800);
  motor.control(0,0);
  digitalWrite(RightDir,HIGH); //resetting the DC motors again after the second rotation
  digitalWrite(LeftDir,LOW);
  analogWrite(LeftEn, 0);
  analogWrite(RightEn, 0);
}


void line_tracker() {


  int reached_endpoint = 0;  //variable used to determine when the line tracker reaches the end of the track and takes the program out of the while loop
  do {
   if((digitalRead(LeftSen)==1)&&(digitalRead(LeftMSen)==1)&&(digitalRead(MidSen)==1)&&(digitalRead(RightMSen)==1)&&(digitalRead(RightSen)==1))    //this means that all 5 pins are lit and
    {                                                                                                                                              //the bin should move in a straight line
      analogWrite(RightEn, 130);   //Setting speeds for the DC motors to move in a straight line
      analogWrite(LeftEn, 140);   //One of the DC motors is slower than the other
      
      
      proximity_distance();               //run the function that calculates the proximity distance
      while (distance_proximity < 30) {   //while an object is less than 30 cm away, the movement is halted until the distance exceeds 30cm again
        analogWrite(LeftEn, 0);
        analogWrite(RightEn, 0);   
        delay(2500);
        proximity_distance();
        
      }
    }
    else if((digitalRead(LeftSen)==1)&&(digitalRead(LeftMSen)==1)&&(digitalRead(MidSen)==1)&&(digitalRead(RightMSen)==1)&&(digitalRead(RightSen)==0))
    {
      analogWrite(RightEn, 100);   //Adjusting the speeds of each motor accordingly based on which IR sensors are detecting tape and which are not
      analogWrite(LeftEn, 140);
      
      
      proximity_distance();
      while (distance_proximity < 30) {
        analogWrite(LeftEn, 0);
        analogWrite(RightEn, 0);   
        delay(2500);
        proximity_distance();
      }
    }
    else if((digitalRead(LeftSen)==1)&&(digitalRead(LeftMSen)==1)&&(digitalRead(MidSen)==1)&&(digitalRead(RightMSen)==0)&&(digitalRead(RightSen)==0))
    {
      analogWrite(RightEn, 70);   
      analogWrite(LeftEn, 160);   
      
      
      proximity_distance();
      while (distance_proximity < 30) {
        analogWrite(LeftEn, 0);
        analogWrite(RightEn, 0);   
        delay(2500);
        proximity_distance();
      }
    }
    else if((digitalRead(LeftSen)==1)&&(digitalRead(LeftMSen)==1)&&(digitalRead(MidSen)==0)&&(digitalRead(RightMSen)==0)&&(digitalRead(RightSen)==0))
    {
      analogWrite(RightEn, 60);
      analogWrite(LeftEn, 200);   
      
      
      proximity_distance();
      while (distance_proximity < 30) {
        analogWrite(LeftEn, 0);
        analogWrite(RightEn, 0);   
        delay(2500);
        proximity_distance();
      }
    }
    else if((digitalRead(LeftSen)==1)&&(digitalRead(LeftMSen)==0)&&(digitalRead(MidSen)==0)&&(digitalRead(RightMSen)==0)&&(digitalRead(RightSen)==0))
    {
      analogWrite(RightEn, 40);   
      analogWrite(LeftEn, 250); 
  
    
      proximity_distance();
      while (distance_proximity < 30) {
        analogWrite(LeftEn, 0);
        analogWrite(RightEn, 0);   
        delay(2500);
        proximity_distance();
      }
    }
    else if((digitalRead(LeftSen)==0)&&(digitalRead(LeftMSen)==1)&&(digitalRead(MidSen)==1)&&(digitalRead(RightMSen)==1)&&(digitalRead(RightSen)==1))
    {
      analogWrite(RightEn, 130);   
      analogWrite(LeftEn, 90);   
      
      
      proximity_distance();
      while (distance_proximity < 30) {
        analogWrite(LeftEn, 0);
        analogWrite(RightEn, 0);   
        delay(2500);
        proximity_distance();
      }
    }
    else if((digitalRead(LeftSen)==0)&&(digitalRead(LeftMSen)==0)&&(digitalRead(MidSen)==1)&&(digitalRead(RightMSen)==1)&&(digitalRead(RightSen)==1))
    {
      analogWrite(RightEn, 140);   
      analogWrite(LeftEn, 90);   
      
      
      proximity_distance();
      while (distance_proximity < 30) {
        analogWrite(LeftEn, 0);
        analogWrite(RightEn, 0);   
        delay(2500);
        proximity_distance();
      }
    }
    else if((digitalRead(LeftSen)==0)&&(digitalRead(LeftMSen)==0)&&(digitalRead(MidSen)==0)&&(digitalRead(RightMSen)==1)&&(digitalRead(RightSen)==1))
    {
      analogWrite(RightEn, 200);   
      analogWrite(LeftEn, 60);   
      
      
      proximity_distance();
      while (distance_proximity < 30) {
        analogWrite(LeftEn, 0);
        analogWrite(RightEn, 0);   
        delay(2500);
        proximity_distance();
      }
    }
    else if((digitalRead(LeftSen)==0)&&(digitalRead(LeftMSen)==0)&&(digitalRead(MidSen)==0)&&(digitalRead(RightMSen)==0)&&(digitalRead(RightSen)==1))
    {
      analogWrite(RightEn, 230);   
      analogWrite(LeftEn, 40);   
      
      
      proximity_distance();
      while (distance_proximity < 30) {
        analogWrite(LeftEn, 0);
        analogWrite(RightEn, 0);   
        delay(2500);
        proximity_distance();
      }
    }
    else if((digitalRead(LeftSen)==0)&&(digitalRead(LeftMSen)==0)&&(digitalRead(MidSen)==0)&&(digitalRead(RightMSen)==0)&&(digitalRead(RightSen)==0))
    {
      analogWrite(RightEn, 0);   
      analogWrite(LeftEn, 0);   
      reached_endpoint = 1;     //when all IR sensors are off, there is no more tape and the bin has reached its destination
    }
  } while (reached_endpoint != 1);
}

void proximity_distance() {
  
  digitalWrite(trigPin, LOW);                 // Clears the trigPin
  delayMicroseconds(2);  
  digitalWrite(trigPin, HIGH);               // Sets the trigPin on HIGH state for 10 micro seconds
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);        // Reads the echoPin, returns the sound wave travel time in microseconds
  distance_proximity = duration*0.034/2;    // Calculating the distance
  // Prints the distance on the Serial Monitor
  Serial.print("Proximity Distance: ");
  Serial.println(distance_proximity);  
}


void dispose() {
  delay(500);
  motor.control(100,100);     //rotating 180 degrees to have flap door face the disposal site
  delay(4800);
  motor.control(0,0);
  delay(1000);
  Servos();       // run the function for the servo motors
  delay(2000);  
}


void Servos() { 
  Rservo.attach(13);   // attaches the right-hand servo's signal pin on pin D6 and the left on pin D7
  Lservo.attach(12);
  Serial.println("Going up");
  Rservo.write(130);  //Turn clockwise at high speed. The highest clockwise speed is 180 and the highest anticlockwise speed is 0. 90 is no motion
  Lservo.write(50);   //Turn anticlockwise at high speed. The opposite orientation of the two servo motors makes the platform go up
  delay(350);
  Serial.println("Gonna stop");
  Rservo.detach();    //Stop. You can use detach function or use write(90), but some lack of precision may change this value so detaching is more convenient
  Lservo.detach();
  delay(1000);
  Serial.println("Going back in");
  delay(1000);
  Rservo.attach(13);  //Always use attach function after detach to re-connect your servo with the board
  Lservo.attach(12);
  Serial.println("Going down");
  Rservo.write(50);
  Lservo.write(130);
  delay(350);
  Serial.println("Completed first cycle");
  Rservo.detach();
  Lservo.detach();
  delay(2000);
  Serial.println("Going back in the second time");
  delay(2000);
  Rservo.attach(13);
  Lservo.attach(12);
  Serial.println("Going up for the second time");
  Rservo.write(130);
  Lservo.write(50);
  delay(350);
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
  delay(350);
  Serial.println("Completed second cycle");
  Rservo.detach();
  Lservo.detach();
  delay(2000);
}
