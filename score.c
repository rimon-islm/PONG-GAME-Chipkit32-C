#include <stdint.h>
#include <pic32mx.h>
#include "mipslab.h"
#include <stdio.h>
#include <stdlib.h>

void goal(int player) {
  // For score mode
  if ((player == 1) && (game_mode != 3)) {
    // Increase score for Player 1 and display score message.
    score_player1 += 1;
    display_string(2, "Player 1 scored!");
    display_update(); 
    delay(2000); // Delay to allow players to see the score message.
  }
  if ((player == 2) && (game_mode != 3)) {
    // Increase score for Player 2 and display score message.
    score_player2 += 1;
    display_string(2, "Player 2 scored!"); 
    display_update();
    delay(2000); // Delay to allow players to see the score message.
  }

  // Update score display on chipkit.
  if ((game_mode == 2) || (game_mode == 1)) {
    // Update score display on chipkit for Player 1.
    if (score_player1 == 1) {
      PORTE |= 0x80;  // Led 5 glowinf
    }
    else if (score_player1 == 2) {
      PORTE |= 0xC0;  // Led 6 glowing
    }
    else if (score_player1 == 3) {
      PORTE |= 0xE0;  // Led 7 glowing
    }
    else if (score_player1 == 4) {
      PORTE |= 0xF0;  // Led 7 glowing
      player1_win(); // Player 1 wins.
    }

    // Update score display on chipkit for Player 2 or AI.
    if (score_player2 == 4) {
      PORTE |= 0x8;  // Led 4 glowing
      player2_win(); // Player 2 wins.
    }
    else if (score_player2 == 3) {
      PORTE |= 0x4;  // Led 3 glowing
    }
    else if (score_player2 == 2) {
      PORTE |= 0x2;  // Led 2 glowing
    }
    else if (score_player2 == 1) {
      PORTE |= 0x1;   // Led 1 glowing
    }
  }

  // Reset the game to its initial state after scoring.
  reset_game();
}