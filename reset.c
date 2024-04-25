#include <stdint.h>
#include <pic32mx.h>
#include "mipslab.h"
#include <stdio.h>
#include <stdlib.h>

void quit() {
  delay(1000);              // Delay for 1000 milliseconds
  PORTE = 0x0;              // Set PORTE to 0, the leds is off

  // Makes us return to our menu
  game_active = 0;          // Set game_active flag to 0
  game_mode = 0;            // Reset game_mode to 0
  score_player1 = 0;        // Reset score for player 1
  score_player2 = 0;        // Reset score for player 2
  mytime = 0x0001;          // Reset mytime variable to initial value

  string_clear();           // Clear strings in display
  clearDisplay();           // Clear the display buffer
  translateToDisplay();     // Translate pixel data to display
  display_image(0, oled_display);  // Display the image on the OLED display
}

// Function to reset the game state and display initial positions.
void reset_game() {

  // Reset paddle positions to initial values.
  // Set the paddle position to the leftmost edge.
  paddle1_xPos = 0; // Center the paddle horizontally.
  paddle1_yPos = 32 / 2 - 4; // Center the paddle vertically.
  
  // Set the paddle position to the rightmost edge.
  paddle2_xPos = 128 - 4; // Center the paddle horizontally.
  paddle2_yPos = 32 / 2 - 4; // Center the paddle vertically.

  // Reset ball position to the center of the display.
  ball_xPos = 128 / 2 - 2; // Center the ball horizontally.
  ball_yPos = 32 / 2; // Center the ball vertically.

  // Set the ball speed based on the current score comparison.
  if (score_player1 > score_player2) {
    ball_speedx = -1; // Move the ball towards player 1.
  }
  else if (score_player1 < score_player2) {
    ball_speedx = 1; // Move the ball towards player 2.
  }
  else {
    ball_speedx = 1; // Move the ball in a default direction if scores are equal.
  }
  ball_speedy = 1; // Reset the vertical speed of the ball.

  // Clear the display to remove previous game elements.
  clearDisplay();
 
  // Set pixels for paddle 1, paddle 2, and the ball on the display.
  setPixelArray(paddle1_xPos, paddle1_yPos, paddle_width, paddle_height); // Set pixels for paddle 1.
  setPixelArray(paddle2_xPos, paddle2_yPos, paddle_width, paddle_height); // Set pixels for paddle 2.
  setPixelArray(ball_xPos, ball_yPos, ball_size, ball_size); // Set pixels for the ball.

  // Convert the display array into a 1D image array and update the display.
  translateToDisplay();
  display_image(0, oled_display); // Display the updated image.
  delay(1000); // Delay for 1 second to allow the players to see the initial state.
}

// Function to clear all strings displayed on the OLED display.
void string_clear() {
  // Clear each string displayed on the OLED display.
  display_string(0, ""); 
  display_string(1, ""); 
  display_string(2, ""); 
  display_string(3, "");
  display_string(4, ""); 

  // Update the display to remove the cleared strings.
  display_update();
}