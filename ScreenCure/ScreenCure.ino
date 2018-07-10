#include <Adafruit_GFX.h>
#include <Adafruit_ST7735.h>
#include <SD.h>
#include <SPI.h>

#if defined(__SAM3X8E__)
    #undef __FlashStringHelper::F(string_literal)
    #define F(string_literal) string_literal
#endif

// TFT display and SD card will share the hardware SPI interface.
// Hardware SPI pins are specific to the Arduino board type and
// cannot be remapped to alternate pins.  For Arduino Uno,
// Duemilanove, etc., pin 11 = MOSI, pin 12 = MISO, pin 13 = SCK.
//#define SD_CS    4  // Chip select line for SD card
#define TFT_CS  10  // Chip select line for TFT display
#define TFT_DC   8  // Data/command line for TFT
#define TFT_RST  -1  // Reset line for TFT (or connect to +5V)

Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS, TFT_DC, TFT_RST);

#define BUTTON_NONE 0
#define BUTTON_DOWN 1
#define BUTTON_RIGHT 2
#define BUTTON_SELECT 3
#define BUTTON_UP 4
#define BUTTON_LEFT 5


float timer = 60.0;
float butVert = 5.0;
float butHorz = 1.0;

const int pPin = 9;

void setup(void) {
  Serial.begin(9600);
  // initialize the LED pin as an output:
  pinMode(pPin, OUTPUT);
  digitalWrite(pPin, LOW);

  // Initialize 1.8" TFT
  tft.initR(INITR_BLACKTAB);   // initialize a ST7735S chip, black tab

  Serial.println("OK!");
  tft.fillScreen(ST7735_BLACK);
  tft.setRotation(1);
  tft.setTextSize(2);
  tft.setTextColor(ST7735_WHITE);
  tft.setCursor(0, 0);
  tft.print("Cure time:");
  tft.setTextSize(5);
  tft.setTextColor(ST7735_RED);
  tft.setCursor(20, 40);
  tft.print(timer,1);
  tft.setTextSize(1);
  tft.setTextColor(ST7735_WHITE);
  tft.setCursor(38, 110);
  tft.print("McScreeny Cure");
  tft.setCursor(50, 120);
  tft.print("UTA FabLab");
}


uint8_t readButton(void) {
  float a = analogRead(3);
  
  a *= 5.0;
  a /= 1024.0;
  
  Serial.print("Button read analog = ");
  Serial.println(a);
  if (a < 0.2) return BUTTON_RIGHT;
  if (a < 1.0) return BUTTON_UP;
  if (a < 1.5) return BUTTON_SELECT;
  if (a < 2.0) return BUTTON_LEFT;
  if (a < 3.2) return BUTTON_DOWN;
  else return BUTTON_NONE;
}

void loop() { 
  uint8_t b = readButton();
  tft.setTextSize(5);
  if (b == BUTTON_UP) {
    tft.setTextColor(ST7735_BLACK);
    tft.setCursor(20, 40);
    tft.print(timer,1);
    timer += butVert;
    if (timer < 0) {
      timer = 0;
    }
    delay(200);
    tft.setTextColor(ST7735_RED);
    tft.setCursor(20, 40);
    tft.print(timer,1);
  }
  if (b == BUTTON_DOWN) {
    tft.setTextColor(ST7735_BLACK);
    tft.setCursor(20, 40);
    tft.print(timer,1);
    timer -= butVert;
    if (timer < 0) {
      timer = 0;
    }
    delay(200);
    tft.setTextColor(ST7735_RED);
    tft.setCursor(20, 40);
    tft.print(timer,1);
  }
  if (b == BUTTON_LEFT) {
    tft.setTextColor(ST7735_BLACK);
    tft.setCursor(20, 40);
    tft.print(timer,1);
    timer -= butHorz;
    if (timer < 0) {
      timer = 0;
    }
    delay(200);
    tft.setTextColor(ST7735_RED);
    tft.setCursor(20, 40);
    tft.print(timer,1);
  }
  if (b == BUTTON_RIGHT) {
    tft.setTextColor(ST7735_BLACK);
    tft.setCursor(20, 40);
    tft.print(timer,1);
    timer += butHorz;
    if (timer < 0) {
      timer = 0;
    }
    delay(200);
    tft.setTextColor(ST7735_RED);
    tft.setCursor(20, 40);
    tft.print(timer,1);
  }
  if (b == BUTTON_SELECT) {
    while (timer != 0.0) {
      digitalWrite(pPin, HIGH);
      for (timer; timer>=0.0; timer-=0.3){
            tft.setTextColor(ST7735_RED);
            tft.setCursor(20, 40);
            tft.print(timer,1);
            Serial.println(timer);
            delay(100);
            tft.setTextColor(ST7735_BLACK);
            tft.setCursor(20, 40);
            tft.print(timer,1);
      }

    if (timer <= 0) {
      digitalWrite(pPin, LOW);
      Serial.println("END");
      tft.fillScreen(ST7735_BLACK);
      delay(500);
      tft.setTextSize(5);
      tft.setTextColor(ST7735_CYAN);
      tft.setCursor(20, 50);//digitalWrite(LED, LOW);
      tft.print("DONE");
      tft.setTextSize(1);
      tft.setTextColor(ST7735_WHITE);
      tft.setCursor(38, 110);
      tft.print("McScreeny Cure");
      tft.setCursor(50, 120);
      tft.print("UTA FabLab");
      delay(1250);      
      tft.fillScreen(ST7735_BLACK);
      delay(500);
      tft.setTextSize(4);
      tft.setTextColor(ST7735_RED);
      tft.setCursor(27, 50);//digitalWrite(LED, LOW);
      tft.print("RESET");
      tft.setTextSize(1);
      tft.setTextColor(ST7735_WHITE);
      tft.setCursor(38, 110);
      tft.print("McScreeny Cure");
      tft.setCursor(50, 120);
      tft.print("UTA FabLab");
      delay(1250);
     }
    }
  }
}

