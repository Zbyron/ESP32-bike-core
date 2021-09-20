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

int nImpulse = 0;
float nMetersPerCycle = 5.3;
int nMetersTraveled;
float nKmTraveled;
int nSeconds;
float nAverageSpeed;
float nCalories;

//bounce
int counter = 0;       // how many times we have seen new value
int reading;           // the current value read from the input pin
int current_state = LOW;    // the debounced input value
long milTime = 0;         // the last time the output pin was sampled
int debounce_count = 10; // number of millis/samples to consider before declaring a debounced input
 bool lowTriggered = false;
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
  display.print(String(nKmTraveled) + "KM");

  display.setTextSize(1);
  display.setCursor(0, 30);
  display.print(String(nMetersTraveled) + "M");
  
  display.setCursor(0, 40);
  display.print("Time: " + String(nSeconds) + "s");


  display.setCursor(0, 50);
  display.print("Calories: " + String(nCalories));
 
  display.display(); 
}

void updateBikeData() {
   //------------Elaborations--------------
  nImpulse++;
  nMetersTraveled = nImpulse * nMetersPerCycle;
  nKmTraveled = nMetersTraveled/1000.0;
  nSeconds = millis() / 1000;
  nAverageSpeed = nKmTraveled * 3600 / nSeconds;
  nCalories = nImpulse/10.0;

}

void bikeSerialOut() {
  Serial.println("Ped: ");
  Serial.println(nImpulse);
  Serial.println("  Km: ");
  Serial.println(nKmTraveled);
 
  Serial.println("Time (secs): ");
  Serial.println(nSeconds);

  Serial.println("Speed AVG: ");
  Serial.println(nAverageSpeed);
  
  Serial.println("Calories: ");
  Serial.println(nCalories);
}

void readBikeInput() {
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
    // If the Input has shown the same value for long enough let's switch it
    if(counter >= debounce_count)
    {
      counter = 0;
      if( reading == HIGH && lowTriggered){
        updateBikeData();
        updateDisplay();
        bikeSerialOut();
        lowTriggered = false;
      }
        
    }
    milTime = millis();
  }
}

void setup() {
  Wire.begin();
  initDisplay();
  pinMode(bikePin,INPUT);
  Serial.begin(9600);
  Serial.println("Starting...");
}


void loop() {
  // while(digitalRead(bikePin)==LOW)
  //    delay(10);
  // while(digitalRead(bikePin)==HIGH)
  //    delay(10);

  // if(digitalRead(bikePin)==HIGH)
  //  Serial.println("HIGH");
  // else
  //   Serial.println("LOW");
  //  //------------Elaborations--------------
  // nImpulse++;
  // nMetersTraveled = nImpulse * nMetersPerCycle;
  // nKmTraveled = nMetersTraveled/1000.0;
  // nSeconds = millis() / 1000;
  // nAverageSpeed = nKmTraveled * 3600 / nSeconds;
  // nCalories = nImpulse/10.0;
  // updateDisplay();
  // bikeSerialOut();

  readBikeInput();
  
  //----------OUT-----------------
  
  
}