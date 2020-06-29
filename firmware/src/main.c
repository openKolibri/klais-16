// main.c controller for segmented display
// Copyright (C) 2020 Kolibri - Sawaiz Syed

// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <https://www.gnu.org/licenses/>.

// STM8 Libraries
#include <stm8s.h>

// C Libraries
#include <stdio.h>
#include <string.h>

#include "TM1640.cpp"
#include "TM1640.h"

// [17:17] ASCII mode Current Char/ Control byte
// [15:16] Brightness Control Mode
// [13:16] Segment Control Mode
// [00:16] Led Control Mode
typedef struct DataBuffer {
  unsigned char data[17];
  int8_t txMode;
  int8_t rxMode;
  int8_t marker;
} DataBuffer;
// Default Operating Mode is ASCII
DataBuffer buffer;

// Stores the config read from pads
uint8_t config = 0x00;


// Character Operating Modes
typedef enum Modes {
  ASCII              = 0x00,   // No Control Code
  SEGEMENT_CONTROL   = 0x11,   // DC1
  LED_CONTROL        = 0x12,   // DC2
  BRIGHTNESS_CONTROL = 0x13,   // DC3
  BAUDRATE_CONTROL   = 0x14    // DC4
} Modes;


INTERRUPT_HANDLER(UART1_TX_IRQHandler, 17) {
  switch (buffer.txMode) {
      case LED_CONTROL:
        if (buffer.marker > 0) {
          buffer.marker--;
          UART1_SendData8(buffer.data[buffer.marker]);
        } else {
          // Reset marker postion
          buffer.marker = 16;
          // ASCII mode: Replace buffer with new byte
          buffer.data[16] = UART1_ReceiveData8();
          buffer.txMode = buffer.data[16];
          UART1_ITConfig(UART1_IT_TXE, DISABLE);
        }
        break;

    case SEGEMENT_CONTROL:
      if (buffer.marker > 13) {
        buffer.marker--;
        UART1_SendData8(buffer.data[buffer.marker]);
      } else {
        // Reset marker postion
        buffer.marker = 16;
        // ASCII mode: Replace buffer with new byte
        buffer.data[16] = UART1_ReceiveData8();
        buffer.txMode = buffer.data[16];
        UART1_ITConfig(UART1_IT_TXE, DISABLE);
      }
      break;

    case BRIGHTNESS_CONTROL:
      if (buffer.marker > 15) {
        buffer.marker--;
        UART1_SendData8(buffer.data[buffer.marker]);
      } else {
        // Reset marker postion
        buffer.marker = 16;
        // ASCII mode: Replace buffer with new byte
        buffer.data[16] = UART1_ReceiveData8();
        buffer.txMode = buffer.data[16];
        UART1_ITConfig(UART1_IT_TXE, DISABLE);
      }
      break;

    default:
      // ASCII mode: Replace buffer with new byte
      buffer.marker = 16;
      buffer.data[16] = UART1_ReceiveData8();
      buffer.txMode = buffer.data[16];
      UART1_ITConfig(UART1_IT_TXE, DISABLE);
      break;
  }
}

INTERRUPT_HANDLER(UART1_RX_IRQHandler, 18) {
  // Reset timeout for display refresh
  TIM4_SetCounter(0x00);
  TIM4_ClearITPendingBit(TIM4_IT_UPDATE);
  TIM4_ITConfig(TIM4_IT_UPDATE, ENABLE);

  // Process newly recived Character based on recieve mode
  switch (buffer.rxMode) {
      case LED_CONTROL:
        // Recieve 16 additional bytes for led data
        buffer.data[--buffer.marker] = UART1_ReceiveData8();
        if (buffer.marker < 1) {
          buffer.txMode = LED_CONTROL;
          buffer.rxMode = ASCII;
        }
        break;

    case SEGEMENT_CONTROL:
      // Recieve 3 additional bytes for segment data
      buffer.data[--buffer.marker] = UART1_ReceiveData8();
      if (buffer.marker < 14) {
        buffer.txMode = SEGEMENT_CONTROL;
        buffer.rxMode = ASCII;
      }
      break;

    case BRIGHTNESS_CONTROL:
      // Recieve a additional byte for brightness
      buffer.data[--buffer.marker] = UART1_ReceiveData8();
      buffer.txMode = BRIGHTNESS_CONTROL;
      buffer.rxMode = ASCII;
      break;

    default:
      buffer.rxMode = UART1_ReceiveData8();
      // Forward the current buffered data
      buffer.marker = 16;
      UART1_ITConfig(UART1_IT_TXE, ENABLE);
      UART1_SendData8(buffer.data[16]);
  }
}

// Timer overflow interupt

