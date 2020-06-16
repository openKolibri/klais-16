#ifndef _TM1640_H
#define _TM1640_H

#include "segmentMapping.h"
#include "sixteenSegments.h"

// Pins
#define TM1640_PORT GPIOB
#define TM1640_CLK  GPIO_PIN_5
#define TM1640_DIN  GPIO_PIN_4

// Data command settings
#define AUTO_INC_ADDR 0x40
#define FIXED_ADDR    0x41

// Grid memory locations (0xC0 on boot)
#define GRID_00  0xC0    // [7:0] = SEG8-SEG1
#define GRID_01  0xC1    // [7:0] = SEG8-SEG1
#define GRID_02  0xC2    // [7:0] = SEG8-SEG1
#define GRID_03  0xC3    // [7:0] = SEG8-SEG1
#define GRID_04  0xC4    // [7:0] = SEG8-SEG1
#define GRID_05  0xC5    // [7:0] = SEG8-SEG1
#define GRID_06  0xC6    // [7:0] = SEG8-SEG1
#define GRID_07  0xC7    // [7:0] = SEG8-SEG1
#define GRID_08  0xC8    // [7:0] = SEG8-SEG1
#define GRID_09  0xC9    // [7:0] = SEG8-SEG1
#define GRID_10  0xCA    // [7:0] = SEG8-SEG1
#define GRID_11  0xCB    // [7:0] = SEG8-SEG1
#define GRID_12  0xCC    // [7:0] = SEG8-SEG1
#define GRID_13  0xCD    // [7:0] = SEG8-SEG1
#define GRID_14  0xCE    // [7:0] = SEG8-SEG1
#define GRID_15  0xCF    // [7:0] = SEG8-SEG1

// Display brightness
typedef enum Brightness {
    BRIGHTNESS_OFF = 0x81,
    BRIGHTNESS_01  = 0x88,
    BRIGHTNESS_02  = 0x89,
    BRIGHTNESS_04  = 0x8A,
    BRIGHTNESS_10  = 0x8B,
    BRIGHTNESS_11  = 0x8C,
    BRIGHTNESS_12  = 0x8D,
    BRIGHTNESS_13  = 0x8E,
    BRIGHTNESS_14  = 0x8F
} brightness;


// Prototypes
void tm1640Init(GPIO_TypeDef* clkPort, GPIO_Pin_TypeDef clkPin, GPIO_TypeDef* dioPort, GPIO_Pin_TypeDef dioPin);
void printLetter(uint8_t letter);
void showSegments(uint32_t charMap);
void showLeds(uint8_t *data);
void setBrightness(brightness value);
void sendCommand(uint8_t data[], uint8_t length);
void sendByte(uint8_t byte);

#endif /* _TM1640_H */