//This is a test for the magnetic encoder AS5600 reading and displaying the angles on a 1.8' 128x160 RGB_TFT
// Currently there is a bit of lag on the screen because of the different clockspeeds of the components and their interaction. 


#include <Adafruit_GFX.h>    // Core graphics library
#include <Adafruit_ST7735.h> // Hardware-specific library for ST7735
#include <Adafruit_ST7789.h> // Hardware-specific library for ST7789
#include <SPI.h>
#include "AS5600.h"
#include "Wire.h"

AS5600 as5600;   //  use default Wire

#define TFT_CS        10
#define TFT_RST        9 // Or set to -1 and connect to Arduino RESET pin
#define TFT_DC         8
Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS, TFT_DC, TFT_RST);


int sumberS = 0;
void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);
  Serial.print("AS5600_LIB_VERSION: ");
  Serial.println(AS5600_LIB_VERSION);


   tft.initR(INITR_BLACKTAB);     

  Serial.println(F("Initialized"));

  //  ESP32
  //  as5600.begin(14,15);
  //  AVR
  as5600.begin(4);  //  set direction pin.
  as5600.setDirection(AS5600_CLOCK_WISE);  // default, just be explicit.
  int b = as5600.isConnected();
  Serial.print("Connect: ");
  Serial.println(b);
  delay(10);
}


void loop()
{
  //Serial.print(millis());
  //Serial.print("\t");
  Serial.print(as5600.readAngle());
  Serial.print("\t");
  Serial.println(as5600.rawAngle());
  Serial.println(as5600.rawAngle() * AS5600_RAW_TO_DEGREES);



for (sumberS = 0; sumberS <=10; sumberS++){
    tft.setCursor(10,60);
    tft.setTextColor(ST77XX_WHITE);
    tft.setTextSize(2);
    tft.setTextWrap(true);
    tft.println(sumberS);
    tft.println(as5600.readAngle());
    
    
    delay(100);
    tft.fillScreen(ST77XX_BLACK);
  }

}