// Updates the display only when timer overflows and then stops the timer 
// Timer get reset and started when a new charachter has been processed
// Timer duration is 2.5x the baud rate
// So that if multiple charachters are sent in series, the display only updates if 
// a charachter rests in the buffer for over 2.5 charachters.
INTERRUPT_HANDLER(TIM4_UPD_OVF_IRQHandler, 23){
    GPIO_WriteReverse(GPIOD, GPIO_PIN_3);
    TIM4_ITConfig(TIM4_IT_UPDATE, DISABLE);
    switch (buffer.txMode) {
        case LED_CONTROL:
          showLeds(buffer.data);
          break;
        case SEGEMENT_CONTROL:
          showSegments(0x3FFFF & ( (uint32_t)buffer.data[13] << 16 | (uint32_t)buffer.data[14] << 8) |  (uint32_t)buffer.data[15] );
          break;

        case BRIGHTNESS_CONTROL:
          setBrightness(buffer.data[15]);
          break;

        default:
          printLetter(buffer.data[16]);
    }
}



void main() {
  // Clock Prescaler 1, 16MHz
  CLK_HSIPrescalerConfig(CLK_PRESCALER_HSIDIV1);

  GPIO_DeInit(GPIOA);
  GPIO_DeInit(GPIOB);
  GPIO_DeInit(GPIOC);
  GPIO_DeInit(GPIOD);

  // Setup config pins, Input, WeakPullup
  GPIO_Init(GPIOC, GPIO_PIN_3, GPIO_MODE_IN_PU_NO_IT);
  GPIO_Init(GPIOC, GPIO_PIN_4, GPIO_MODE_IN_PU_NO_IT);
  GPIO_Init(GPIOC, GPIO_PIN_5, GPIO_MODE_IN_PU_NO_IT);
  GPIO_Init(GPIOC, GPIO_PIN_6, GPIO_MODE_IN_PU_NO_IT);
  GPIO_Init(GPIOC, GPIO_PIN_7, GPIO_MODE_IN_PU_NO_IT);
  GPIO_Init(GPIOD, GPIO_PIN_2, GPIO_MODE_IN_PU_NO_IT);
  GPIO_Init(GPIOD, GPIO_PIN_3, GPIO_MODE_IN_PU_NO_IT);

  // Read configuration
  config |= !GPIO_ReadInputPin(GPIOC, GPIO_PIN_3) << 0;
  config |= !GPIO_ReadInputPin(GPIOC, GPIO_PIN_4) << 1;
  config |= !GPIO_ReadInputPin(GPIOC, GPIO_PIN_5) << 2;
  config |= !GPIO_ReadInputPin(GPIOC, GPIO_PIN_6) << 3;
  config |= !GPIO_ReadInputPin(GPIOC, GPIO_PIN_7) << 4;
  config |= !GPIO_ReadInputPin(GPIOD, GPIO_PIN_2) << 5;
  config |= !GPIO_ReadInputPin(GPIOD, GPIO_PIN_3) << 6;

  // Set baud rate based on config
  uint32_t bauds[] = {115200, 110, 300, 600, 1200, 2400, 4800, 9600, 19200, 38400, 57600, 128000, 230400, 256000, 460800, 1000000};
  uint32_t baud = bauds[(config & 0X1E) >> 1];
 
  // Starting buffer marker location
  buffer.marker = 16;
  buffer.txMode = ASCII;
  buffer.rxMode = ASCII;
  // Starting charachter is space
  buffer.data[16] = ' ';

  UART1_DeInit();
  // UART1 configured as follow:
  //       - BaudRate = baud
  //       - Word Length = 8 Bits
  //       - One Stop Bit
  //       - No parity
  //       - Receive and transmit enabled
  //       - UART1 Clock disabled
  UART1_Init(baud, UART1_WORDLENGTH_8D, UART1_STOPBITS_1,
             UART1_PARITY_NO, UART1_SYNCMODE_CLOCK_DISABLE,
             UART1_MODE_TXRX_ENABLE);
  UART1_ITConfig(UART1_IT_RXNE_OR, ENABLE);
  UART1_Cmd(ENABLE);

  // Display refresh timer
  //   - CLK = 16 MHZ
  //   - DIV 128
  //   - OVF @ 125
  //   - 1ms
  TIM4_DeInit();
  TIM4_TimeBaseInit(TIM4_PRESCALER_128, 125);
  TIM4_ITConfig(TIM4_IT_UPDATE, ENABLE);
  TIM4_Cmd(ENABLE);

  // Enable interupts
  enableInterrupts();

  // Set PB3 to Push pull
  GPIO_Init(GPIOD, GPIO_PIN_3, GPIO_MODE_OUT_PP_LOW_FAST);

  tm1640Init(GPIOB, GPIO_PIN_5, GPIOB, GPIO_PIN_4);
  setBrightness(BRIGHTNESS_14);
  printLetter(buffer.data[buffer.marker]);

  while (1) {
  }
}
