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

static const unsigned char PROGMEM plant_[] = {
0x1f, 0xc0, 0x00, 0x00, //   ########                         
  0x30, 0x70, 0x00, 0x00, //  ##     ###                         
  0x20, 0x18, 0x00, 0x00, //  #        ##                        
  0x00, 0x0f, 0x00, 0x00, //           ####                      
  0x00, 0x1f, 0x80, 0x00, //          ######                     
  0x00, 0x3f, 0xc0, 0x00, //         ########                    
  0x00, 0x1f, 0xe0, 0x00, //          #######                    
  0x00, 0x01, 0x20, 0x00, //            #  #                     
  0x00, 0x0a, 0x88, 0x00, //           # #  # #                  
  0x00, 0x12, 0x44, 0x00, //          #  #   # #                 
  0x00, 0x24, 0x22, 0x00, //         #  #   #  #                
  0x00, 0x01, 0x80, 0x00, //            ##                       
  0x00, 0x03, 0xc0, 0x00, //           ####                      
  0x00, 0x07, 0xe0, 0x00, //          ######                     
  0x00, 0x0d, 0xb0, 0x00, //          ## ## ##                   
  0x00, 0x1f, 0xf8, 0x00, //         ##########                  
  0x00, 0x1e, 0x78, 0x00, //         ####  ####                  
  0x00, 0x3d, 0xbc, 0x00, //        ## ##  ## ##                 
  0x00, 0x7f, 0xfe, 0x00, //       ############                
  0x00, 0x77, 0xee, 0x00, //       ### ###### ###                
  0x00, 0x23, 0xc4, 0x00, //        #  ####  #                   
  0x00, 0x01, 0x80, 0x00, //            ##                       
  0x00, 0x01, 0x80, 0x00, //            ##                       
  0x00, 0x01, 0x80, 0x00, //            ##                       
  0x00, 0x01, 0x80, 0x00, //            ##                       
  0x00, 0x01, 0x80, 0x00, //            ##                       
  0x3f, 0xff, 0xff, 0xfc, //  ##############################     
  0x7f, 0xff, 0xff, 0xfe, // ################################    
  0x6d, 0xb6, 0xdb, 0x6e, // ## ## ## ## ## ## ## ## ## ##    
  0x36, 0xdb, 0x6c, 0x36, //  ## ## ## ## ## ## ## ## ##      
  0x1b, 0x6d, 0xb8, 0x1c, //   ## ## ## ## ## ## ## ##        
  0x00, 0x00, 0x00, 0x00  
};


static const unsigned char PROGMEM face_A []= {
  0x00, 0x3f, 0xfc, 0x00, //        ##############        
  0x01, 0xe0, 0x07, 0x80, //      #####        #####      
  0x07, 0x00, 0x00, 0xe0, //    ###                ###    
  0x0e, 0x00, 0x00, 0x70, //   ###                  ###   
  0x1c, 0x00, 0x00, 0x38, //  ###                    ###  
  0x38, 0x00, 0x00, 0x1c, // ###                      ### 
  0x30, 0x00, 0x00, 0x0c, // ##                        ## 
  0x70, 0x3c, 0x3c, 0x0e, // #      ####    ####      #  
  0x60, 0x7e, 0x7e, 0x06, // #     ######  ######     # 
  0x60, 0x7e, 0x7e, 0x06, // #     ######  ######     # 
  0xe0, 0x3c, 0x3c, 0x07, // #      ####    ####      # 
  0xc0, 0x00, 0x00, 0x03, // #                        # 
  0xc0, 0x00, 0x00, 0x03, // #                        # 
  0xc0, 0x00, 0x00, 0x03, // #                        # 
  0xc0, 0x00, 0x00, 0x03, // #                        # 
  0xc0, 0x00, 0x00, 0x03, // #                        # 
  0xc0, 0x7f, 0xfe, 0x03, // #    ################    #  
  0xc0, 0x7f, 0xfe, 0x03, // #    ################    # 
  0xc0, 0x00, 0x00, 0x03, // #                        # 
  0xc0, 0x00, 0x00, 0x03, // #                        # 
  0x60, 0x00, 0x00, 0x06, // #                        # 
  0x60, 0x00, 0x00, 0x06, // #                        # 
  0x30, 0x00, 0x00, 0x0c, // ##                        ## 
  0x38, 0x00, 0x00, 0x1c, // ###                      ### 
  0x1c, 0x00, 0x00, 0x38, //  ###                    ###  
  0x0e, 0x00, 0x00, 0x70, //   ###                  ###   
  0x07, 0x00, 0x00, 0xe0, //    ###                ###    
  0x01, 0xe0, 0x07, 0x80, //      #####        #####      
  0x00, 0x3f, 0xfc, 0x00, //        ##############        
  0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00  
};

