//Example sketch for Cytron Arduino Edubot 
//Parts required:
//CT Uno
//2Amp Motor Driver Shield
//LSS05 Auto-Calibrating Line Sensor
//More info available at http://tutorial.cytron.com.my/

//Pin declaration
int RightEn = 5;
int RightDir = 4;
int LeftEn = 6;
int LeftDir = 7;
int LeftSen = A1;
int LeftMSen = A2;
int MidSen = A3;
int RightMSen = A4;
int RightSen = A5;

void setup()
{
  //Motor Driver Pin Setup
  pinMode(RightEn,OUTPUT);
  pinMode(RightDir,OUTPUT);
  pinMode(LeftEn,OUTPUT);
  pinMode(LeftDir,OUTPUT);
  
  digitalWrite(RightDir,HIGH);
  digitalWrite(LeftDir,LOW);
  
  //LSS05 Auto-Calibrating Line Sensor Pin Setup
  pinMode(LeftSen,INPUT);
  pinMode(LeftMSen,INPUT);
  pinMode(MidSen,INPUT);
  pinMode(RightMSen,INPUT);
  pinMode(RightSen,INPUT);
}

void loop()
{
  if((digitalRead(LeftSen)==1)&&(digitalRead(LeftMSen)==1)&&(digitalRead(MidSen)==1)&&(digitalRead(RightMSen)==1)&&(digitalRead(RightSen)==1))
  {
    analogWrite(RightEn, 130);   //PWM Speed Control
    analogWrite(LeftEn, 140);   //PWM Speed Control
  }
  else if((digitalRead(LeftSen)==1)&&(digitalRead(LeftMSen)==1)&&(digitalRead(MidSen)==1)&&(digitalRead(RightMSen)==1)&&(digitalRead(RightSen)==0))
  {
    analogWrite(RightEn, 100);   //PWM Speed Control
    analogWrite(LeftEn, 140);   //PWM Speed Control
  }
  else if((digitalRead(LeftSen)==1)&&(digitalRead(LeftMSen)==1)&&(digitalRead(MidSen)==1)&&(digitalRead(RightMSen)==0)&&(digitalRead(RightSen)==0))
  {
    analogWrite(RightEn, 70);   //PWM Speed Control
    analogWrite(LeftEn, 160);   //PWM Speed Control
  }
  else if((digitalRead(LeftSen)==1)&&(digitalRead(LeftMSen)==1)&&(digitalRead(MidSen)==0)&&(digitalRead(RightMSen)==0)&&(digitalRead(RightSen)==0))
  {
    analogWrite(RightEn, 60);   //PWM Speed Control
    analogWrite(LeftEn, 200);   //PWM Speed Control
  }
  else if((digitalRead(LeftSen)==1)&&(digitalRead(LeftMSen)==0)&&(digitalRead(MidSen)==0)&&(digitalRead(RightMSen)==0)&&(digitalRead(RightSen)==0))
  {
    analogWrite(RightEn, 40);   //PWM Speed Control
    analogWrite(LeftEn, 250);   //PWM Speed Control
  }
  else if((digitalRead(LeftSen)==0)&&(digitalRead(LeftMSen)==1)&&(digitalRead(MidSen)==1)&&(digitalRead(RightMSen)==1)&&(digitalRead(RightSen)==1))
  {
    analogWrite(RightEn, 130);   //PWM Speed Control
    analogWrite(LeftEn, 90);   //PWM Speed Control
  }
  else if((digitalRead(LeftSen)==0)&&(digitalRead(LeftMSen)==0)&&(digitalRead(MidSen)==1)&&(digitalRead(RightMSen)==1)&&(digitalRead(RightSen)==1))
  {
    analogWrite(RightEn, 140);   //PWM Speed Control
    analogWrite(LeftEn, 90);   //PWM Speed Control
  }
  else if((digitalRead(LeftSen)==0)&&(digitalRead(LeftMSen)==0)&&(digitalRead(MidSen)==0)&&(digitalRead(RightMSen)==1)&&(digitalRead(RightSen)==1))
  {
    analogWrite(RightEn, 200);   //PWM Speed Control
    analogWrite(LeftEn, 60);   //PWM Speed Control
  }
  else if((digitalRead(LeftSen)==0)&&(digitalRead(LeftMSen)==0)&&(digitalRead(MidSen)==0)&&(digitalRead(RightMSen)==0)&&(digitalRead(RightSen)==1))
  {
    analogWrite(RightEn, 230);   //PWM Speed Control
    analogWrite(LeftEn, 40);   //PWM Speed Control
  }
  else if((digitalRead(LeftSen)==0)&&(digitalRead(LeftMSen)==0)&&(digitalRead(MidSen)==0)&&(digitalRead(RightMSen)==0)&&(digitalRead(RightSen)==0))
  {
    analogWrite(RightEn, 0);   //PWM Speed Control
    analogWrite(LeftEn, 0);   //PWM Speed Control
  }
}
