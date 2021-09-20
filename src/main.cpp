#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_I2CDevice.h> 
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "bike.h"

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
#define OLED_RESET     -1 // Reset pin # (or -1 if sharing Arduino reset pin)

Bike bike(17);

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

void initDisplay(){
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  delay(2000);
  display.clearDisplay();
  display.setTextColor(WHITE);
  display.setCursor(0,0);
  display.print("Bike Start");
  display.display(); 
}

void updateDisplay(){
  display.clearDisplay();

  display.setTextSize(2);
  display.setCursor(0,0);
  display.print(String(bike.nKmTraveled) + "KM");

  display.setTextSize(1);
  display.setCursor(0, 30);
  display.print(String(bike.nMetersTraveled) + "M");
  
  display.setCursor(0, 40);
  display.print("Time: " + String(bike.nSeconds) + "s");


  display.setCursor(0, 50);
  display.print("Calories: " + String(bike.nCalories));
 
  display.display(); 
}

void setup() {
  Wire.begin();
  initDisplay();
  Serial.begin(9600);
  Serial.println("Starting...");
}

void loop() {

  bike.readBikeInput();
  updateDisplay();  
  
}