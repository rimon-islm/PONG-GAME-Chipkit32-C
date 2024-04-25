#include <stdint.h>
#include <pic32mx.h>
#include "mipslab.h"
#include <stdio.h>
#include <stdlib.h>

// Paddle specific variables
int paddle_height = 8;  // Height of the paddle
int paddle_width = 3;   // Width of the paddle
int paddle_speed = 1;   // Speed of paddle movement

int paddle1_xPos = 0;  // Initial X position of paddle 1
int paddle1_yPos = 32 / 2 - 4;  // Initial Y position of paddle 1

int paddle2_xPos = 128 - 4;  // Initial X position of paddle 2
int paddle2_yPos = 32 / 2 - 4;  // Initial Y position of paddle 2

int paddle2_up = 0;  // Flag indicating upward movement of paddle 2
int paddle2_down = 0;  // Flag indicating downward movement of paddle 2
int paddle1_up = 0;  // Flag indicating upward movement of paddle 1
int paddle1_down = 0;  // Flag indicating downward movement of paddle 1

// Ball specific variables
int ball_size = 2;  // Diameter of the ball
int ball_speedx = 1;  // Horizontal speed of the ball
int ball_speedy = 1;  // Vertical speed of the ball

int ball_xPos = 128 / 2 - 2;  // Initial X position of the ball
int ball_yPos = 32 / 2;  // Initial Y position of the ball


void player_movement_two(btns) {
  // Reset paddle direction flags.
  // Player 2 paddle direction flags
  paddle2_up = 0;
  paddle2_down = 0;
  // Player 1 paddle direction flags
  paddle1_up = 0;
  paddle1_down = 0;

  // Check button input and adjust paddle positions accordingly for both players.
  // Player 2 controls:
  if ((btns & 0x1) && (paddle2_yPos < (32 - paddle_height))) {  // Secures that we dont go out of bounds
    paddle2_yPos += paddle_speed; // Move paddle 2 up.
    paddle2_up = 1; // Set flag indicating paddle 2 is moving up to next rows in display.
  }
  if ((btns & 0x2) && (paddle2_yPos > 0)) {
    paddle2_yPos -= paddle_speed; // Move paddle 2 down.
    paddle2_down = 1; // Set flag indicating paddle 2 is moving down to next rows.
  }
  // Player 1 controls:
  if ((btns & 0x4) && (paddle1_yPos < (32 - paddle_height))) {  // Secures that we dont go out of bounds
    paddle1_yPos += paddle_speed; // Move paddle 1 up.
    paddle1_up = 1; // Set flag indicating paddle 1 is moving up to next rows.
  }
  if ((btns & 0x8) && (paddle1_yPos > 0)) {
    paddle1_yPos -= paddle_speed; // Move paddle 1 down.
    paddle1_down = 1; // Set flag indicating paddle 1 is moving down to next rows.
  }
}

void player_movement_one(btns) {
  // Reset paddle direction flags.
  paddle1_up = 0;
  paddle1_down = 0;
  // Player 1 controls:
  if ((btns & 0x4) && (paddle1_yPos < (32 - paddle_height))) {  // Secures that we dont go out of bounds
    paddle1_yPos += paddle_speed; // Move paddle 1 up.
    paddle1_up = 1; // Set flag indicating paddle 1 is moving up to next rows in display.
  }
  if ((btns & 0x8) && (paddle1_yPos > 0)) {
    paddle1_yPos -= paddle_speed; // Move paddle 1 down.
    paddle1_down = 1; // Set flag indicating paddle 1 is moving down to next rows in display.
  }
}

// Function to update the position of the ball based on its speed and handle ball movement logic.
void ball_movement() {
  ball_xPos += ball_speedx; // Update the horizontal position of the ball
  ball_yPos += ball_speedy ; // Update the vertical position of the ball

  // Check for collisions with the top and bottom boundaries of the display
  if (ball_yPos < 1 || ball_yPos > (31 - ball_size)) {
    ball_speedy = -(ball_speedy); // Reverse the vertical direction of the ball
  }
}


// Function to control the movement of the AI-controlled paddle (Paddle 2).
void ai_move(void) {
  paddle2_down = 0; // Reset the flag indicating paddle 2 is moving down
  paddle2_up = 0; // Reset the flag indicating paddle 2 is moving up

  // Check if the ball's vertical position is a multiple of 4
  if ((ball_yPos % 4) == 0) {
    // If the ball is above the AI paddle and the paddle is not at the top boundary
    if ((ball_yPos < paddle2_yPos) && (paddle2_yPos > 0)) {
      paddle2_yPos -= paddle_speed; // Move the paddle up
      paddle2_up = 1; // Set the flag indicating paddle 2 is moving up
    }
    // If the ball is below the AI paddle and the paddle is not at the bottom boundary
    if ((ball_yPos > paddle2_yPos) && (paddle2_yPos < (32 - paddle_height))) {
      paddle2_yPos += paddle_speed; // Move the paddle down
      paddle2_down = 1; // Set the flag indicating paddle 2 is moving down
    }
  }
}