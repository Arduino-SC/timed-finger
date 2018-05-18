void segmentValues(){

  // load digit values from array
  datadOne = dataArraydOne[dOne];    
  datadTwo = dataArraydTwo[dTwo];

  // send values to shift register, and 7 segment display
  digitalWrite(latchPin, 0);    
  shiftOut(dataPin, clockPin, datadTwo);   
  shiftOut(dataPin, clockPin, datadOne);
  digitalWrite(latchPin, 1);
}
