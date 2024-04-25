#include <stdint.h>
#include <pic32mx.h>
#include "mipslab.h"
#include <stdio.h>
#include <stdlib.h>

// Function to handle collisions between the ball and the paddles, as well as out-of-bounds conditions.
void paddle_hit() {
  // Check collision with Paddle 1 (Left Paddle)
  if (ball_xPos == paddle_width) {  // If the ball reaches the position of the left paddle

   /* This nested condition checks if the ball's y-position overlaps with the y-range of the left paddle. 
      Specifically, it checks if the bottom edge of the ball is below the top edge of the left paddle, 
      and if the top edge of the ball is above the bottom edge of the left paddle.*/
    if (((ball_yPos + ball_size) > paddle1_yPos) && (ball_yPos - ball_size) < (paddle1_yPos + paddle_height)) {
      ball_speedx = -(ball_speedx);  // Reverse the horizontal direction of the ball
    }
  }
  // If the ball goes beyond the left boundary
  else if(ball_xPos < -21) {
    // Player 2 scores a goal
    goal(2);
  }
  // Check collision with Paddle 2 (Right Paddle)
  if (ball_xPos == (128 - paddle_width - 4)) {  // If the ball reaches the position of the right paddle

  /* This nested condition checks if the ball's y-position overlaps with the y-range of the right paddle. 
      Specifically, it checks if the bottom edge of the ball is below the top edge of the right paddle, 
      and if the top edge of the ball is above the bottom edge of the right paddle.*/
    if (((ball_yPos + ball_size) > paddle2_yPos) && (ball_yPos - ball_size) < (paddle2_yPos + paddle_height)) {
      ball_speedx = -(ball_speedx); // Reverse the horizontal direction of the ball
    }
  }
  // If the ball goes beyond the right boundary
  else if (ball_xPos > 138) { 
    goal(1);  // Player 1 scores a goal
  }
}