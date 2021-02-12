#include <Servo.h>
int leftPin = A0; //left
int rightPin = A1; //right  //930 for white //1000 black

const int MotorLeft = 9; //left
const int MotorRight = 10; //right
int leftsensor;
int rightsensor;
Servo myservoleft; //left wheel
Servo myservoright; //right wheel
int threshold = 450;

void  robotmove(int leftsensor, int rightsensor){
  if (leftsensor > threshold && rightsensor > threshold){
    moveStraight();
  } 
  //turn right
  else if (leftsensor > threshold && rightsensor < threshold){
    while(rightsensor < threshold){
      tiltRight();
      rightsensor = analogRead(rightPin);
    }
    }
   //turn left
   else if (leftsensor < threshold && rightsensor > threshold){
    while(leftsensor < threshold){
      tiltLeft();
      leftsensor = analogRead(leftPin);
    }
    }
  else{
    moveStraight();
    }
  }
  
void tiltRight(){
  myservoleft.write(180);
  myservoright.write(85);
  }


void tiltLeft(){
  myservoleft.write(95);
  myservoright.write(0);
  }

void moveStraight(){
  myservoleft.write(140);
  myservoright.write(40);
  }

void stop(){
  myservoleft.write(90);
  myservoright.write(90);
  }
 
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  myservoleft.attach(9);
  myservoright.attach(10);
}

void loop() {
  // put your main code here, to run repeatedly:
  //pinMode(OutPin, OUTPUT);
  leftsensor  = analogRead(leftPin);
  rightsensor = analogRead(rightPin);
  robotmove(leftsensor,rightsensor);
  /*
  if(leftsensor < 910 && rightsensor > 930)
  {
    myservoleft.write(90);
    myservoright.write(90);
    delay(1000);
    myservoleft.write(90+20);
    myservoright.write(90-40);
    delay(2000);
    //leftsensor  = analogRead(OutPin);
    //rightsensor = analogRead(OutPin2);
    Serial.println("leftsensorwhite");
  }
  else if(leftsensor > 910 && rightsensor< 930)
  {
    myservoleft.write(90);
    myservoright.write(90);
    delay(1000);
    myservoleft.write(120);
    myservoright.write(75);
    //leftsensor  = analogRead(OutPin);
    //rightsensor = analogRead(OutPin2);
    Serial.println("righttsensorwhite");
           
  }
  else{
    Serial.println("straight");
    myservoleft.write(90);
  myservoright.write(0);
  }

  ////////STRAIGHT//////////
  /*myservoleft.write(100);
  myservoright.write(75);
  delay(3000); 
  //RIGHT TURN
  myservoleft.write(100); 
  myservoright.write(90);
  delay(1400);*/
  ////////////////////////
  
  
 
  //Serial.println(analogRead(OutPin2));
  //delay(1000);
}
