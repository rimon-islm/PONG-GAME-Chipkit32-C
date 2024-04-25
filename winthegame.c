#include <stdint.h>
#include <pic32mx.h>
#include "mipslab.h"
#include <stdio.h>
#include <stdlib.h>

void player1_win(){
    display_string(2, "Player 1 wins!");  // Display "Player 1 wins!" on line 2 of the display
    display_string(3, textstring);         // Display the timer string on line 3 of the display
    display_update();                      // Update the display to show the new strings
    delay(3000);                           // Delay for 3000 milliseconds (3 seconds)
    string_clear();                        // Clear all strings from the display
    display_update();                      // Update the display to remove the strings
    quit();                                // Quit the game and perform cleanup/reset operations
}

void player2_win(){
    if (game_mode == 2) {
        display_string(2, "AI wins");      // Display "AI wins" on line 2 if game mode is 2 (Singel player)
        display_string(3, textstring);     // Display the timer string on line 3
    } else {
        display_string(2, "Player 2 wins!");  // Display "Player 2 wins!" on line 2 if game mode is not 2 (Two players)
        display_string(3, textstring);        // Display the timer string on line 3
    }
    display_update();                         // Update the display to show the new strings
    delay(3000);                              // Delay for 3000 milliseconds (3 seconds)
    string_clear();                           // Clear all strings from the display
    display_update();                         // Update the display to remove the strings
    quit();                                   // Quit the game and perform cleanup/reset operations
}
