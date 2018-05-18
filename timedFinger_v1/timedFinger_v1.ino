/*

 Timed Finger v1
 
 Runs a servo motor to trigger to a certain angle over a certain interval.
 This is used to achieve time-lapse photography on cameras which do not
 have the time-laps function. The angle needs to be set up in code, and
 does not have any external inputs. 
 
 created 24 Oct 2014
 by Daniel Jansson
 http://www.switchandlever.com
 
 For more information regarding this sketch, view the video at 
 http://www.youtube.com/SwitchAndLever
 
 */


#include <Servo.h>         // built in servo library to control the servo motor
Servo myservo;


void setup() 
{ 
  // attach servo to digital pin 6
  myservo.attach(6);
} 

void loop() 
{ 

  myservo.write(90);                  // change this incrementally until it triggers camera button
  delay(1000);                        // how long to keep the servo in position, basically how long the camera needs the button pressed for

  // uncomment below once the right angle has been set

  //myservo.write(X);               // change value of X to something slightly less than the previous servo angle to move servo away from button
  //delay(9000);                    // this number, together with previous delay added, makes for the total time between each photo

} 




