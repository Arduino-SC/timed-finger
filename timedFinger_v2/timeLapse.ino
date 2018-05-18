int pushDelay = 1000;    // how long the camera trigger is pushed, may need to be tweaked depending on camera

void timeLapse(){

  if(buttonCounter >= 2){      // if the button has been pushed twice, or more, start the timelapse

    myservo.write(servoPos);    // move servo horn to push button
    delay(pushDelay);                // keep horn in position for one second

    myservo.write(servoPos - 20);  // retract servo horn slightly to release button
    delay((timeCounter * 1000) - pushDelay); // wait for the set amount of time, minus time to push button

  }

}






