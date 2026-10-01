#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);


#define MOISTURE_PIN A0
#define BUZZER_PIN 10
#define LED1_PIN 6
#define LED2_PIN 7
#define LED3_PIN 8
#define LED4_PIN 9


int AirValue = 750;   
int WaterValue = 350; 

void setup() {
  Serial.begin(9600);

  
  pinMode(BUZZER_PIN, OUTPUT);
  pinMode(LED1_PIN, OUTPUT);
  pinMode(LED2_PIN, OUTPUT);
  pinMode(LED3_PIN, OUTPUT);
  pinMode(LED4_PIN, OUTPUT);


  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;);
  }
  display.clearDisplay();
  display.setTextColor(SSD1306_WHITE);
}

void loop() {
  int sensorValue = analogRead(MOISTURE_PIN);
  int moisturePercent = map(sensorValue, AirValue, WaterValue, 0, 100);
  
  if(moisturePercent > 100) moisturePercent = 100;
  if(moisturePercent < 0) moisturePercent = 0;

  display.clearDisplay();
  
  display.setTextSize(1);
  display.setCursor(0, 0);
  display.println(F("Soil Moisture:"));

  display.setTextSize(3);
  display.setCursor(20, 20);
  display.print(moisturePercent);
  display.println(F("%"));

  display.setTextSize(1);
  display.setCursor(0, 50);
  display.print(F("Raw: "));
  display.print(sensorValue);
  
  display.display();

  digitalWrite(LED4_PIN, moisturePercent >= 80 ? LOW : HIGH);
  digitalWrite(LED3_PIN, (moisturePercent >= 70 && moisturePercent < 80) ? LOW : HIGH);
  digitalWrite(LED2_PIN, (moisturePercent >= 50 && moisturePercent < 70) ? LOW : HIGH);
  digitalWrite(LED1_PIN, moisturePercent < 50 ? LOW : HIGH);
  

  if(moisturePercent <=40 ) {
    tone(BUZZER_PIN, 2000); 
    delay(1500);             
    noTone(BUZZER_PIN);     
    delay(800);             
  } else {
    noTone(BUZZER_PIN);     
    delay(1000);            
  }
}
