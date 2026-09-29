#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// กำหนดขาอุปกรณ์
#define MOISTURE_PIN A0
#define BUZZER_PIN 8
#define LED1_PIN 2
#define LED2_PIN 3
#define LED3_PIN 4
#define LED4_PIN 5

// ตั้งค่า Calibration ของเซนเซอร์ความชื้น
int AirValue = 750;   
int WaterValue = 350; 

void setup() {
  Serial.begin(9600);

  // ตั้งค่าให้ขา LED และ Buzzer เป็นขาออก (OUTPUT)
  pinMode(BUZZER_PIN, OUTPUT);
  pinMode(LED1_PIN, OUTPUT);
  pinMode(LED2_PIN, OUTPUT);
  pinMode(LED3_PIN, OUTPUT);
  pinMode(LED4_PIN, OUTPUT);

  // เริ่มต้นหน้าจอ OLED
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

  // --- 1. ส่วนแสดงผลจอ OLED ---
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

  // --- 2. ส่วนแสดงผล LED 4 ระดับ ---
  // LED1 ติดเมื่อความชื้น > 0%
  digitalWrite(LED1_PIN, moisturePercent >= 0 ? HIGH : LOW);
  // LED2 ติดเมื่อความชื้น >= 25%
  digitalWrite(LED2_PIN, moisturePercent >= 25 ? HIGH : LOW);
  // LED3 ติดเมื่อความชื้น >= 50%
  digitalWrite(LED3_PIN, moisturePercent >= 50 ? HIGH : LOW);
  // LED4 ติดเมื่อความชื้น >= 75%
  digitalWrite(LED4_PIN, moisturePercent >= 75 ? HIGH : LOW);

  // --- 3. ส่วนแจ้งเตือน Buzzer ---
  // ถ้าน้ำแห้งกว่า 20% ให้บัซเซอร์ดังแจ้งเตือน
  if(moisturePercent > 70) {
    tone(BUZZER_PIN, 200); // สร้างเสียงความถี่ 1000Hz (รองรับทั้ง Active/Passive)
    delay(1500);             // ดัง 0.2 วินาที
    noTone(BUZZER_PIN);     // ดับเสียง
    delay(800);             // เงียบ 0.8 วินาที (รวมเป็น 1 รอบ = 1 วินาทีพอดี)
  } else {
    noTone(BUZZER_PIN);     // ถ้าความชื้นปกติ ให้ปิดเสียง
    delay(1000);            // รออัปเดตข้อมูลใหม่ทุกๆ 1 วินาที
  }
}