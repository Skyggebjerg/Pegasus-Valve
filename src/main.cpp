// For PEGASUS Valve control


#include <Arduino.h>

#include <M5Atom.h>
#include "StepperDriver.h"
#include "FastLED.h"

//#define Neopixel_PIN 26
//#define NUM_LEDS     37

//CRGB leds[NUM_LEDS];
//uint8_t gHue = 0;  // Initial tone value.
//uint8_t brightn = 0;  // Initial brightness value. 

//int cur_value1 = 0, cur_value2 = 0;

int motor_steps = 200;
int step_divisition = 32; //32
int en_pin = 22;
int dir_pin = 23;
int step_pin = 19;

int step = 0;
int speed = 0;

//int toggler =0;

StepperDriver ss(motor_steps, step_divisition, en_pin, dir_pin, step_pin);

void setup()
{
  M5.begin(true, false, true);
  pinMode(26, INPUT_PULLDOWN); // set pin mode to input
  pinMode(32, OUTPUT);
  digitalWrite(32, LOW);
  ss.powerEnable(false);
  ss.setSpeed(0);
  delay(1600);

}

void loop()
{
      while(digitalRead(26) == LOW) { // Wait for Pump signal OK
        delay(10);
      }

      ss.powerEnable(true);
      ss.setSpeed(300); // 60 = 60 revolutions per minute (rpm) = 1 rev per sec
      ss.step(100,50,50); //turn valve 180 degrees (to outlet)
      delay(100);
      digitalWrite(32, HIGH); // Tell Pump that Valve is changed to outlet
      ss.powerEnable(false); // release torque on stepmotor      

      while(digitalRead(26) == HIGH) { // Wait for Pump signal OK
        delay(10);
} 
      ss.powerEnable(true);
      ss.setSpeed(300);      
      ss.step(-100,50,50); //turn valve back to inlet
     delay(100);
           digitalWrite(32, LOW); // Tell Pump that Valve is back to inlet
      ss.powerEnable(false);
   }
         //M5.update();
//}