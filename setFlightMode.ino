#include <Servo.h> 

Servo flightModeHigh; //Create servo object
Servo flightModeLow;

int modeStatusHigh = 0;
int modeStatusLow = 0;

void setup()
{
flightModeHigh.attach(10); // attaches the servo on pin 10 to the servo object 
flightModeLow.attach(11);
}

void loop()
{
  modeStatusHigh = 1950;
  modeStatusLow = 1050;
  flightModeHigh.writeMicroseconds(modeStatusHigh); //Set flightmode to Attitude
  //flightModeLow.writeMicroseconds(modeStatusLow); //Set flightmode to Rate
  delay(3000);
}