static const unsigned char PROGMEM face_B[] = {
  0x00, 0x3f, 0xfc, 0x00, //        ##############        
  0x01, 0xe0, 0x07, 0x80, //      #####        #####      
  0x07, 0x00, 0x00, 0xe0, //    ###                ###    
  0x0e, 0x00, 0x00, 0x70, //   ###                  ###   
  0x1c, 0x00, 0x00, 0x38, //  ###                    ###  
  0x38, 0x00, 0x00, 0x1c, // ###                      ### 
  0x30, 0x00, 0x00, 0x0c, // ##                        ## 
  0x70, 0x3c, 0x3c, 0x0e, // #      ####    ####      #  
  0x60, 0x7e, 0x7e, 0x06, // #     ######  ######     # 
  0x60, 0x7e, 0x7e, 0x06, // #     ######  ######     # 
  0xe0, 0x3c, 0x3c, 0x07, // #      ####    ####      # 
  0xc0, 0x00, 0x00, 0x03, // #                        # 
  0xc0, 0x00, 0x00, 0x03, // #                        # 
  0xc0, 0x60, 0x06, 0x03, // #     ##          ##     #  
  0xc0, 0x30, 0x0c, 0x03, // #    ##            ##    # 
  0xc0, 0x18, 0x18, 0x03, // #   ##              ##   # 
  0xc0, 0x0d, 0xb0, 0x03, // #  ##  ##        ##  ##  # 
  0xc0, 0x07, 0xe0, 0x03, // #    ############    #  
  0xc0, 0x03, 0xc0, 0x03, // #     ##########     # 
  0xc0, 0x00, 0x00, 0x03, // #                        # 
  0x60, 0x00, 0x00, 0x06, // #                        # 
  0x60, 0x00, 0x00, 0x06, // #                        # 
  0x30, 0x00, 0x00, 0x0c, // ##                        ## 
  0x38, 0x00, 0x00, 0x1c, // ###                      ### 
  0x1c, 0x00, 0x00, 0x38, //  ###                    ###  
  0x0e, 0x00, 0x00, 0x70, //   ###                  ###   
  0x07, 0x00, 0x00, 0xe0, //    ###                ###    
  0x01, 0xe0, 0x07, 0x80, //      #####        #####      
  0x00, 0x3f, 0xfc, 0x00, //        ##############        
  0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00  
};


