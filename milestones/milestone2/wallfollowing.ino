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
int ir_front =8;
int ir_right =12;
int ir_left = 13;
int ir_front_wall, ir_right_wall, ir_left_wall;




void turnBackwards(){
  myservoleft.write(180);
  myservoright.write(90);
  delay(3000);
  }
   
void turnRight(){
  myservoleft.write(180);
  myservoright.write(90);
  delay(1500);
  }

void turnLeft(){
  myservoleft.write(90);
  myservoright.write(0);
  delay(1750);
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
  myservoright.write(85);
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
void findwall(){
  if(ir_front_wall && ir_right_wall){
    Serial.println("fr and ri");
    turnLeft();
    }
  else if (ir_right_wall){
    Serial.println("ri");
    moveStraight();
    delay(100);
    }
  else{
    Serial.println("none");
    turnRight();
    }
  }
void  robotmove(int leftsensor, int rightsensor){
  if(leftsensor < threshold && rightsensor < threshold){
    stop();
    delay(10);
    Serial.println("AT INTERSECTION");
    findwall();
  }
  //turn right
  else if (leftsensor > threshold && rightsensor < threshold){
    Serial.println("RIGHT SEES WHITE");
    tiltRight();
    }
   //turn left
   else if (leftsensor < threshold && rightsensor > threshold){
    Serial.println("LEFT SEES WHITE");
    tiltLeft();
    }
   //when see both white
  else{
    moveStraight();
  } 
}


void loop() {
  ir_front_wall = digitalRead(ir_front);
  ir_right_wall = digitalRead(ir_right);
  ir_left_wall = digitalRead(ir_left);
  robotmove(leftsensor,rightsensor);

}
