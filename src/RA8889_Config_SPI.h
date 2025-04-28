/* RA8889_Config_SPI.h
 A file to place user defines and configs.
*/

#ifndef RA8889_CONFIG_SPI_H
#define RA8889_CONFIG_SPI_H

// Uncomment next line to increase SDRAM and CORE clock speeds.
//#define USE_FAST_CLOCK_MODE

// SPI hardware settings
#define USE_SPI // Needed for writeRect() in RA8889_GFX

#define RA8889_CS 10
#define RA8889_RESET 9
//#define RA8889_CS 30
//#define RA8889_RESET 28

//Uncomment to to use 47MHz SPI clock. Default is 30MHz.
#define USE_SPI_47000000

// Uncomment to use BL pin else wired to 3.3V
//#define BACKLITE 5 //External backlight control connected to this Arduino pin
//#define BACKLITE 29 // Kurt's DB5 shield

// Uncomment to use FT5206 touch.
#define USE_FT5206_TOUCH

#endif // RA8889_CONFIG_H