static const unsigned char PROGMEM face_C[] = {
  0x00, 0x3f, 0xfc, 0x00, //        ##############        
  0x01, 0xe0, 0x07, 0x80, //      #####        #####      
  0x07, 0x00, 0x00, 0xe0, //    ###                ###    
  0x0e, 0x00, 0x00, 0x70, //   ###                  ###   
  0x1c, 0x00, 0x00, 0x38, //  ###                    ###  
  0x38, 0x00, 0x00, 0x1c, // ###                      ### 
  0x30, 0x00, 0x00, 0x0c, // ##                        ## 
  0x70, 0x3c, 0x3c, 0x0e, // #      ####    ####      #  
  0x60, 0x7e, 0x7e, 0x06, // #     ######  ######     # 
  0x60, 0x7e, 0x7e, 0x06, // #     ######  ######     # 
  0xe0, 0x3c, 0x3c, 0x07, // #      ####    ####      # 
  0xc0, 0x00, 0x00, 0x03, // #                        # 
  0xc0, 0x7f, 0xfe, 0x03, // #    ################    #  
  0xc0, 0xff, 0xff, 0x03, // #   ##################   # 
  0xc0, 0x7f, 0xfe, 0x03, // #   ##################   # 
  0xc0, 0x3f, 0xfc, 0x03, // #    ################    #  
  0xc0, 0x1f, 0xf8, 0x03, // #     ##############     # 
  0xc0, 0x0f, 0xf0, 0x03, // #      ############      # 
  0xc0, 0x07, 0xe0, 0x03, // #       ##########       # 
  0xc0, 0x01, 0x80, 0x03, // #         ######         # 
  0x60, 0x00, 0x00, 0x06, // #                        # 
  0x60, 0x00, 0x00, 0x06, // #                        # 
  0x30, 0x00, 0x00, 0x0c, // ##                        ## 
  0x38, 0x00, 0x00, 0x1c, // ###                      ### 
  0x1c, 0x00, 0x00, 0x38, //  ###                    ###  
  0x0e, 0x00, 0x00, 0x70, //   ###                  ###   
  0x07, 0x00, 0x00, 0xe0, //    ###                ###    
  0x01, 0xe0, 0x07, 0x80, //      #####        #####      
  0x00, 0x3f, 0xfc, 0x00, //        ##############        
  0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00  
};

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

  display.display();

  if(moisturePercent < 40)
  {
    display.clearDisplay();
    display.setTextSize(1);
    display.setCursor(0, 0);display.println(F("Soil Moisture:"));
    display.setTextSize(3);
    display.setCursor(20, 20);
    display.print(moisturePercent);
    display.println(F("%"));
    display.drawBitmap(90, 20,plant_, 32, 32, SSD1306_WHITE);
    display.display();
  } 
  else if(moisturePercent >= 50 && moisturePercent < 70)
  {
    display.clearDisplay();
    display.setTextSize(1);
    display.setCursor(0, 0);display.println(F("Soil Moisture:"));
    display.setTextSize(3);
    display.setCursor(20, 20);
    display.print(moisturePercent);
    display.println(F("%"));
    display.drawBitmap(90, 20,face_A, 32, 32, SSD1306_WHITE);
    display.display();
  }
  else if(moisturePercent >= 70 && moisturePercent < 80)
  {
    display.clearDisplay();
    display.setTextSize(1);
    display.setCursor(0, 0);display.println(F("Soil Moisture:"));
    display.setTextSize(3);
    display.setCursor(20, 20);
    display.print(moisturePercent);
    display.println(F("%"));
    display.drawBitmap(90, 20,face_B, 32, 32, SSD1306_WHITE);
    display.display();
  }
  else if(moisturePercent >= 80)
  {
    display.clearDisplay();
    display.setTextSize(1);
    display.setCursor(0, 0);display.println(F("Soil Moisture:"));
    display.setTextSize(3);
    display.setCursor(20, 20);
    display.print(moisturePercent);
    display.println(F("%"));
    display.drawBitmap(90, 20,face_C, 32, 32, SSD1306_WHITE);
    display.display();
  }

  digitalWrite(LED4_PIN, moisturePercent >= 80 ? LOW : HIGH);
  digitalWrite(LED3_PIN, moisturePercent >= 70 && moisturePercent < 80 ? LOW : HIGH);
  digitalWrite(LED2_PIN, moisturePercent >= 50 && moisturePercent < 70 ? LOW : HIGH);
  digitalWrite(LED1_PIN, moisturePercent < 40 ? LOW : HIGH);
  

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
