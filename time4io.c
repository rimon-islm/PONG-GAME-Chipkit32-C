#include <stdint.h>
#include <pic32mx.h>
#include "mipslab.h"

// The switches SW4 through SW1 are connected to bits 11 through 8 of Port D.
// Shift then mask to give the data bits for SW4-SW1 to LSB, the rest is set to 0
int getsw(){
  return ((PORTD>>8) & 0x000f);
}

// The buttons BTN4, BTN3, and BTN2, are connected to bits 7, 6 and 5 of Port D.
// Shift then mask to give the data bits for BTN4-BTN2 to LSB, the rest is set to 0
// Extract bit 1 for representing the push button (PORTF)
int getbtns(){
  return ((((PORTD >> 5) & 0x0007) << 1) | ((PORTF >> 1) & 0x1));
}
