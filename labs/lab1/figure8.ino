#include <Servo.h>
int leftPin = A0; //left
int rightPin = A1; //right  //930 for white //1000 black

const int MotorLeft = 9; //left
const int MotorRight = 10; //right
int leftsensor;
int rightsensor;
Servo myservoleft; //left wheel
Servo myservoright; //right wheel
int threshold = 425;
int rightcount = 0;
int leftcount = 0;

void  robotmove(int leftsensor, int rightsensor){
  if(leftsensor < threshold && rightsensor < threshold){
    Serial.println("HERERERERERERERERERERERERERERERERE");
    Serial.println(leftcount);
    Serial.println(rightcount);
    stop();
    delay(500);
    if(leftcount<4){
      turnLeft();
      delay(1500);
      leftcount++;
      }
     else if(leftcount>=4 && rightcount <4){
      turnRight();
      delay(1500);
      rightcount++;
      }
     else{
      stop();
      delay(2000);
      leftcount = 0;
      rightcount = 0;
      }
    }
  //turn right
  else if (leftsensor > threshold && rightsensor < threshold){
    Serial.println("RIGHT SEES WHITE");
    tiltRight();
    /*
    while(rightsensor < threshold){
      tiltRight();
      rightsensor = analogRead(rightPin);
    }*/
    }
   //turn left
   else if (leftsensor < threshold && rightsensor > threshold){
    Serial.println("LEFT SEES WHITE");
    tiltLeft();
    /*
    while(leftsensor < threshold){
      tiltLeft();
      leftsensor = analogRead(leftPin);
    }
    */
    }
   //when see both white
  else{
    moveStraight();
  } 
}

void turnRight(){
  myservoleft.write(180);
  myservoright.write(90);
  }

void turnLeft(){
  myservoleft.write(90);
  myservoright.write(0);
  }
  
void tiltRight(){
  myservoleft.write(94);
  myservoright.write(90);
  }


void tiltLeft(){
  myservoleft.write(90);
  myservoright.write(82);
  }

void moveStraight(){
  myservoleft.write(93);
  myservoright.write(87);
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
 /*
  Serial.println("leftsensor");
  Serial.println(leftsensor);
  Serial.println("rightsensor");
  Serial.println(rightsensor);
  */
  robotmove(leftsensor,rightsensor);

}
