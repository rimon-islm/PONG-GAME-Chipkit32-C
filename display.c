#include <stdint.h>
#include <pic32mx.h>
#include "mipslab.h"
#include <stdio.h>
#include <stdlib.h>

// Set array slots to ones or zeros in the 2D array.
// Function to set array slots to ones within a specified rectangle region in the 2D array.
void setPixelArray(int xPos, int yPos, int width, int height) {
  int row, column;

  // Loop through each row in the display array (32 rows)
  for (row = 0; row < 32; row++) {
    // Loop through each column in the display array (128 columns)
    for (column = 0; column < 128; column++) {
      // Check if the current pixel is within the specified rectangle region
      if (row >= yPos && row <= (yPos + height) && column >= xPos && column <= (xPos + width)) {
        // If the pixel is within the rectangle region, set it to 1 (turn it on)
        display[row][column] = 1;
      }
    }         
  }
}

// Translate the 2D array into the 1D array with 512 slots.
void translateToDisplay() {
  int page, column, row;
  uint8_t powerOfTwo = 1; // Initialize powerOfTwo to represent the first bit.
  uint8_t oledNumber = 0; // Initialize oledNumber to store pixel data for one column.

  // Loop through each page of the display (4 pages in total).
  for(page = 0; page < 4; page++) {
    // Loop through each column of the display (128 columns in total).
    for(column = 0; column < 128; column++) {
      powerOfTwo = 1; // Reset powerOfTwo to represent the first bit.
      oledNumber = 0; // Reset oledNumber to store pixel data for one column.

      // Loop through each row within the current column.
      for(row = 0; row < 8; row++) {
        // Check if the pixel at the current position is set (non-zero).
        if(display[8 * page + row][column]) {
          // If the pixel is set, set the corresponding bit in oledNumber to 1.
          // The |= operator performs a bitwise OR operation to set the bit.
          oledNumber |= powerOfTwo;
        }
        // Move to the next bit position (representing the next row) for the next iteration.
        powerOfTwo <<= 1; // Left shift powerOfTwo by 1 to represent the next bit.
      }
      
      // Store the pixel data (oledNumber) for the current column in the 1D oled_display array.
      // The index in oled_display is calculated based on the current column and page.
      oled_display[column + page * 128] = oledNumber;
    }
  }
}

// Function to clear the display by setting all pixels to 0.
void clearDisplay() {
  int row, column, i; // Declare loop counters.

  // Loop through each row of the display array (32 rows).
  for(row = 0; row < 32; row++) {
    // Loop through each column of the display array (128 columns).
    for(column = 0; column < 128; column++) {
      // Set the pixel at the current position to 0 (turn it off).
      display[row][column] = 0;
    }
  }

  // Loop through each element of the oled_display array (512 elements).
  for (i = 0; i < 512; i++) {
    // Set the pixel data in the 1D oled_display array to 0 (turn it off).
    oled_display[i] = 0;
  }
}
