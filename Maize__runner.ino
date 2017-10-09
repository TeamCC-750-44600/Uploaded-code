#include <Servo.h>
#include <Wire.h>// motorshield libraries
#include <Adafruit_MotorShield.h>
#include "utility/Adafruit_MS_PWMServoDriver.h"
// ultrs pins
const int mainEcho = 3;
const int mainTrig = 2;

// obstacle avoidance pins
#define avoidPinR 8
#define avoidPinL 7
#define avoidPinF 6
// servo position
int pos = 0;

//distances for functions
int mrCurrent;
int right;// variable for right reading
int left;// variable for left reading


Adafruit_MotorShield AFMS = Adafruit_MotorShield(); 
Adafruit_DCMotor *myMotor3 = AFMS.getMotor(3);
Adafruit_DCMotor *myMotor4 = AFMS.getMotor(4);

//declaring function that calculates the distance of an ultrasonic sensor
int calculate_distance(int guntrig, int echovoice ){
  int duration;
  int distance;
     digitalWrite(guntrig, HIGH);
    delayMicroseconds(2);
    digitalWrite(guntrig, LOW);
    duration = pulseIn(echovoice, HIGH);
    distance= (duration/2) /29.1;
    Serial.print(distance);
    Serial.print(" cm");
    //Serial.println(duration);
    return distance;
}
// initializes the srevo library on your servo
Servo myservo;
      void ReadDistance(){
     //calculates the current middle reading using the sensor's pins
    mrCurrent = calculate_distance(mainTrig, mainEcho);
    Serial.println(" mrCurrent");
    //servo from middle to left
    for (pos = 80; pos <= 180; pos += 1) 
    { 
      // in steps of 1 degree
      myservo.write(pos);              
      delay(5);
      //Serial.println(pos);    
    }
    //calculates the left reading using the sensor's pins
    left = calculate_distance(mainTrig, mainEcho);
    Serial.println(" left");
   
    //servo from left to right
    for (pos = 180; pos >= 0; pos -= 1) 
    { 
      myservo.write(pos);              
      delay(5);
    }
    //calculates the right reading using the sensor's pins
    right = calculate_distance(mainTrig, mainEcho);
    Serial.println(" right");

    //servo from right to middle
    for (pos = 0; pos <= 80; pos += 1) 
    { //sevo from 0-90 
      myservo.write(pos);              
      delay(5);
      //Serial.println(pos);
    }
}


void setup() 
{
  Serial.begin(9600);          
  myservo.attach(9);
  AFMS.begin();  
  myMotor3->setSpeed(75);
  myMotor4->setSpeed(75);
  pinMode(mainTrig, OUTPUT);
  pinMode(mainEcho, INPUT);
  pinMode(avoidPinR, INPUT);
  pinMode(avoidPinL, INPUT);
  pinMode(avoidPinF, INPUT);
  //myservo.write(pos);
}

void loop() 
{

  
    //says if the previous reading and current reading have a proximity of 5cm apart, or if the right and left is less than five, that the robot is stuck  
    
    boolean avoidValR = digitalRead(avoidPinR);
    boolean avoidValL = digitalRead(avoidPinL);
    boolean avoidValF = digitalRead(avoidPinF);
    if ((avoidValR == LOW) || (avoidValL == LOW)|| (avoidValF == LOW) )
    {
         /*Serial.println(avoidValR);
         Serial.println(" avoidVal");
         Serial.println(avoidValL);
         Serial.println(" avoidVal2");
         Serial.println(avoidValF);
         Serial.println(" avoidVal3");                   
         Serial.println("I am under correction");*/
         myMotor3->run(BACKWARD);//moves forward
         myMotor4->run(BACKWARD);
         delay(200);
         myMotor3->run(RELEASE);
         myMotor4->run(RELEASE);
         //
         if(right < left)
         {     
            myMotor4->run(FORWARD);//turns left
            delay(300);
            myMotor4->run(RELEASE);
         }
         else
         {
            myMotor3->run(FORWARD);
            delay(300);
            myMotor3->run(RELEASE);
         }
         //
   
    }
    else
    {
        ReadDistance();
        //mrCurrent reading is greater than 20cm
        if(left > 30) 
        {
             myMotor4->run(FORWARD);//turns left
             delay(1000);
             myMotor4->run(RELEASE);
             myMotor3->run(FORWARD);//moves forward
             myMotor4->run(FORWARD);
             delay(300);
             myMotor3->run(RELEASE);
             myMotor4->run(RELEASE);            
        }
        else if (mrCurrent > 15)//left reading is greater than 20 cm
        {

             myMotor3->run(FORWARD);//moves forward
             myMotor4->run(FORWARD);
             delay(300);
             myMotor3->run(RELEASE);
             myMotor4->run(RELEASE);
             //Serial.println(" I am Moving forward");
        }
        else 
        {
            myMotor3->run(FORWARD);//turns right
            delay(1000);
            myMotor3->run(RELEASE);
        }
    }

 
}
//end of the code
