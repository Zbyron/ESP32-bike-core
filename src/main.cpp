#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_I2CDevice.h> 
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
#define OLED_RESET     -1 // Reset pin # (or -1 if sharing Arduino reset pin)
#define bikePin 17

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

int nImpulsi = 0;
float nMetriUnaPedalata = 5.3;
int nMetriPercorsi;
float nKmPercorsi;
int nSeconds;
float nVelocitaMedia;
float nCalories;

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
  display.print(String(nKmPercorsi) + "KMPS");

  display.setTextSize(1);
  display.setCursor(0, 30);
  display.print(String(nMetriPercorsi) + "KM");
  
  display.setCursor(0, 40);
  display.print("Time: " + String(nSeconds) + "s");


  display.setCursor(0, 50);
  display.print("Calories: " + String(nCalories));
 
  display.display(); 
}

void setup() {
  Wire.begin();
  initDisplay();
  pinMode(bikePin,INPUT);
  Serial.begin(9600);
  Serial.println("Starting...");
}

void loop() {
  while(digitalRead(bikePin)==LOW)
     delay(10);
  while(digitalRead(bikePin)==HIGH)
     delay(10);

   //------------Elaborations--------------
  nImpulsi++;
  nMetriPercorsi = nImpulsi * nMetriUnaPedalata;
  nKmPercorsi = nMetriPercorsi/1000.0;
  nSeconds = millis() / 1000;
  nVelocitaMedia = nKmPercorsi * 3600 / nSeconds;
  nCalories = nImpulsi/10.0;

  //----------Screen-----------------
  updateDisplay();
  Serial.println("Ped: ");
  Serial.println(nImpulsi);
  Serial.println("  Km: ");
  Serial.println(nKmPercorsi);
 
  Serial.println("Time (secs): ");
  Serial.println(nSeconds);

  Serial.println("Speed AVG: ");
  Serial.println(nVelocitaMedia);
  
  Serial.println("Calories: ");
  Serial.println(nCalories);

}