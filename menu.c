#include <stdint.h>
#include <pic32mx.h>
#include "mipslab.h"
#include <stdio.h>
#include <stdlib.h>

// Just begin with the first onption in menu
int current_option = 1;

// Function to handle menu navigation and selection based on button input.
void menu(int btns) {
  delay(200); // Delay to debounce button input.

  // Check if the current option is the first one.
  if(current_option == 1) {
    // Display options for Menu.
    display_string(0, "--> Two Player"); // Highlight "Two Player" option.
    display_string(1, "  One Player");

    // Check if button 1 is pressed.
    if (getbtns() & 0x1) {
      // If pressed, reset the game, set game mode to Two Player, activate game, and clear strings.
      reset_game();
      game_mode = 1;    // Check the mipslabwork.c file, this chooses which gamemode we play, in this case two_player()
      game_active = 1;
      string_clear(); // Clear displayed strings.
    }
  }
  // Check if the current option is the second one.
  else if(current_option == 2) {
    // Display options for Menu.
    display_string(0, "  Two Player");
    display_string(1, "--> One Player"); // Highlight "One Player" option.

    // Check if button 1 is pressed.
    if (getbtns() & 0x1) {
      // If pressed, reset the game, set game mode to One Player, activate game, and clear strings.
      reset_game();
      game_mode = 2;    // Check the mipslabwork.c file, this chooses which gamemode we play, in this case one_player()
      game_active = 1;
      string_clear(); // Clear displayed strings.
    }
  }

  // Check if button 2 is pressed and the current option is 1.
  if ((getbtns() & 0x2) && (current_option == 1)) {
    current_option++; // Move to option 2.
  }
  // Check if button 4 is pressed and the current option is 2.
  if ((getbtns() & 0x4) && (current_option == 2)) {
    current_option--; // Move back to option 1.
  }
  // Update the display to reflect changes.
  display_update();
}
