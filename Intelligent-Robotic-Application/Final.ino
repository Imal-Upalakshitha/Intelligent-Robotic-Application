//Libraries
#include <Servo.h>
//Motor
#define ENA 11
#define ENB 10
#define IN1 8
#define IN2 9
#define IN3 13
#define IN4 12

//IR Sensors
#define IR_LEFT_PIN 0
#define IR_RIGHT_PIN 2
//#define IR_MIDDLE_Back_PIN 3
#define IR_MIDDLE_Front_PIN 4

//Ultra Sonic Sensor
const int trigPin = 5;
const int echoPin = 6;

//Indicating LEDs
#define LED_LEFT A0
#define LED_MIDDLE_LEFT A1
#define LED_MIDDLE_RIGHT A2
#define LED_RIGHT A3

int A=0;


Servo servoA;

void setup() {

  //IR sensors
  pinMode(IR_LEFT_PIN, INPUT);
  //pinMode(IR_MIDDLE_Back_PIN, INPUT);
  pinMode(IR_MIDDLE_Front_PIN, INPUT);
  pinMode(IR_LEFT_PIN, INPUT);

  //Serial output
  Serial.begin(9600);

  //Indicating LEDs
  pinMode(LED_LEFT, OUTPUT);
  pinMode(LED_MIDDLE_LEFT, OUTPUT);
  pinMode(LED_MIDDLE_RIGHT, OUTPUT);
  pinMode(LED_RIGHT, OUTPUT);

  //Sonar trig pin
  pinMode(trigPin, OUTPUT);
  
  // Sonar echo pin
  pinMode(echoPin, INPUT);

  //Servo
  servoA.attach(7);
  servoA.write(0);
}

void loop() {


 servoA.write(0);

  long duration;
  // Variable to store the distance:
  int distance;

  int val = 1;

  //IR Sensor
  int left = digitalRead(IR_LEFT_PIN);
  //int middleBack = digitalRead(IR_MIDDLE_Back_PIN);
  int middleFront = digitalRead(IR_MIDDLE_Front_PIN);
  int right = digitalRead(IR_RIGHT_PIN);

  //Sonar sensor
  digitalWrite(trigPin, LOW);
  delayMicroseconds(20);

  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
 
  distance = duration * 0.034 / 2;

if (distance <= 20) 
  {
    // Do something if the distance is less than or equal to 20 cm
    stop();
    meArm();
    Serial.print(distance);
    delay(500);
   
  }

if (left < 1) 
  {
    digitalWrite(LED_LEFT, HIGH);
  }
  else {
    digitalWrite(LED_LEFT, LOW);
  }

  

  if (middleFront < 1) 
  {
    digitalWrite(LED_MIDDLE_RIGHT, HIGH);
  }
  else 
  {
    digitalWrite(LED_MIDDLE_RIGHT, LOW);
  }

  if (right < 1) 
  {
    digitalWrite(LED_RIGHT, HIGH);
  }
  else
  {
    digitalWrite(LED_RIGHT, LOW);
  }

  //Motor Speed
  analogWrite(ENA,90);
  analogWrite(ENB,100);




if  ( left < val  && middleFront < val && right < val ) //000
  {
    stop();
    Serial.print("stop");
  }


if  ( left < val &&  middleFront < val && right == val ) //001
   {
    rght();
    Serial.print("right");
   }


if  ( left < val &&  middleFront == val && right == val ) //011  
   {
    rght();
    Serial.print("right");
   }


if  ( left < val  && middleFront == val && right < val ) //010  
   {
    forward();
    Serial.print("forward");
   }


if  ( left == val &&  middleFront < val && right < val ) //100  
   {
    lft();
    Serial.print("left");
   }


if  ( left == val &&  middleFront == val && right < val ) //110
   {
    lft();
    Serial.print("left");
   }


if  ( left == val &&  middleFront < val && right == val ) //101 
   {
    stop();
    Serial.print("stop");
   }



if  ( left == val &&  middleFront == val && right == val ) //111 
   {    
   stop();
    Serial.print("uturn");
   }


}
void stopM()
{
  // Stop the motors
  analogWrite(ENA,0);
  analogWrite(ENB,0);
  delay(1000);

}
void stop()
{
  // Stop the motors
  analogWrite(ENA,0);
  analogWrite(ENB,0);
}

void forward() 
{
  // Move forward
  analogWrite(ENA,60);
  analogWrite(ENB,100);

  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}

void lft() 
{
  // Turn left
  analogWrite(ENA,80);
  analogWrite(ENB,0);

  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}

void rght() 
{
  // Turn right
  analogWrite(ENA,80);
  analogWrite(ENB,100);

  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);

}

void uTurn() 
{
  // Make a U-turn
  analogWrite(ENA,90);
  analogWrite(ENB,100);

  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);

  delay(1400);

  }

void meArm()
{

  servoA.write(0);

  for (A; A<= 180; ++A) 
      {
       servoA.write(A);
       delay(20);
      }

for (A; A>= 0; --A) 
      {
       servoA.write(A);
       delay(20);
      }
delay(500);
}

