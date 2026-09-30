#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);


#define MOISTURE_PIN A0
#define BUZZER_PIN 10
#define LED1_PIN 9
#define LED2_PIN 8
#define LED3_PIN 7
#define LED4_PIN 6


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

  digitalWrite(LED1_PIN, moisturePercent >= 80 and moisturePercent <=100 ? HIGH : LOW);
  
  digitalWrite(LED2_PIN, moisturePercent >= 70 and moisturePercent < 80 ? HIGH : LOW);
  
  digitalWrite(LED3_PIN, moisturePercent >= 50 and moisturePercent < 70 ? HIGH : LOW);

  digitalWrite(LED4_PIN, moisturePercent  >= 20 and moisturePercent <50 ? HIGH : LOW);

  if(moisturePercent <=30 ) {
    tone(BUZZER_PIN, 2000); 
    delay(1500);             
    noTone(BUZZER_PIN);     
    delay(800);             
  } else {
    noTone(BUZZER_PIN);     
    delay(1000);            
  }
}

// LED4: ไฟเขียว (ความชื้นสูงมาก มากกว่าหรือเท่ากับ 80%)
  digitalWrite(LED4_PIN, moisturePercent >= 80 ? HIGH : LOW);
  
  // LED3: ไฟน้ำเงิน (ความชื้นปานกลางค่อนข้างสูง ช่วง 70% ถึง 79%)
  digitalWrite(LED3_PIN, moisturePercent >= 70 && moisturePercent < 80 ? HIGH : LOW);
  
  // LED2: ไฟเหลือง (ความชื้นปานกลาง ช่วง 50% ถึง 69%)
  digitalWrite(LED2_PIN, moisturePercent >= 50 && moisturePercent < 70 ? HIGH : LOW);

  // LED1: ไฟแดง (ดินแห้ง / ความชื้นต่ำกว่า 50% หรืออยู่ในช่วง 20% - 49%)
  digitalWrite(LED1_PIN, moisturePercent >= 20 && moisturePercent < 50 ? HIGH : LOW);
