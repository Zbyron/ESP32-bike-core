#include "bike.h"
#include <Arduino.h>

int bikePin;
int nImpulse = 0;
float nMetersPerCycle = 5.3;
int nMetersTraveled;
float nKmTraveled;
int nSeconds;
float nAverageSpeed;
float nCalories;

//bounce
int counter = 0;       
int reading;           
int current_state = LOW;
long milTime = 0;
int debounce_count = 10; 
bool lowTriggered = false;

Bike::Bike(int pin) {
    bikePin = pin;
    pinMode(pin,INPUT);
}

void Bike::updateBikeData() {
  nImpulse++;
  nMetersTraveled = nImpulse *  5.3;// nMetersPerCycle;
  nKmTraveled = nMetersTraveled/1000.0;
  nSeconds = millis() / 1000;
  nAverageSpeed = nKmTraveled * 3600 / nSeconds;
  nCalories = nImpulse/10.0;

}

void Bike::bikeSerialOut() {
  Serial.write("ESP32_BIKE_PED\r\n");
  Serial.flush();
}

void Bike::readBikeInput() {
  if(millis() != milTime)
  {
   
    reading = digitalRead(bikePin);
    if(reading == LOW)
      lowTriggered = true;

    if(reading == current_state && counter > 0)
    {
      counter--;
    }
    if(reading != current_state)
    {
       counter++; 
    }
    if(counter >= debounce_count)
    {
      counter = 0;
      if( reading == HIGH && lowTriggered){
        updateBikeData();
        bikeSerialOut();
        lowTriggered = false;
      }
        
    }
    milTime = millis();
  }
}