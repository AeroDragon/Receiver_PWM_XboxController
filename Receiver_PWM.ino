// Controlling a servo position using a potentiometer (variable resistor) 
// by Michal Rinott <http://people.interaction-ivrea.it/m.rinott> 

#include <Servo.h> 
 
Servo throttle;  // create servo object to control a servo 
Servo yaw;
Servo roll;
Servo pitch;
 
int throttlePot = 0;  // analog pin used to connect the potentiometer
int yawPot = 1;
int rollPot = 2;
int pitchPot = 3;

unsigned long  throttleSpeed;    // variable to read the value from the analog pin 
unsigned long  yawSpeed;
unsigned long  rollSpeed;
unsigned long  pitchSpeed;

int throttle_read = 2;
int yaw_read = 3;
int pitch_read = 4;
int roll_read = 5;

#define cmdLength 4
int transmitter_Commands[cmdLength];
//int ledpin = 4;
 
void setup() 
{ 
  throttle.attach(9);  // attaches the servo on pin 9 to the servo object 
  yaw.attach(10);
  roll.attach(11);
  pitch.attach(6);
  //throttle.writeMicroseconds(1050);   //Arm motors at 1050
 // pinMode(ledpin,OUTPUT);
  pinMode(throttle_read, INPUT);
  pinMode(yaw_read, INPUT);
  pinMode(pitch_read, INPUT);
  pinMode(roll_read, INPUT);
  Serial.begin(9600);  
} 
 
void loop() 
{ 
  //readSerial();
  //convertCommands();
  //sendCommands();
  //Serial.flush();
  //Serial.println(transmitter_Commands[0]);
  //led();
//  delay(5);
  getThrottle();
  getYaw(); 
  getRoll();
  getPitch(); 

//throttleSpeed = pulseIn(throttle_read, HIGH);
//yawSpeed = pulseIn(yaw_read, HIGH);
//pitchSpeed = pulseIn(pitch_read, HIGH);
//rollSpeed = pulseIn(roll_read, HIGH);
sendCommands();
}

void sendCommands()
{
  throttle.writeMicroseconds(throttleSpeed); 
  delay(50);
  yaw.writeMicroseconds(yawSpeed);
  delay(50);
  pitch.writeMicroseconds(pitchSpeed);
  delay(50);
  roll.writeMicroseconds(rollSpeed);  
  delay(50);
}
void convertCommands()
{
  throttleSpeed = map(transmitter_Commands[0], 0, 127, 1000, 2000);
  yawSpeed = map(transmitter_Commands[1], 0, 127, 1000, 2000);
  pitchSpeed = map(transmitter_Commands[2], 0, 127, 1000, 2000);
  rollSpeed = map(transmitter_Commands[3], 0, 127, 1000, 2000);
}

void led()
{
  if (throttleSpeed >= 100 )
  {
    //digitalWrite(ledpin,HIGH);
  }
  else
 {
   //digitalWrite(ledpin,LOW);
 }  
}

void readSerial()
{
  while (Serial.available() > 0) {
    for(int i=0; i<cmdLength-1; i++)
    {
      transmitter_Commands[i] = (byte)Serial.read();
    }
  }
}

void getThrottle()
{
  throttleSpeed = analogRead(throttlePot);            // reads the value of the potentiometer (value between 0 and 1023) 
  throttleSpeed = map(throttleSpeed, 0, 630, 800, 2280);
  //throttleSpeed = map(throttleSpeed, 0, 630, 484, 2425);
  //throttleSpeed = map(throttleSpeed, 0, 545, 706, 2177);     // scale it to use it with the servo (value between 1000 and 2000) 
  if (throttleSpeed < 1000){
    throttleSpeed = 1000;
  }
  throttle.writeMicroseconds(throttleSpeed);                  // sets the servo position according to the scaled value 
  delay(50);                           // waits for the servo to get there
  Serial.println(throttleSpeed);
}

void getYaw()
{
  yawSpeed = analogRead(yawPot);
  yawSpeed = map(yawSpeed, 0, 630, 1000, 2000);     // scale it to use it with the servo (value between 1000 and 2000) 
  yaw.writeMicroseconds(yawSpeed);                  // sets the servo position according to the scaled value 
  delay(50);
}

void getRoll()
{
  rollSpeed = analogRead(rollPot);
  rollSpeed = map(rollSpeed, 0, 630, 1000, 2000);     // scale it to use it with the servo (value between 1000 and 2000) 
  roll.writeMicroseconds(rollSpeed);                  // sets the servo position according to the scaled value 
  delay(50);
}

void getPitch()
{
  pitchSpeed = analogRead(pitchPot);
  pitchSpeed = map(pitchSpeed, 0, 630, 1000, 2000);     // scale it to use it with the servo (value between 1000 and 2000) 
  pitch.writeMicroseconds(pitchSpeed);                  // sets the servo position according to the scaled value 
  delay(50);
}
