#include <stdint.h>
#include <pic32mx.h>
#include "mipslab.h"
#include <stdio.h>
#include <stdlib.h>

//Game specific variables
// Indicates whether the game is currently active or not.
int game_active = 0;
// Represents the mode of the game (e.g., single-player or multiplayer).
int game_mode = 0;
// Stores the score of player 1.
int score_player1 = 0;
// Stores the score of player 2.
int score_player2 = 0;

// Function to handle one-player mode gameplay.
void one_player(int btns) {
  player_movement_one(btns); // Handle player movement for the human player.
  ai_move(); // Simulate movement for the AI player.
  ball_movement(); // Move the ball.
  paddle_hit(); // Check for collisions between the ball and paddles.

  // Clear the display to remove previous game elements.
  clearDisplay();

  // Set pixels for paddle 1, paddle 2, and the ball on the display.
  setPixelArray(paddle1_xPos, paddle1_yPos, paddle_width, paddle_height); // Set pixels for human player's paddle.
  setPixelArray(paddle2_xPos, paddle2_yPos, paddle_width, paddle_height); // Set pixels for AI player's paddle.
  setPixelArray(ball_xPos, ball_yPos, ball_size, ball_size); // Set pixels for the ball.

  // Convert the display 2D array into a 1D image array and update the display.
  translateToDisplay();
  display_image(0, oled_display); // Display the updated image.
}

// Function to handle two-player mode gameplay.
void two_player(int btns) {
  player_movement_two(btns); // Handle player movement for both players.
  ball_movement(); // Move the ball.
  paddle_hit(); // Check for collisions between the ball and paddles.

  // Clear the display to remove previous game elements.
  clearDisplay();

  // Set pixels for both paddles and the ball on the display.
  setPixelArray(paddle1_xPos, paddle1_yPos, paddle_width, paddle_height); // Set pixels for paddle 1.
  setPixelArray(paddle2_xPos, paddle2_yPos, paddle_width, paddle_height); // Set pixels for paddle 2.
  setPixelArray(ball_xPos, ball_yPos, ball_size, ball_size); // Set pixels for the ball.

  // Convert the display array into a 1D image array and update the display.
  translateToDisplay();
  display_image(0, oled_display); // Display the updated image.
}