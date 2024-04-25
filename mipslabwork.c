/* mipslabwork.c

   This file written 2015 by F Lundevall
   Updated 2017-04-21 by F Lundevall

   This file should be changed by YOU! So you must
   add comment(s) here with your name(s) and date(s):

   This file modified 2024-02-29 by Rimon Islam & Arvin Mardukh

   For copyright and licensing, see file COPYING */

#include <stdint.h>   /* Declarations of uint_32 and the like */
#include <pic32mx.h>  /* Declarations of system-specific addresses etc */
#include "mipslab.h"  /* Declatations for these labs */
#include <stdio.h>
#include <stdlib.h>

uint8_t display[32][128];    // 2D Array representing the display buffer with 32 rows and 128 columns
uint8_t oled_display[512];   // 1D Array representing the OLED display buffer with 512 slots

int timeoutcount = 0;        // Counter variable for timeout
int mytime = 0x0001;         // Timer variable initialized to a specific value
char textstring[] = "text, more text, and even more text!";   // Text string variable

// We need to declare the pointers as volatile because we want to avoid
// unintentional compiler optimization might optimize the pointer in 
// such a way that it behaves as if it's not changing its value over time.
volatile int *trisE;  
volatile int *portE;


/* Interrupt Service Routine */
void user_isr( void )
{
  return;

}

/* Lab-specific initialization goes here */
void labinit( void )
{
  // Cast their respective adress as they were declared as volatile
  // PORTE contains the data that decides the input/output configuration
  // TRISE contains the bits that determine whether Port bits are input or output
  trisE = (volatile int*) 0xbf886100; // Address of TRISE register
  portE = (volatile int*) 0xbf886110; // Address of PORTE register¨

  *trisE = *trisE & 0xffffff00; // To mask out the 8 LSBs and sets them to 0 --> outputs
  *portE = 0x00000000; // Set PORTE to 0 so that the LEDs show how many "ticks"
  
  TRISD = TRISD | 0x0fe0; // OR to keep values at 11-5 bits, starting from bit 0. Set as input (BTN 2-4, SW 1-4)
  TRISFSET = 0x2;   // Set as input (BTN 1)
  


    /* Initialization of Timer2 */

  // Set ON-bit (bit 15) to zero to stop the clock
  T2CON = 0x0;

  // Use the set-register for t2con to set prescaling to 1:256 (70 = 0111 0000)
  // Bit 6-4 are the TCKPS that controls prescaling. 2^3 = 8 configurations.
  T2CONSET = 0x70;

  // Reset the timer register
	TMR2 = 0x0;

  // Period register. Set the value to (clock frequency)/(prescaling) and then
  // divide it by 10 because we want it to be 100ms delay, and we have that the
  // main time update and display code only executes per 10th interrupt.
  // The timer ticks up to this value then sets the interrupt flag in IFS0 to 1.

  // 1 Hz = 1 tick/s | 80 MHz means our clock ticks 80 x 10^6 times per second
  // With the prescalar our clock ticks at 80 x 10^6 / 256 times per second
  // Ticks = clock cycles
  // PR2 register wants us to tell it after how many clock cycles it should interupt
  // We want it to stop after 0.1 s and we know it takes the clock 
  // 1 second to complete 80 x 10^6 / 256 clock cycles
  // Therefore if we tell PR2 to stop after (80 000 000 / 256) / 10 clock cycles
  // This will make the clock interupt every 0.1 second.
	PR2 = ((80000000 / 256) / 10);

  // Set ON-bit (bit 15) to one to start the clock
	T2CONSET = 0x8000;

  return;
}

/* This function is called repetitively from the main program */
// This code is called repeatedly from mipslabmain
void labwork(void) {
  int btns = getbtns(); // Read the state of the buttons.
  int sw = getsw();     // Read the state of the switches.

  // Check if switch 1 is activated.
  if (sw & 0x1) {
    quit(); // Quit the program if switch 1 is activated.
  }

  // Check if the game is not active (not currently in progress).
  if (!game_active) {
    menu(btns); // If not active, display the menu and handle menu navigation/selection.
  }

  // Check if the game is active and the game mode is set to Two Player.
  if ((game_active) && (game_mode == 1)) {
    two_player(btns); // If conditions are met, call the function for two-player mode.
  }
  // Check if the game is active and the game mode is set to One Player.
  if ((game_active) && (game_mode == 2)) {
    one_player(btns); // If conditions are met, call the function for one-player mode.         
  }


  /* Checking the timeout event flag for T2 (bit 8 in IFS0) */

  // AND with 0001 0000 0000, if the 8th bit is 1 then increment count
  if((IFS(0) & 0x100) && (game_active)){  // The game has to be active
    timeoutcount++;
    // Reset the event flag bit with the clear register
    IFSCLR(0) = 0x100;

  }

  if(timeoutcount == 10){
    // Increment the timer by 1 
    time2string( textstring, mytime );
    tick( &mytime );
    // Reset the counter
    timeoutcount = 0;
  }
}