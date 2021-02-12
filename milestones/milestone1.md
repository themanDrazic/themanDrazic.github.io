# Milestone 1:


# Overview

Milestone 1 focused on two main tasks; the robot follows a line and completes a figure 8. Both tasks required extensive testing and required us to adjust our sensors and robot to allow the line sensors to properly detect the line.


## Follow a line

Our approach to follow a line was to use 2 line sensors. These sensors would detect if the robot goes over the white line and adjusts back to where the sensors are on the black part of the route. Our sensors are positioned in the front portion of the robot where they are sensing the black part of the area.

```c
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
```
In terms of reacting to a white line our robot had three cases: No white detected, left sensor detects white and right sensor detects white. If the sensors do not detect any white line it continues on its path. If the left sensor detects white the robot increases the speed of the right motor and slows the left motor which allows the robot to keep moving while it adjusts back to the line. The same is true for if the right sensor detects white. The left motor will increase and the right motor will decrease and continue moving straight once both sensors detect only black area. We kept the motors moving to allow the robot to quickly correct itself and avoid a zig-zag problem where the robot over compensates for detecting the line.
```c
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
```
## Video
<iframe width="560" height="315" src="https://www.youtube.com/embed/8wf_05XcU9A" frameborder="0" allow="accelerometer; autoplay; encrypted-media; gyroscope; picture-in-picture" allowfullscreen></iframe>


## Completing a figure 8

The next part of the milestone was to have the robot complete a figure 8. Using the previous line following code we added another set of conditions for the robot to follow. If the 2 line sensors saw a white line, which is a corner in the figure 8, the robot would turn for 1.5 seconds and continue to follow the line. We created a counter for 4 left turns and 4 right turns. After 4 left turns the robot would complete the other part of the 8 by doing right turns. For turns we would turn off the other motor to complete the turn.
```c
void turnRight(){
  myservoleft.write(180);
  myservoright.write(90);
  }

void turnLeft(){
  myservoleft.write(90);
  myservoright.write(0);
  }
```
Left turn part
```c
else if (leftsensor < threshold && rightsensor > threshold){
   Serial.println("LEFT SEES WHITE");
   tiltLeft();
   }

```

Right turn part
```c
else if (leftsensor > threshold && rightsensor < threshold){
    Serial.println("RIGHT SEES WHITE");
    tiltRight();
    }
```
Overall figure 8 program
```c
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
```
## Video
<iframe width="560" height="315" src="https://www.youtube.com/embed/NkZulQDeWco" frameborder="0" allow="accelerometer; autoplay; encrypted-media; gyroscope; picture-in-picture" allowfullscreen></iframe>
