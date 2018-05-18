int servoPos;

void potRead(){

  buttonState = digitalRead(buttonPin);    // read the state of the button


    if(buttonState == 0 && setupActivated == 0){  // keep potentiometer active until button has been pressed
    int potVal = analogRead(potPin);    // read the potentiometer

    int potAvg = rollingAverage(d,CNT,potVal);    // average the reading, as it may be noisy

    servoPos = map(potAvg,0,1023,0,180);    // map the averaged reading to fit into the range of the servo

    myservo.write(servoPos);    // write position to servo
  }

  if(buttonState != lastButtonState){     // check if button has been pushed
    if(buttonState == 1){    // if it's currently being pushed increase the buttonCounter
      buttonCounter++;
    }
  }

  if(buttonCounter == 1){                      // when button is pressed
    setupActivated = 1;                      // change value of setupActivated, to signify that setup is done
    myservo.write(servoPos - 20);              // retract servo horn slightly to release button
  }

  lastButtonState = buttonState;            // reset the value of the button, so it can be read again

}

















