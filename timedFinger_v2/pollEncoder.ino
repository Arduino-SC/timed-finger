void pollEncoder(){

  if(buttonCounter == 1){    // trigger only if button has been pushed once

    long newPos = myEnc.read();    // read the encoder and store value
    if (newPos != position) {      // trigger only when the position changes
      position = newPos;           // set position to new position

      fourPos = position % 4;    // spits out a 0 if number is divisable by 4, as encoder updates four times per step

      if(fourPos == 0){      // do this every step

        if(position/4 > oldPos){    // what happens when there's a plus step
          if(timeCounter != 99){    // only trigger if the value is different than 99
            Serial.println("plus");  // increment timer here

            dTwo++;                  // increase dTwo by one
            timeCounter++;           // increase the time by one

            int tenStep = dTwo % 10;   // check if the value is divisable by 10

              if (tenStep == 0){      // trigger if it is
              dTwo = 0;               // reset dTwo
              dOne++;                 // increase value of dOne
            }
          }
          oldPos = position/4;      // reset the position before exiting if statement
        }

        if(position/4 < oldPos){    // what happens when there's a minus step
          if(timeCounter != 1){    // keep the value above 1
            Serial.println("minus");  // decrement timer here

            dTwo--;                  // decrease dTwo by one
            timeCounter--;           // decrease the time by one

            int tenStep = dTwo % 10;   // check if the value is divisable by 10

              if (tenStep == 0){      // trigger if it is
              dTwo = 0;              // reset dTwo
              segmentValues();      // send values to display before lowering dOne
              dOne--;               // decrease dOne, but only after values have been sent, otherwise display will show 00

              goto skipSegmentPush;    // bypass 
            }
          }
          oldPos = position/4;      // reset the position before exiting if statement
        }

        segmentValues();    // send values to display
skipSegmentPush:    // bypassed sending the values to display, since that's already done
        delay(0);      // because the goto needed something to do to function properly
      }
    }
  }
}

