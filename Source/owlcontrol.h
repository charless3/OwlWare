#ifndef __OWL_CONTROL_H
#define __OWL_CONTROL_H

#include <stdbool.h>
#include <stdint.h>
#include "stm32f4xx.h"
#include "device.h"
#include "gpio.h"

#ifdef __cplusplus
 extern "C" {
#endif

   bool isClockExternal();
   uint32_t* getDeviceId();
   void jump_to_bootloader();
   char* getFirmwareVersion();

   typedef enum {
     NONE  = 0,
     GREEN = LED_GREEN,
     RED   = LED_RED
   }  LedPin;

   LedPin getLed();

   inline void setLed(LedPin led){
     clearPin(LED_PORT, led ^ (LED_RED|LED_GREEN));
     setPin(LED_PORT, led);
   }

   inline void toggleLed(){
     togglePin(LED_PORT, LED_RED|LED_GREEN);
   }

   inline void blink(){
     togglePin(LED_PORT, LED_RED|LED_GREEN);
     togglePin(LED_PORT, LED_RED|LED_GREEN);
   }

   inline void debugSet(){
     setPin(GPIOB, GPIO_Pin_1); // PB1, DEBUG LED
   }

   inline void debugClear(){
     clearPin(GPIOB, GPIO_Pin_1); // PB1, DEBUG LED
   }

   inline void debugToggle(){
     togglePin(GPIOB, GPIO_Pin_1); // PB1, DEBUG LED
   }

   void ledSetup();

   void adcSetup();
   int16_t getAnalogValue(uint8_t index);
   int16_t* getAnalogValues();

   inline bool isStompSwitchPressed(){
     return getPin(SWITCH_A_PORT, SWITCH_A_PIN);
   }

   inline bool isPushButtonPressed(){
     return !getPin(SWITCH_B_PORT, SWITCH_B_PIN);
   }

   inline bool isPushGatePressed(){
     return !getPin(SWITCH_A_PORT, SWITCH_A_PIN);
   }

   void setupSwitchA(void (*f)());
   void setupSwitchB(void (*f)());

   void setupExpressionPedal();
   bool hasExpressionPedal();

   void exitProgram(bool isr);
   void updateProgramIndex(uint8_t index);
   void togglePushButton();

   int8_t getErrorStatus();
   void setErrorStatus(int8_t err);
   void setErrorMessage(int8_t err, const char* msg);
   void setParameterValues(int16_t* values, int size);
#define ASSERT(cond, msg) do{if(!(cond))setErrorMessage(PROGRAM_ERROR, msg);}while(0)

#define NO_ERROR         0x00
#define HARDFAULT_ERROR  0x10
#define BUS_ERROR        0x20
#define MEM_ERROR        0x30
#define NMI_ERROR        0x40
#define USAGE_ERROR      0x50
#define PROGRAM_ERROR    0x60

#ifdef __cplusplus
}
#endif

#endif /* __OWL_CONTROL_H */
