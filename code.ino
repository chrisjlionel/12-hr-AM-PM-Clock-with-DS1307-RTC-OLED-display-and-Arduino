#include <Wire.h>
#include <DS1307.h>
#include <Adafruit_GFX.h> //for this must add lib file download from Adfruit
#include <Adafruit_SSD1306.h> //for this must add lib file download from adfruit

#define OLED_RESET 4
Adafruit_SSD1306 display(OLED_RESET);

DS1307 clock;
RTCDateTime dt;

void setup()
{
  Serial.begin(9600);

  display.begin(SSD1306_SWITCHCAPVCC, 0x3C); //initialize with the I2C addr 0x3C (128x64)
  display.clearDisplay();

  // Initialize DS1307
  Serial.println("Initialize DS1307");;
  clock.begin();

  // If date not set
  if (!clock.isReady())
  {
    // Set sketch compiling time
    clock.setDateTime(__DATE__, __TIME__);

    // Set from UNIX timestamp
    // clock.setDateTime(1397408400);

    // Manual (YYYY, MM, DD, HH, II, SS
    // clock.setDateTime(2014, 4, 13, 19, 21, 00);
  }
}

void loop()
{
  dt = clock.getDateTime();

  Serial.print("Short format witch 12h mode: ");
  Serial.println(clock.dateFormat("d-m-Y", dt));
  Serial.println(clock.dateFormat("h:i:s a", dt));

  display.clearDisplay();
  
  display.setCursor(0,0);  //OLED Display
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.print(clock.dateFormat("d-m-Y", dt));
  display.setCursor(0,19);
  display.println(clock.dateFormat("h:i:sa", dt));
  display.display();
  delay(500);
  display.clearDisplay();
  delay(1000);
}
