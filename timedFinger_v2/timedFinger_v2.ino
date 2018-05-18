/*

 Timed Finger v2
 
 Runs a servo motor to trigger to a certain angle over a certain interval.
 This is used to achieve time-lapse photography on cameras which do not
 have the time-laps function. Position the servo using the potentiometer
 so it pokes the trigger on the camera and shoot away.
 
 The sketch uses two Kingbright SC56/11HWA 7 segment character displays 
 to display the time for the time-lapse interval. This interval is set
 using a rotary encoder.
 
 created 24 Oct 2014
 by Daniel Jansson
 http://www.switchandlever.com
 
 For more information regarding this sketch, view the video at 
 http://www.youtube.com/SwitchAndLever
 
 
 The Timed Finger relies on the following libraries:
 
 Encoder Library, for reading the rotary encoder, available
 from: https://www.pjrc.com/teensy/td_libs_Encoder.html
 
 Average LIbrary, for cleaning up the potentiometer values,
 available from: http://hacking.majenko.co.uk/libs/average
 
 As well as the shiftOut code for shifting out the values 
 to the shift registers, available from:
 http://arduino.cc/en/Reference/shiftOut
 
 */




#define ENCODER_DO_NOT_USE_INTERRUPTS
#include <Encoder.h>
Encoder myEnc(7, 8);      // encoder left leg to pin 7, right leg to 8, middle to GND

#include <Servo.h>        // built in servo library to control the servo motor
Servo myservo; 

#include <Average.h>      // averaging library to clean up the potentiometer values
#define CNT 20
int d[CNT];


//Pin connected to ST_CP of 74HC595
int latchPin = 10;
//Pin connected to SH_CP of 74HC595
int clockPin = 12;
////Pin connected to DS of 74HC595
int dataPin = 11;

// value to control the left seven segment display
// from here refered to as dOne and dTwo, instead of left and right
int dOne = 0;    // left
int dTwo = 1;    // right

//holders for data you're going to pass to shifting function
byte datadOne;
byte datadTwo;
byte dataArraydOne[10];
byte dataArraydTwo[10];

// rotary encoder values
long position  = -999;
long fourPos = 0;
long oldPos = 0;
int timeCounter = 1;

// analog pin for potentiometer
int potPin = 0;

// button to control when setup is done
int buttonPin = 2;
int buttonState = 0;
int lastButtonState = 0;
int buttonCounter = 0;
int setupActivated = 0;

void setup() {
  Serial.begin(9600);

  //set pins to output because they are addressed in the main loop
  pinMode(latchPin, OUTPUT);


  //HEX values to control the first 7 segment display
  dataArraydOne[0] = 0x7E; //01111110, zero
  dataArraydOne[1] = 0x48; //01001000, one
  dataArraydOne[2] = 0x3D; //00111101, two
  dataArraydOne[3] = 0x6D; //01101101, three
  dataArraydOne[4] = 0x4B; //01001011, four
  dataArraydOne[5] = 0x67; //01100111, five
  dataArraydOne[6] = 0x77; //01110111, six
  dataArraydOne[7] = 0x4C; //01001100, seven
  dataArraydOne[8] = 0x7F; //01111111, eight
  dataArraydOne[9] = 0x4F; //01001111, nine

  //HEX values to control the second 7 segment display
  dataArraydTwo[0] = 0x7E; //01111110, zero
  dataArraydTwo[1] = 0x48; //01001000, one
  dataArraydTwo[2] = 0x3D; //00111101, two
  dataArraydTwo[3] = 0x6D; //01101101, three
  dataArraydTwo[4] = 0x4B; //01001011, four
  dataArraydTwo[5] = 0x67; //01100111, five
  dataArraydTwo[6] = 0x77; //01110111, six
  dataArraydTwo[7] = 0x4C; //01001100, seven
  dataArraydTwo[8] = 0x7F; //01111111, eight
  dataArraydTwo[9] = 0x4F; //01001111, nine


  // sets the initial time on display to 01 and pushes the values out    
  datadOne = dataArraydOne[0];    
  datadTwo = dataArraydTwo[1];

  digitalWrite(latchPin, 0);
  shiftOut(dataPin, clockPin, datadTwo);   
  shiftOut(dataPin, clockPin, datadOne);
  digitalWrite(latchPin, 1);

  // attach servo to digital pin 6
  myservo.attach(6);

  // set button as input
  pinMode(buttonPin, INPUT);


}



void loop() {

  pollEncoder();                          // read value from rotary encoder and update 7 segment displays

  potRead();                              // read value from potentiometer and feed it to the servo angle

  timeLapse();                            // run timelapse

}






