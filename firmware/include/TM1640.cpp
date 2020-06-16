#include "TM1640.h"

static GPIO_TypeDef*  _tm1640ClkPort;
static GPIO_Pin_TypeDef _tm1640ClkPin;
static GPIO_TypeDef*  _tm1640DioPort;
static GPIO_Pin_TypeDef _tm1640DioPin;

void tm1640Init(GPIO_TypeDef* clkPort, GPIO_Pin_TypeDef clkPin, GPIO_TypeDef* dioPort, GPIO_Pin_TypeDef dioPin) {
  _tm1640ClkPort = clkPort;
  _tm1640ClkPin = clkPin;
  _tm1640DioPort = dioPort;
  _tm1640DioPin = dioPin;

  // Initalsize GPIO
  GPIO_WriteHigh(clkPort, clkPin);
  GPIO_WriteHigh(dioPort, dioPin);
  GPIO_Init(clkPort, clkPin, GPIO_MODE_OUT_PP_LOW_FAST);
  GPIO_Init(dioPort, dioPin, GPIO_MODE_OUT_PP_LOW_FAST);

  setBrightness(BRIGHTNESS_01);

  uint8_t data[] = {AUTO_INC_ADDR};
  sendCommand(data, 1);
}

void setBrightness(brightness value){
    uint8_t data[]= {value};
    sendCommand(data, 1);
}

void printLetter(char letter) {
  showSegments(SixteenSegmentASCII[letter - 32]);
}

void showSegments(uint32_t charMap) {
  uint8_t buffer[17] = {0};
  buffer[0] = 0xC0;
  for (int i = 0; i < 18; i++) {
    if (charMap >> i & 1) {
      for (int j = 0; j < segmentElements[i]; j++) {
        // Calculate the segment and grid mapping
        uint8_t grid = ((segments[i][j] - 1) / 8) + 1;
        uint8_t seg = (segments[i][j] - 1) % 8;
        buffer[grid] |= 1 << seg;
      }
    }
  }
  sendCommand(buffer, 17);
}

void showLeds(uint8_t *data) {
  uint8_t buffer[17] = {0};
  buffer[0] = 0xC0;
  for(int i = 1 ; i < sizeof(buffer) ; i++){
      buffer[i] = data[16-i];
  }
  sendCommand(buffer, 17);
}

void sendCommand(uint8_t data[], uint8_t length) {
  // TM1640_DIN LOW
  GPIO_WriteLow(TM1640_PORT, TM1640_DIN);
  // TM1640_CLK LOW
  GPIO_WriteLow(TM1640_PORT, TM1640_CLK);
  for (int i = 0; i < length; i++) {
    sendByte(data[i]);
  }
  // TM1640_CLK HIGH
  GPIO_WriteHigh(TM1640_PORT, TM1640_CLK);
  // TM1640_DIN HIGH
  GPIO_WriteHigh(TM1640_PORT, TM1640_DIN);
}

void sendByte(uint8_t byte) {
  for (int i = 0; i < 8; i++) {
    if (byte & 0x01 << i) {
      GPIO_WriteHigh(TM1640_PORT, TM1640_DIN);
    } else {
      GPIO_WriteLow(TM1640_PORT, TM1640_DIN);
    }
    // Toggle TM1640_CLK Twice
    GPIO_WriteHigh(TM1640_PORT, TM1640_CLK);
    GPIO_WriteLow(TM1640_PORT, TM1640_CLK);
  }
  // TM1640_DIN HIGH
  GPIO_WriteLow(TM1640_PORT, TM1640_DIN);
}