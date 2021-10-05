#include <Servo.h> //includes the servo library
#include <cvzone.h>
#define motor_A_direction 0 //change the value into 1 for opposite direction
#define motor_B_direction 0 //change the value into 1 for opposite direction
#define ldr1 A0 // set ldr 1 Analog input pin of East ldr as an integer
#define ldr2 A1 // set ldr 2 Analog input pin of West ldr as an integer
#define potPin A2 // potentiometer to control the blade

byte pos = 90; // initial position of the Horizontal movement controlling servo motor
int tolerance = 15; // allowable tolerance setting - so solar servo motor isn't constantly in motion
int val = 0;
int mpin[6] = {3, 4, 5, 7, 8, 11};
SerialData serialData(1, 1); //(numOfValsRec,digitsPerValRec)
int valsRec[1]; // array of int with size numOfValsRec

Servo axleServo;
Servo solarServo;
Servo bladeServo;

bool turnLeft = false;

void setup()
{
  //Serial.begin(9600);
  serialData.begin(9600);
  pin_define(); //direction setting
  for (byte i = 0; i < 6; i++) pinMode(mpin[i], OUTPUT);
  pinMode(13, OUTPUT);
  pinMode(ldr1, INPUT); //set East ldr pin as an input
  pinMode(ldr2, INPUT); //set West ldr pin as an input

  axleServo.attach(6);
  solarServo.attach(9);
  bladeServo.attach(10);
  axleServo.write(pos); // writing the starting position of the horizontal movement servo motor
  solarServo.write(pos);
  bladeServo.write(pos);
  delay(1000);

}

void loop()
{
  serialData.Get(valsRec);
  if (valsRec[0] == 0)
  {
    axleServo.write(pos);
  }
  else if (valsRec[0] == 1 && turnLeft == false)
  {
    motor(250, -250);  //Right
    axleServo.write(0);
    delay(2000);
    turnLeft == true;
  }
  else if (valsRec[0] == 1 && turnLeft == true)
  {
    motor(-250, 250);  //Left
    axleServo.write(180);
    delay(2000);
    turnLeft == false;
  }
  val = analogRead(potPin);            // reads the value of the potentiometer (value between 0 and 1023)
  val = map(val, 0, 1023, 0, 180);     // scale it to use it with the servo (value between 0 and 180)
  bladeServo.write(val);             // Controlling the blade servo....
  controlSolar();// Control the Solar Tracker
  motor(250, 250);  //Forward
}
