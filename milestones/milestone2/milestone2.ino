#include <Servo.h>
int leftPin = A0; //left
int rightPin = A1; //right  //930 for white //1000 black
int rightIRPin = A3; // right IR sensor pin

const int MotorLeft = 9; //left
const int MotorRight = 10; //right
int leftsensor;
int rightsensor;
int rightIRsensor;
Servo myservoleft; //left wheel
Servo myservoright; //right wheel
int threshold = 450;

//wall detection
//HIGH for seeing wall
//LOW for no wall
int ir_front =8;
int ir_right =12;
int ir_left = 13;
int ir_front_wall, ir_right_wall, ir_left_wall;

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



void wall(int front, int right, int left, int IRrightanalog)
{
  //case 1 follow right wall
  //Serial.println(IRrightanalog);
  //Serial.println(right);
   //moveStraight();
  if(right ==HIGH)
  {
    //Serial.println(front);
    if(front ==HIGH)
    {
      Serial.println(front);
      //moveback();
    //delay(100);
    //moveStraight();
    delay(250);
    turnLeft();
    delay(1600);
    }
    if(IRrightanalog> 550)
    {
      //while(IRrightanalog>550)
      //{
        tiltLeft();
        delay(100);
        IRrightanalog = analogRead(rightIRPin);
      //}
      
    }
    else if(IRrightanalog < 400)
    {
      //while(IRrightanalog<300)
      //{
        tiltRight();
        delay(100);
        IRrightanalog = analogRead(rightIRPin);
      //}
      
    }
    moveStraight();
    //Serial.println("right wall is seen");
    //Serial.println(right);
  }
  
  //case 2 right turn
  else if(right ==LOW)
  {
    Serial.println("walls are gone");
    Serial.println(right);
    //delay(200);
    //turnRight();
    //delay(1500);
    //moveStraight();
    while(right==LOW){
      turnRight();
      delay(750);
      moveStraight();
      delay(300);
      turnRight();
      delay(750);
      moveStraight();
      delay(300);
      right = digitalRead(ir_right);
    }
  }
  //case 3 left turn 
//  else if(front == HIGH && right == HIGH && left == LOW)
//  {
//    
//  }
}
void tiltRight(){
  myservoleft.write(180);
  myservoright.write(85);
  
  }

void turnRight()
{
  myservoleft.write(180);
  myservoright.write(90);
  //delay(1000);
}
void turnLeft()
{
  myservoleft.write(90);
  myservoright.write(0);
  //delay(1000);
}
void tiltLeft(){
  myservoleft.write(95);
  myservoright.write(0);
  }

void moveStraight(){
  myservoleft.write(140);
  myservoright.write(40);
  }
void moveback()
{
  myservoleft.write(40);
  myservoright.write(140);
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
  
  pinMode(ir_front, INPUT);
  pinMode(ir_right, INPUT);
  pinMode(ir_left, INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  //pinMode(OutPin, OUTPUT);
  leftsensor  = analogRead(leftPin);
  rightsensor = analogRead(rightPin);
  rightIRsensor = analogRead(rightIRPin);

  
  ir_front_wall = digitalRead(ir_front);
  ir_right_wall = digitalRead(ir_right);
  ir_left_wall = digitalRead(ir_left);
  
  //robotmove(leftsensor,rightsensor);
  //Serial.println(ir_right_wall);
  wall(ir_front_wall,ir_right_wall,ir_left_wall,rightIRsensor);

}
