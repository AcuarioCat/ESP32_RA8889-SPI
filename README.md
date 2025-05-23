# ESP32_RA8889-SPI
## A RA8889 SPI DRIVER library for ESP32 boards and variants.
## Based onthe TeensyRA8889-SPI driver by wwatson4506.

This library is designed to be used with the ESP32__RA8889-GFX-Common library and can be found here:
- https://github.com/AcuarioCat/ESP32_RA8889-GFX-Common

Communication with the ESP32 is accomplished using SPI.

![https://github.com/AcuarioCat/ESP32_RA8889-GFX-Common/blob/main/extras/RA8889_GFX_Common.jpg](https://github.com/AcuarioCat/ESP32_RA8889-GFX-Common/blob/main/extras/RA8889_GFX_Common.jpg)

## TOUCH SCREEN
The capacitive touch controller now used on the ER-TFTM101-1 is the Goodix GT9271. I2C communication is used with the GT9371 controller.
A minimal driver adapted from the arduino-goodix library can be found here: 
- https://github.com/wwatson4506/Arduino-goodix-GT9271
***

## LIBRARY INSTALLATION
1. Unzip this library to the **Arduino/libraries** folder.
2. Unzip **ESP32_RA8889-GFX-Common**  library to the **Arduino/libraries** folder.
3. Download **ILI9341_fonts** [https://github.com/wwatson4506/ILI9341_fonts](https://github.com/wwatson4506/ILI9341_fonts) and install into the **Arduino/libraries** folder.
***

# PINOUTS

### CONNECTING THE ESP32 TO THE ER-TFT101B4-1-6105 in SPI 4 wire  mode:
40 pin dual inline connector pinouts for SPI buss mode can be found here:

https://www.buydisplay.com/download/interfacing/ER-TFTM101-1_CTP_Interfacing.pdf

### ESP32 <--------------> RA8889
```
SPI usage.
PIN                            PIN
- CS   25 -------------------> Pin 05 SCS
- SCK  19 -------------------> Pin 08 SCLK
- MOSI 17 -------------------> Pin 07 SDI
- MISO 18 -------------------> Pin 06 SDO
- RST  27 -------------------> Pin 11 RESET
- BL   26 -------------------> Pin 14 BACKLIGHT
Power and Grounds
- TFT 5V --------------------> 3,4,37,38
- GND -----------------------> 1,2,13,31,39,40
NOTE: All power and ground pins should be connected.

Touch Screen (ER-TFT101B4-1-6105 40 pin dual inline connector)
  Teensy 4.1            RA8889
- 3.3V ---------------> CPT_/RST 36
- 28   ---------------> CPT_INT  33
- 25   ---------------> CPT_SDA  34
- 24   ---------------> CPT_SCL  35

```
***
### CONFIG FILE
Both SPI Parallel and 8080 libraries have config file.
Config file for SPI:
```
/* RA8889_Config_SPI.h
 A file to place user defines and configs.
*/

#ifndef RA8889_CONFIG_SPI_H
#define RA8889_CONFIG_SPI_H

// Uncomment next line to increase SDRAM and CORE clock speeds.
//#define USE_FAST_CLOCK_MODE

// SPI hardware settings
#define USE_SPI  // Needed for writeRect() in RA8876_GFX
#define BACKLITE	26
#define LCD_RESET	27
#define LCD_CS		25
#define S_MOSI		18
#define S_MISO		17
#define S_SCK		19

// Example usage in sketch: RA8889_t3 gfx = RA8889_t3(LCD_CS, LCD_RESET, S_MOSI, S_SCK, S_MISO);

// Uncomment define below to use 47MHz SPI clock. Default is 30MHz.
// We start off slow in case of long connecting wires. If having problems,
// the SPI clock speed can be reduced further.
//
// #define USE_SPI_47000000
//

// Uncomment to use FT5206 touch. (Not used on the ER-TFTM1010-1)
#define USE_FT5206_TOUCH

#endif // RA8889_CONFIG_H
```

### MINIMAL SKETCH EXAMPLE
```
// sketch.ino

#include "Arduino.h"
#include "RA8889_Config_SPI.h"
#include <RA8889_t3.h>
#include <SPI.h>

// RA8889_CS and RA8889_RESET are defined in
// src/RA8889_Config_SPI.h.
RA8889_t3 gfx = RA8889_t3(LCD_CS, LCD_RESET, S_MOSI, S_SCK, S_MISO);


void setup() {
  Serial.begin(115200);
  while (!Serial && millis() < 3000) {} //wait for Serial Monitor (3 seconds).

#if defined(USE_SPI_47000000)
  gfx.begin(40000000);
#else
  gfx.begin(); // default SPI clock speed is 30000000 MHz 
#endif
  ... // Rest of user setup code.
}

void loop() {
 ... // Users loop code.
}

```

***

## Examples Folder Listings:

Example sketches can be found in the TeensyRA8876-8080 and TeensyRA8876-SPI examples folders.

- gauges  ---------------------->  A Sumotoy example originally created for the RA8875.
- graphicCursor ------------->  A demonstration of defining and using a graphical mouse pointer. A USB mouse is required. Also demonstrates single and double mouse button clicks.
- graphics --------------------->  Demonstrates common graphics usage, lines, circles, rectangles and more.
- ILI_ADA_FontTest4 -------> Demonstrates usage of ILI9341 and Adafruit fonts on the RA8876.
- MemoryTransfer -----------> Shows usage of many BTE (Block Transfer Engine) functions.
- pipTest ------------------------> Example of PIP (Picture In Picture) usage.
- RA8889_pictureEmbed --> Displays 16Bit color images. Also demonstrates rotation.
- RA8889Rotate --------------> Also demontrates use of rotation.
- scroll ---------------------------> Simple demonstration of scrolliing screen up and down.
- treedee ------------------------> Demonstrates a spinning 3D wire cube.
- UserDefinedFonts ----------> Demonstrates loading  user define fonts into pattern ram.   Fonts can also be loaded from an SD card or USB drive.


***
# CREDITS
Major work on this library was done by the following PJRC forum members:

@mjs513, @KurtE, @MorganS, @rezo and @K7MDL (Keith).

They added functions to be compatible with other display libraries, performed a major rework and helped in debugging the code. The 8080 parallel FlexIO driver is based on work done by @rezo.

***

# REFERENCES
ER-TFT101B4-1-6105 10.1" TFT from BuyDisplay:
- https://www.buydisplay.com/serial-spi-i2c-10-1-inch-tft-lcd-module-dislay-w-ra8889-optl-touch-panel
- https://www.buydisplay.com/download/ic/RA8889.pdf

PJRC Forum Threads:
- https://forum.pjrc.com/threads/58565-RA8876LiteTeensy-For-Teensy-T36-and-T40
- https://forum.pjrc.com/index.php?threads/ra8876-parallel-display-library-testing.75345/
- https://forum.pjrc.com/index.php?threads/recommendations-for-10-tft-display-with-touchscreen-for-teensy-4-1.75666/
***

# This is WIP.   USE AT YOUR OWN RISK.  There are no guarantees when using this library. More to come.
