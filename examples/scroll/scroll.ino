// scroll.ino
// Simple example of Scrolling text down and up
// on the RA8889. The method used is kind of slow
// and needs to be optimized.
#include "Arduino.h"
#include "RA8889_Config_SPI.h"
#include <SPI.h>
#include <RA8889_t3.h>
#include "font8x16.h"

RA8889_t3 tft = RA8889_t3(RA8889_CS, RA8889_RESET); //Using standard SPI pins

// Array of RA8889 Basic Colors
PROGMEM uint16_t myColors[] = {
	0x0000,	0xffff,	0xf800,	0xfc10,	0x8000,	0x07e0,	0x87f0,	0x0400,
	0x001f,	0x051f,	0x841f,	0x0010,	0xffe0,	0xfff0,	0x8400,	0x07ff,
	0x87ff,	0x0410,	0xf81f,	0xfc1f,	0x8010,	0xA145
};

int i = 0, j = 0;
int color = 1;
void setup() {
  //I'm guessing most copies of this display are using external PWM
  //backlight control instead of the internal RA8889 PWM.
  //Connect a Teensy pin to pin 14 on the display.
  //Can use analogWrite() but I suggest you increase the PWM frequency first so it doesn't sing.
#if defined(BACKLITE)
  pinMode(BACKLITE, OUTPUT);
  digitalWrite(BACKLITE, HIGH);
#endif

  Serial.begin(115200);
  while (!Serial && millis() < 1000) {} //wait for Serial Monitor

#if defined(USE_SPI_47000000)
  tft.begin(47000000); // Max is 47000000 MHz (using short 3" wires)
#else
  tft.begin(); // default SPI clock speed is 30000000 MHz 
#endif

  tft.fontLoadMEM((char *)font8x16);
  tft.fillScreen(myColors[11]);
  tft.fillStatusLine(myColors[11]);
  tft.setFontSize(1,false);
  tft.setTMargins(0, 0, 0, 1); //so scroll doesn't erase the status bar
  tft.setCursor(0,0);
  tft.printStatusLine(0,myColors[13],myColors[11],"scroll_down(), scroll_up()");
}

void loop() {
  tft.setFontSource(0);
  tft.setFontSize(1,true);
  tft.setCursor(0,0);
  for(i = 32; i < 256; i++) {
    if(color == 22) color = 1;
    tft.setTextColor(myColors[color++] , myColors[11]);
    tft.write(i);
  }
  tft.setTextColor(myColors[1] , myColors[11]);
  while(j++ < 10) {
    for(i = 0; i < 21; i++) tft.scrollDown();
    for(i = 0; i < 21; i++) tft.scrollUp();
  }
  j = 0;
  delay(2000);
}
