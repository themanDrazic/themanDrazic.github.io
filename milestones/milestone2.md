# Milestone 2:


# Overview

Milestone 2 focused on two main tasks: robot that successfully circles an arbitrary set of walls (e.g. through right hand wall following
and a demonstration of a robot that does line tracking, and walls (together).  We implemented our design on top of milestone 1, which already had the line following and turning.


## Circuitry
A Schmitt trigger is a comparator circuit implemented by applying positive feedback to the noninverting input of a comparator or differential amplifier(We implemented this in lab2 with images). It is an active circuit which converts an analog input signal to a digital output signal. The IR sensor’s analog output goes to 0 as it gets further from an object. In this case, each IR sensor fed its signal into its own Schmitt trigger. The output of the trigger would go to the Arduino. 
We debugged the Schmitt trigger by hooking it up output and ground to a digital multimeter. If the sensor was within a foot of an object, we would receive a signal that was ~3.1V. Otherwise, values ranged between 20-40 mV. 
This was also more convenient for us because the Arduino has more digital than analog pins.

```c
int ledPin = 8;            	// LED connected to digital pin 13
int val = 0;

void setup()
{
  pinMode(ledPin, INPUT);  	// sets the digital pin as output
  Serial.begin(9600);
}

void loop()
{
  val = digitalRead(ledPin);   // sets the LED on
  delay(100);              	// waits for a second
  Serial.println("reading");
  Serial.println(val);
}
```
The three IR sensors were mounted on the front, the left, and the ride sides of the robot with brackets that were about 4’’ above the ground. At about a foot away, the robot was able to detect a wall. The signal was 1 for seeing a wall or 0 for not seeing a wall.  

### Wall Following: 
In order for the robot to follow the right hand wall, we implemented a wall() function that senses the front and right walls using the IR sensors.  We used analog pins to read the analog outputs of the sensors, and the robot will adjust based on the threshold it is detecting.  
```c

if(right ==HIGH)
  {
    //Serial.println(front);
    if(front ==HIGH)
    {
    Serial.println(front);
    turnLeft();
    }
    if(IRrightanalog> 550)
    {
        tiltLeft();
        IRrightanalog = analogRead(rightIRPin);
      
    }
    else if(IRrightanalog < 400)
    {

        tiltRight();
        IRrightanalog = analogRead(rightIRPin); 
    }
    moveStraight();
  }
```
If, however, the robot does not detect walls on its right side, it will do a find-wall logic that consists of turning right multiple times until it finds the wall again. 
```c

 while(right==LOW){
      turnRight();
      moveStraight();
      turnRight();
      moveStraight();
      right = digitalRead(ir_right);
    }
```
### Video for following an arbitrary set of walls 
<iframe width="560" height="315" src="https://www.youtube.com/embed/_8YjSuotA6k" frameborder="0" allow="accelerometer; autoplay; encrypted-media; gyroscope; picture-in-picture" allowfullscreen></iframe>

### Line and Wall Tracking: 
In order for the robot to traverse through the maze while following the right hand wall, we programmed the robot to check the sensor values at each intersection.  The sensors are only connected via digital pins.  If the front and right IR sensors detect high, the robot should turn left.  If only the right IR sensor is high, the robot moves forward.  Otherwise, the robot will turn right until it finds a wall to follow.  Our findwall() function is implemented as below: 
```c
void findwall(){
  if(ir_front_wall && ir_right_wall){
    Serial.println("fr and ri");
    turnLeft();
    }
  else if (ir_right_wall){
    Serial.println("ri");
    moveStraight();
    }
  else{
    Serial.println("none");
    turnRight();
    }
  }
  ```
The function findwall() is called inside our robotmove() when both line sensors detect white(which means the robot is crossing the intersection). Otherwise, the robot will just follow the line as before.  
In order to show that our robot is thinking, we added a red and a blue LED that turns on when the right and front walls are detected, respectively.  

### Video for Maze Right Hand Following:
(The robot got stuck to the mat at 0:28 because the mat wasn't even)
<iframe width="560" height="315" src="https://www.youtube.com/embed/cVWDS6Bz7cs" frameborder="0" allow="accelerometer; autoplay; encrypted-media; gyroscope; picture-in-picture" allowfullscreen></iframe>

