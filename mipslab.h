/* mipslab.h
   Header file for all labs.
   This file written 2015 by F Lundevall
   Some parts are original code written by Axel Isaksson

   Latest update 2015-08-28 by F Lundevall

   For copyright and licensing, see file COPYING */

/* Declare display-related functions from mipslabfunc.c */
void display_image(int x, const uint8_t *data);
void display_init(void);
void display_string(int line, char *s);
void display_update(void);
uint8_t spi_send_recv(uint8_t data);

/* Declare lab-related functions from mipslabfunc.c */
char * itoaconv( int num );
void labwork(void);
int nextprime( int inval );
void quicksleep(int cyc);
void tick( unsigned int * timep );

/* Declare display_debug - a function to help debugging.

   After calling display_debug,
   the two middle lines of the display show
   an address and its current contents.

   There's one parameter: the address to read and display.

   Note: When you use this function, you should comment out any
   repeated calls to display_image; display_image overwrites
   about half of the digits shown by display_debug.
*/
void display_debug( volatile int * const addr );

/* Declare bitmap array containing font */
extern const uint8_t const font[128*8];
/* Declare bitmap array containing icon */
extern const uint8_t const icon[128];
/* Declare text buffer for display output */
extern char textbuffer[4][16];

/* Declare functions written by students.
   Note: Since we declare these functions here,
   students must define their functions with the exact types
   specified in the laboratory instructions. */
/* Written as part of asm lab: delay, time2string */

/* The "extern" keyword indicates that these variables are declared elsewhere in the code,
   in another source file, and their memory space is allocated there.
   It allows multiple source files to share the same variable definition without duplicating memory allocation.*/

void delay(int);
void time2string( char *, int );

/* Written as part of i/o lab: getbtns, getsw, enable_interrupt */
int getbtns(void);
int getsw(void);
void enable_interrupt(void);

// Declaration of the display buffers
// These arrays serve as storage areas for the pixel data that will be shown on a display.
extern uint8_t display[32][128];   // Display buffer for a display with 32 rows and 128 columns of pixels
extern uint8_t oled_display[512];  // Display buffer for an OLED display with a total of 512 pixels

// Gamemode functions
void one_player(int);   // Function to handle the one-player game mode
void two_player(int);   // Function to handle the two-player game mode

// Move functions
void player_movement_one(int);   // Function to handle player movement in one-player mode
void player_movement_two(int);   // Function to handle player movement in two-player mode
void ball_movement(void);         // Function to handle ball movement
void ai_move(void);               // Function to handle AI movement

// Display functions
void translateToDisplay(void);    // Function to translate pixel data to display
void setPixelArray(int, int, int, int);  // Function to set pixel data in the display buffer
void clearDisplay(void);          // Function to clear the display buffer

// Menu functions
void menu(int);             // Function for managing menu options and navigation

// Game functions
void goal(int);             // Function to handle scoring a goal
void quit(void);            // Function to quit the game
void reset_game(void);      // Function to reset the game state
void string_clear(void);    // Function to clear strings from the display
void player1_win(void);     // Function to handle player 1 winning the game
void player2_win(void);     // Function to handle player 2 winning the game

// Menu specific variables
extern int current_option;  // Variable to store the current selected option in the menu

// Game specific variables
extern int game_active;     // Variable to track the game's active state
extern int game_mode;       // Variable to store the current game mode
extern int score_player1;   // Variable to store the score of player 1
extern int score_player2;   // Variable to store the score of player 2

// Paddle specific variables
extern int paddle_height;    // Height of the paddles
extern int paddle_width;     // Width of the paddles
extern int paddle_speed;     // Speed of the paddles' movement

extern int paddle1_xPos;     // X position of player 1's paddle
extern int paddle1_yPos;     // Y position of player 1's paddle

extern int paddle2_xPos;     // X position of player 2's paddle
extern int paddle2_yPos;     // Y position of player 2's paddle

extern int paddle2_up;       // Flag indicating player 2's paddle is moving up
extern int paddle2_down;     // Flag indicating player 2's paddle is moving down
extern int paddle1_up;       // Flag indicating player 1's paddle is moving up
extern int paddle1_down;     // Flag indicating player 1's paddle is moving down

// Ball specific variables
extern int ball_size;       // Size of the ball
extern int ball_speedx;     // Speed of the ball in the x-direction
extern int ball_speedy;     // Speed of the ball in the y-direction

extern int ball_xPos;       // X position of the ball
extern int ball_yPos;       // Y position of the ball

// Timer
extern int mytime;          // Timer variable
extern char textstring[];   // Text string for timer display