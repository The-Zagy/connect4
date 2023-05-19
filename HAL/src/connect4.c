
/**********************************************************************************************************************
 *  FILE DESCRIPTION
 *  -----------------------------------------------------------------------------------------------------------------*/
/**        \file  FileName.c
 *        \brief
 *
 *      \details
 *
 *
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
#include "../tm4c123gh6pm.h"
#include "../LIBRARIES/common/Std_Types.h"
#include "../LIBRARIES/CpuDriver/inc/cpu_driver.h"
#include "../MCAL/INTERRUPT/inc/IntCtrl.h"
#include "../inc/connect4.h"
#include "../../Nokia5110.h"
#include "../../Random.h"
#include "../../TExaS.h"
#include "../MCAL/PORT/Inc/Port_Cfg.h"
#include <math.h>
#include <time.h>
#include <string.h>
#include <stdlib.h>
#define ROWS_NUM 6
#define COLS_NUM 7
#define AC_WHITE "\x1b[37m"
#define AC_RED "\x1b[31m"
#define AC_GREEN "\x1b[32m"
#define AC_YELLOW "\x1b[33m"

// Define the push button inputs
#define MOVE_LEFT_BUTTON_PIN 4
#define MOVE_RIGHT_BUTTON_PIN 0

// Define a global variable to hold the current column name
enum Cols_name current_col = C;

// Define the game board array
position_state_t board[ROWS_NUM][COLS_NUM];
int move_right_flag = 0;
int move_left_flag = 0;
int action_flag = 0;
int timer_flag = 0;

/**
 * insert new position state in certian column, and row number is managed by gravity [first empty row in this column], the row_num state from which row start searching for correct position in recursive
 * return TRUE if inserted successfully
 */

/**********************************************************************************************************************
 *  LOCAL MACROS CONSTANT\FUNCTION
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  LOCAL DATA
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL DATA
 *********************************************************************************************************************/
unsigned long SW1, SW2; // input from PF4,PF0
unsigned int seed = 25;

int r = 0, rr = 0, uturn = 0, i;
int turn = 0, done = 0;

// image of the player's ship
// includes two blacked out columns on the left and right sides of the image to prevent smearing when moved 2 pixels to the left or right
// width=18 x height=8

const unsigned char logo[] = {
    0x42,
    0x4D,
    0x7A,
    0x2E,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x36,
    0x00,
    0x00,
    0x00,
    0x28,
    0x00,
    0x00,
    0x00,
    0x53,
    0x00,
    0x00,
    0x00,
    0x2F,
    0x00,
    0x00,
    0x00,
    0x01,
    0x00,
    0x18,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x44,
    0x2E,
    0x00,
    0x00,
    0xC3,
    0x0E,
    0x00,
    0x00,
    0xC3,
    0x0E,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x0C,
    0x0C,
    0x00,
    0x8D,
    0x8D,
    0x00,
    0x85,
    0x85,
    0x00,
    0xA1,
    0xA1,
    0x00,
    0x87,
    0x87,
    0x00,
    0x23,
    0x23,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x1F,
    0x1F,
    0x00,
    0xCD,
    0xCD,
    0x00,
    0x33,
    0x33,
    0x00,
    0x78,
    0x78,
    0x00,
    0x91,
    0x91,
    0x00,
    0x0C,
    0x0C,
    0x00,
    0x9B,
    0x9B,
    0x00,
    0x2F,
    0x2F,
    0x00,
    0x62,
    0x62,
    0x00,
    0xE4,
    0xE4,
    0x00,
    0x17,
    0x17,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0xA7,
    0xA7,
    0x00,
    0x93,
    0x93,
    0x00,
    0xFF,

};

const unsigned char PlayerShip0[] = {
    0x42, 0x4D, 0xD6, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x76, 0x00, 0x00, 0x00, 0x28, 0x00, 0x00, 0x00, 0x12, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x01, 0x00, 0x04, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x60, 0x00, 0x00, 0x00, 0xC4, 0x0E, 0x00, 0x00, 0xC4, 0x0E, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x80,
    0x00, 0x00, 0x00, 0x80, 0x80, 0x00, 0x80, 0x00, 0x00, 0x00, 0x80, 0x00, 0x80, 0x00, 0x80, 0x80, 0x00, 0x00, 0x80, 0x80, 0x80, 0x00, 0xC0, 0xC0, 0xC0, 0x00, 0x00, 0x00, 0xFF, 0x00, 0x00, 0xFF,
    0x00, 0x00, 0x00, 0xFF, 0xFF, 0x00, 0xFF, 0x00, 0x00, 0x00, 0xFF, 0x00, 0xFF, 0x00, 0xFF, 0xFF, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0x00, 0x00,
    0x00, 0x00, 0x00, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0x00, 0x00, 0x00, 0x00, 0x00, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0A, 0xAA, 0xAA, 0xAA, 0xAA,
    0xAA, 0xA0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0A, 0xAA, 0xA0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0A, 0xAA, 0xA0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0xAA, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF};
const unsigned char empty_cell[] = {
    0x42,
    0x4D,
    0xA6,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x76,
    0x00,
    0x00,
    0x00,
    0x28,
    0x00,
    0x00,
    0x00,
    0x0C,
    0x00,
    0x00,
    0x00,
    0x06,
    0x00,
    0x00,
    0x00,
    0x01,
    0x00,
    0x04,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x30,
    0x00,
    0x00,
    0x00,
    0xC4,
    0x0E,
    0x00,
    0x00,
    0xC4,
    0x0E,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x80,
    0x00,
    0x00,
    0x80,
    0x00,
    0x00,
    0x00,
    0x80,
    0x80,
    0x00,
    0x80,
    0x00,
    0x00,
    0x00,
    0x80,
    0x00,
    0x80,
    0x00,
    0x80,
    0x80,
    0x00,
    0x00,
    0x80,
    0x80,
    0x80,
    0x00,
    0xC0,
    0xC0,
    0xC0,
    0x00,
    0x00,
    0x00,
    0xFF,
    0x00,
    0x00,
    0xFF,
    0x00,
    0x00,
    0x00,
    0xFF,
    0xFF,
    0x00,
    0xFF,
    0x00,
    0x00,
    0x00,
    0xFF,
    0x00,
    0xFF,
    0x00,
    0xFF,
    0xFF,
    0x00,
    0x00,
    0xFF,
    0xFF,
    0xFF,
    0x00,
    0xAA,
    0xAA,
    0xAA,
    0xAA,
    0xAA,
    0xAA,
    0x00,
    0x00,
    0xA0,
    0x00,
    0x00,
    0x00,
    0x00,
    0x0A,
    0x00,
    0x00,
    0xA0,
    0x00,
    0x00,
    0x00,
    0x00,
    0x0A,
    0x00,
    0x00,
    0xA0,
    0x00,
    0x00,
    0x00,
    0x00,
    0x0A,
    0x00,
    0x00,
    0xA0,
    0x00,
    0x00,
    0x00,
    0x00,
    0x0A,
    0x00,
    0x00,
    0xAA,
    0xAA,
    0xAA,
    0xAA,
    0xAA,
    0xAA,
    0x00,
    0x00,
    0xFF,

};

const unsigned char full_cell_player_1[] = {
    0x42,
    0x4D,
    0xA6,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x76,
    0x00,
    0x00,
    0x00,
    0x28,
    0x00,
    0x00,
    0x00,
    0x0C,
    0x00,
    0x00,
    0x00,
    0x06,
    0x00,
    0x00,
    0x00,
    0x01,
    0x00,
    0x04,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x30,
    0x00,
    0x00,
    0x00,
    0xC4,
    0x0E,
    0x00,
    0x00,
    0xC4,
    0x0E,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x80,
    0x00,
    0x00,
    0x80,
    0x00,
    0x00,
    0x00,
    0x80,
    0x80,
    0x00,
    0x80,
    0x00,
    0x00,
    0x00,
    0x80,
    0x00,
    0x80,
    0x00,
    0x80,
    0x80,
    0x00,
    0x00,
    0x80,
    0x80,
    0x80,
    0x00,
    0xC0,
    0xC0,
    0xC0,
    0x00,
    0x00,
    0x00,
    0xFF,
    0x00,
    0x00,
    0xFF,
    0x00,
    0x00,
    0x00,
    0xFF,
    0xFF,
    0x00,
    0xFF,
    0x00,
    0x00,
    0x00,
    0xFF,
    0x00,
    0xFF,
    0x00,
    0xFF,
    0xFF,
    0x00,
    0x00,
    0xFF,
    0xFF,
    0xFF,
    0x00,
    0xAA,
    0xAA,
    0xAA,
    0xAA,
    0xAA,
    0xAA,
    0x00,
    0x00,
    0xAA,
    0x0A,
    0x0A,
    0x0A,
    0x0A,
    0x0A,
    0x00,
    0x00,
    0xA0,
    0xA0,
    0xA0,
    0xA0,
    0xA0,
    0xAA,
    0x00,
    0x00,
    0xAA,
    0x0A,
    0x0A,
    0x0A,
    0x0A,
    0x0A,
    0x00,
    0x00,
    0xA0,
    0xA0,
    0xA0,
    0xA0,
    0xA0,
    0xAA,
    0x00,
    0x00,
    0xAA,
    0xAA,
    0xAA,
    0xAA,
    0xAA,
    0xAA,
    0x00,
    0x00,
    0xFF,

};

const unsigned char full_cell_player_2[] = {
    0x42,
    0x4D,
    0xA6,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x76,
    0x00,
    0x00,
    0x00,
    0x28,
    0x00,
    0x00,
    0x00,
    0x0C,
    0x00,
    0x00,
    0x00,
    0x06,
    0x00,
    0x00,
    0x00,
    0x01,
    0x00,
    0x04,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x30,
    0x00,
    0x00,
    0x00,
    0xC4,
    0x0E,
    0x00,
    0x00,
    0xC4,
    0x0E,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x80,
    0x00,
    0x00,
    0x80,
    0x00,
    0x00,
    0x00,
    0x80,
    0x80,
    0x00,
    0x80,
    0x00,
    0x00,
    0x00,
    0x80,
    0x00,
    0x80,
    0x00,
    0x80,
    0x80,
    0x00,
    0x00,
    0x80,
    0x80,
    0x80,
    0x00,
    0xC0,
    0xC0,
    0xC0,
    0x00,
    0x00,
    0x00,
    0xFF,
    0x00,
    0x00,
    0xFF,
    0x00,
    0x00,
    0x00,
    0xFF,
    0xFF,
    0x00,
    0xFF,
    0x00,
    0x00,
    0x00,
    0xFF,
    0x00,
    0xFF,
    0x00,
    0xFF,
    0xFF,
    0x00,
    0x00,
    0xFF,
    0xFF,
    0xFF,
    0x00,
    0xAA,
    0xAA,
    0xAA,
    0xAA,
    0xAA,
    0xAA,
    0x00,
    0x00,
    0xAA,
    0x00,
    0xA0,
    0x0A,
    0x00,
    0x0A,
    0x00,
    0x00,
    0xA0,
    0xA0,
    0x0A,
    0x00,
    0xA0,
    0x0A,
    0x00,
    0x00,
    0xA0,
    0x0A,
    0x00,
    0xA0,
    0x0A,
    0x0A,
    0x00,
    0x00,
    0xA0,
    0x00,
    0xA0,
    0x0A,
    0x00,
    0xAA,
    0x00,
    0x00,
    0xAA,
    0xAA,
    0xAA,
    0xAA,
    0xAA,
    0xAA,
    0x00,
    0x00,
    0xFF,

};

const unsigned char arrow[] = {
    0x42,
    0x4D,
    0x9E,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x76,
    0x00,
    0x00,
    0x00,
    0x28,
    0x00,
    0x00,
    0x00,
    0x08,
    0x00,
    0x00,
    0x00,
    0x0A,
    0x00,
    0x00,
    0x00,
    0x01,
    0x00,
    0x04,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x28,
    0x00,
    0x00,
    0x00,
    0xC4,
    0x0E,
    0x00,
    0x00,
    0xC4,
    0x0E,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x80,
    0x00,
    0x00,
    0x80,
    0x00,
    0x00,
    0x00,
    0x80,
    0x80,
    0x00,
    0x80,
    0x00,
    0x00,
    0x00,
    0x80,
    0x00,
    0x80,
    0x00,
    0x80,
    0x80,
    0x00,
    0x00,
    0x80,
    0x80,
    0x80,
    0x00,
    0xC0,
    0xC0,
    0xC0,
    0x00,
    0x00,
    0x00,
    0xFF,
    0x00,
    0x00,
    0xFF,
    0x00,
    0x00,
    0x00,
    0xFF,
    0xFF,
    0x00,
    0xFF,
    0x00,
    0x00,
    0x00,
    0xFF,
    0x00,
    0xFF,
    0x00,
    0xFF,
    0xFF,
    0x00,
    0x00,
    0xFF,
    0xFF,
    0xFF,
    0x00,
    0x00,
    0x0A,
    0xA0,
    0x00,
    0x00,
    0xAA,
    0xAA,
    0x00,
    0x0A,
    0xAA,
    0xAA,
    0xA0,
    0xAA,
    0xAA,
    0xAA,
    0xAA,
    0x00,
    0x0A,
    0xA0,
    0x00,
    0x00,
    0x0A,
    0xA0,
    0x00,
    0x00,
    0x0A,
    0xA0,
    0x00,
    0x00,
    0x0A,
    0xA0,
    0x00,
    0x00,
    0x0A,
    0xA0,
    0x00,
    0x00,
    0x0A,
    0xA0,
    0x00,
    0xFF,

};

// Set up the player at the bottom center of the screen

Player player = {SCREEN_WIDTH / 2 - PLAYER_WIDTH / 2, SCREEN_HEIGHT - PLAYER_HEIGHT - 2};
/**********************************************************************************************************************
 *  LOCAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  LOCAL FUNCTIONS
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL FUNCTIONS
 *********************************************************************************************************************/

// Initialize the GPIO module PORTF and interrupt module
void init_GPIO_interrupt(void)
{
  // Enable PORTF
  SYSCTL_RCGCGPIO_R |= SYSCTL_RCGCGPIO_R5;

  // Enable the Move Left and Move Right buttons
  GPIO_PORTF_DIR_R &= ~(1 << MOVE_LEFT_BUTTON_PIN);
  GPIO_PORTF_DIR_R &= ~(1 << MOVE_RIGHT_BUTTON_PIN);
  GPIO_PORTF_DEN_R |= (1 << MOVE_LEFT_BUTTON_PIN);
  GPIO_PORTF_DEN_R |= (1 << MOVE_RIGHT_BUTTON_PIN);

  // Enable internal pull-up resistors for the buttons
  GPIO_PORTF_PUR_R |= (1 << MOVE_LEFT_BUTTON_PIN);
  GPIO_PORTF_PUR_R |= (1 << MOVE_RIGHT_BUTTON_PIN);

  // Configure the buttons to trigger interrupts on the falling edge
  GPIO_PORTF_IS_R &= ~(1 << MOVE_LEFT_BUTTON_PIN);
  GPIO_PORTF_IS_R &= ~(1 << MOVE_RIGHT_BUTTON_PIN);
  GPIO_PORTF_IBE_R &= ~(1 << MOVE_LEFT_BUTTON_PIN);
  GPIO_PORTF_IBE_R &= ~(1 << MOVE_RIGHT_BUTTON_PIN);
  GPIO_PORTF_IEV_R &= ~(1 << MOVE_LEFT_BUTTON_PIN);
  GPIO_PORTF_IEV_R &= ~(1 << MOVE_RIGHT_BUTTON_PIN);
  GPIO_PORTF_ICR_R |= (1 << MOVE_LEFT_BUTTON_PIN);
  GPIO_PORTF_ICR_R |= (1 << MOVE_RIGHT_BUTTON_PIN);
  GPIO_PORTF_IM_R |= (1 << MOVE_LEFT_BUTTON_PIN);
  GPIO_PORTF_IM_R |= (1 << MOVE_RIGHT_BUTTON_PIN);

  // Enable the interrupt for PORTF
  NVIC_EN0_R |= (1 << (INT_GPIOF - 16));
}
// Draw the arrow indicator for the current column
void draw_arrow_indicator(enum Cols_name current_col)
{
  int x = current_col * CELL_WIDTH + 3;
  int y = 10;
  Nokia5110_ClearBuffer();
  Nokia5110_DisplayBuffer();
  Nokia5110_PrintBMP(x, y, arrow, 0);
  Nokia5110_DisplayBuffer();
}

void draw_board_with_indicator(position_state_t board[ROWS_NUM][COLS_NUM], enum Cols_name current_col, enum Game_state game_state)
{

  // Draw the board as usual
  draw_board(board, current_col, game_state);

  // Draw the arrow indicator
  draw_arrow_indicator(current_col);
}

//// Interrupt handler for PORTF
// void PortF_Handler(void)
//{
//   // Check if the move left button was pressed
//   if (GPIO_PORTF_RIS_R & (1 << MOVE_LEFT_BUTTON_PIN))
//   {
//     // Clear the interrupt flag
//     GPIO_PORTF_ICR_R |= (1 << MOVE_LEFT_BUTTON_PIN);

//    // Update the current column name
//    if (current_col > A)
//    {
//      current_col--;
//    }
//    draw_board_with_indicator(board, current_col, 1);
//  }

//  // Check if the move right button was pressed
//  if (GPIO_PORTF_RIS_R & (1 << MOVE_RIGHT_BUTTON_PIN))
//  {
//    // Clear the interrupt flag
//    GPIO_PORTF_ICR_R |= (1 << MOVE_RIGHT_BUTTON_PIN);

//    // Update the current column name
//    if (current_col < G)
//    {
//      current_col++;
//    }
//    draw_board_with_indicator(board, current_col, 1);
//  }
//}
void Timer2_Init(unsigned long period)
{
  unsigned long volatile delay;
  SYSCTL_RCGCTIMER_R |= 0x04; // 0) activate timer2
  delay = SYSCTL_RCGCTIMER_R;
  timer_flag = 0;
  TIMER2_CTL_R = 0x00000000;                             // 1) disable timer2A during setup
  TIMER2_CFG_R = 0x00000000;                             // 2) configure for 32-bit mode
  TIMER2_TAMR_R = 0x00000002;                            // 3) configure for periodic mode, default down-count settings
  TIMER2_TAILR_R = period - 1;                           // 4) reload value
  TIMER2_TAPR_R = 0;                                     // 5) bus clock resolution
  TIMER2_ICR_R = 0x00000001;                             // 6) clear timer2A timeout flag
  TIMER2_IMR_R = 0x00000001;                             // 7) arm timeout interrupt
  NVIC_PRI5_R = (NVIC_PRI5_R & 0x00FFFFFF) | 0x80000000; // 8) priority 4
                                                         // interrupts enabled in the main program after all devices initialized
                                                         // vector number 39, interrupt number
  NVIC_EN0_R = 1 << 23;                                  // 9) enable IRQ 23 in NVIC
  TIMER2_CTL_R = 0x00000001;                             // 10) enable timer2A
}

void Timer2A_Handler(void)
{
  TIMER2_ICR_R = 0x00000001; // acknowledge timer2A timeout
  timer_flag += 1;
}

void stop_timer(void)
{
  TIMER2_CTL_R = 0x00000000; // 1) disable timer2A during setup
}

void game_Init(void)
{
  Timer2_Init(80000000);
  // int mode;
  Port_Init(&Move_Right_Button);
  Port_Init(&Move_Left_Button);
  Port_Init(&Action_Button);

  Port_EXTI_Init(&EXTI_Right_Button);
  Port_EXTI_Init(&EXTI_Left_Button);
  Port_EXTI_Init(&EXTI_Action_Button);

  IntCrtl_Init(&Int_Right_Button);
  IntCrtl_Init(&Int_Left_Button);
  IntCrtl_Init(&Int_Action_Button);
  Nokia5110_Clear();
  cpuDriver_EnableGlobalInterrupt();
}

void starting_screen(void)
{
  // Nokia5110_SetCursor(0, 0);
  Nokia5110_ClearBuffer();
  //  Nokia5110_DrawFullImage(logo);
  Nokia5110_SetCursor(0, 5);
  Nokia5110_OutString("Welcome :D!");
  Nokia5110_DisplayBuffer();
  while (timer_flag != 1)
    ;
  stop_timer();
}

void select_mode(game_mode_t mode)
{ // here is selecting if the mode is P1 VS AI or P1 vs P2

  Nokia5110_SetCursor(0, 0);
  Nokia5110_OutString("select");
  Nokia5110_SetCursor(7, 0);
  Nokia5110_OutString("mode");
  Nokia5110_SetCursor(3, 2);
  Nokia5110_OutString("P1 VS AI");
  Nokia5110_SetCursor(3, 4);
  Nokia5110_OutString("P1 VS P2");
  Nokia5110_SetCursor(0, (mode * 2) + 2);
  Nokia5110_OutString(">>");
}

bool_t insert_token(position_state_t board[ROWS_NUM][COLS_NUM], position_state_t state, enum Cols_name col_num, unsigned row_num)
{
  // don't go out of scope
  if (col_num >= COLS_NUM || col_num < 0 || row_num >= ROWS_NUM || row_num < 0)
  {
    return FALSE_t;
  }
  // can't insert in full column
  // go down the rows until you find empty row and the one before it is full or you reached the floor

  // reached non empty field means no free space in this column
  if (board[row_num][col_num] != EMPTY)
  {
    return FALSE_t;
  }

  // empty then non-empty or ground is the one satisfy the gravity
  if (board[row_num][col_num] == EMPTY && (board[row_num + 1][col_num] != EMPTY || row_num == ROWS_NUM - 1))
  {
    board[row_num][col_num] = state;
    return TRUE_t;
  }
  else
  {
    return insert_token(board, state, col_num, row_num + 1);
  }
  return FALSE_t;
}

bool_t check_for_winner(position_state_t board[ROWS_NUM][COLS_NUM], position_state_t piece)
{
  int c;
  int r;
  // Check horizontal locations for win
  for (c = 0; c < COLS_NUM - 3; c++)
  {
    for (r = 0; r < ROWS_NUM; r++)
    {
      if (board[r][c] == piece && board[r][c + 1] == piece && board[r][c + 2] == piece && board[r][c + 3] == piece)
      {
        return TRUE_t;
      }
    }
  }

  // Check vertical locations for win
  for (c = 0; c < COLS_NUM; c++)
  {
    for (r = 0; r < ROWS_NUM - 3; r++)
    {
      if (board[r][c] == piece && board[r + 1][c] == piece && board[r + 2][c] == piece && board[r + 3][c] == piece)
      {
        return TRUE_t;
      }
    }
  }

  // Check positively sloped diagonals
  for (c = 0; c < COLS_NUM - 3; c++)
  {
    for (r = 0; r < ROWS_NUM - 3; r++)
    {
      if (board[r][c] == piece && board[r + 1][c + 1] == piece && board[r + 2][c + 2] == piece && board[r + 3][c + 3] == piece)
      {
        return TRUE_t;
      }
    }
  }

  // Check negatively sloped diagonals
  for (c = 0; c < COLS_NUM - 3; c++)
  {
    for (r = 3; r < ROWS_NUM; r++)
    {
      if (board[r][c] == piece && board[r - 1][c + 1] == piece && board[r - 2][c + 2] == piece && board[r - 3][c + 3] == piece)
      {
        return TRUE_t;
      }
    }
  }

  return FALSE_t;
}
void draw_board(position_state_t board[ROWS_NUM][COLS_NUM], enum Cols_name arrow_position, enum Game_state game_state)
{
  int offsetY = 17;
  int i, j;
  Nokia5110_PrintBMP(arrow_position * CELL_WIDTH + 3, 10, arrow, 0);
  Nokia5110_SetCursor(arrow_position * CELL_WIDTH + 6, 10);

  for (i = 0; i < ROWS_NUM; i++)
  {
    for (j = 0; j < COLS_NUM; j++)
    {
      int x = j * CELL_WIDTH;
      int y = i * CELL_HEIGHT + offsetY;
      if (board[i][j] == EMPTY)
      {
        Nokia5110_PrintBMP(x, y, empty_cell, 0);
      }
      else if (board[i][j] == PLAYER1_SLOT)
      {
        Nokia5110_PrintBMP(x, y, full_cell_player_1, 0);
      }
      else if (board[i][j] == PLAYER2_SLOT)
      {
        Nokia5110_PrintBMP(x, y, full_cell_player_2, 0);
      }
    }
  }
  Nokia5110_DisplayBuffer();
  if (game_state == GAME_PLAYER1_TURN)
  {
    Nokia5110_OutString("P1");
  }
  else
  {
    Nokia5110_OutString("P2");
  }
}

void Delay100ms(unsigned long count)
{
  unsigned long volatile time;
  while (count)
  {
    time = 72724; // 0.1sec at 80 MHz
    while (time)
    {
      time--;
    }
    count--;
  }
}

void UARTB_init()
{

  SYSCTL_RCGCUART_R |= (1 << 1);
  GPIO_PORTB_AFSEL_R |= 0x03;
  GPIO_PORTB_DEN_R |= 0x03;
  GPIO_PORTB_PCTL_R |= 0x11;
  UART1_CTL_R &= ~(1 << 0);
  UART1_IBRD_R = 8;
  UART1_FBRD_R = 44;
  // IBRD = int(16,000,000 / (16 * 115200)) = int(8.6805)
  // FBRD = int(0.6805 * 64 + 0.5) = 44
  UART1_LCRH_R = (3 << 5);
  UART1_CC_R = 0;
  UART1_CTL_R |= (1 << 0) | (1 << 8) | (1 << 9);
}

void UARTB_OutChar(char data)
{
  // as part of Lab 11, modify this program to use UART0 instead of UART1
  while ((UART1_FR_R & (1 << 5)) != 0)
    ;
  UART1_DR_R = data;
}

void PortF_Init(void)
{
  volatile unsigned long delay;
  SYSCTL_RCGC2_R |= 0x00000020 | 0x00000002; // 1) B & F clock
  delay = SYSCTL_RCGC2_R;                    // delay
  GPIO_PORTF_LOCK_R = 0x4C4F434B;            // 2) unlock PortF PF0
  GPIO_PORTF_CR_R = 0x1F;                    // allow changes to PF4-0
  GPIO_PORTF_AMSEL_R = 0x00;                 // 3) disable analog function
  GPIO_PORTF_PCTL_R = 0x00000000;            // 4) GPIO clear bit PCTL
  GPIO_PORTF_DIR_R = 0x0E;                   // 5) PF4,PF0 input, PF3,PF2,PF1 output
  GPIO_PORTF_AFSEL_R = 0x00;                 // 6) no alternate function
  GPIO_PORTF_PUR_R = 0x11;                   // enable pullup resistors on PF4,PF0
  GPIO_PORTF_DEN_R = 0x1F;                   // 7) enable digital pins PF4-PF0
}

void endScreen()
{
  Delay100ms(50);
  if (turn == ROWS_NUM * COLS_NUM && !done)
  {
    Nokia5110_OutString("It's a tie!");
  }
  else
  {
    turn--;
    Nokia5110_Clear();
    Nokia5110_SetCursor(1, 1);
    Nokia5110_OutString("Player");
    Nokia5110_SetCursor(8, 1);
    Nokia5110_OutString(turn % 2 == 0 ? "X" : "O");
    Nokia5110_SetCursor(3, 2);
    Nokia5110_OutString("wins!");
    Delay100ms(15);
    Nokia5110_SetCursor(1, 4);
    Nokia5110_OutString("GAME OVER");
    Delay100ms(5);
    Nokia5110_SetCursor(1, 4);
    Nokia5110_OutString("        ");
    Delay100ms(5);
    Nokia5110_SetCursor(1, 4);
    Nokia5110_OutString("GAME OVER");
  }
}
/******************************************************************************
 * \Syntax          : Std_ReturnType FunctionName(AnyType parameterName)
 * \Description     : Describe this service
 *
 * \Sync\Async      : Synchronous
 * \Reentrancy      : Non Reentrant
 * \Parameters (in) : parameterName   Parameter Describtion
 * \Parameters (out): None
 * \Return value:   : Std_ReturnType  E_OK
 *                                    E_NOT_OK
 *******************************************************************************/

/**********************************************************************************************************************
 *  END OF FILE: spaceInvaders.c
 *********************************************************************************************************************/

// SpaceInvaders.c
// Runs on LM4F120/TM4C123
// Jonathan Valvano and Daniel Valvano
// This is a starter project for the edX Lab 15
// In order for other students to play your game
// 1) You must leave the hardware configuration as defined
// 2) You must not add/remove any files from the project
// 3) You must add your code only this this C file
// I.e., if you wish to use code from sprite.c or sound.c, move that code in this file
// 4) It must compile with the 32k limit of the free Keil

// April 10, 2014
// http://www.spaceinvaders.de/
// sounds at http://www.classicgaming.cc/classics/spaceinvaders/sounds.php
// http://www.classicgaming.cc/classics/spaceinvaders/playguide.php
/* This example accompanies the books
   "Embedded Systems: Real Time Interfacing to Arm Cortex M Microcontrollers",
   ISBN: 978-1463590154, Jonathan Valvano, copyright (c) 2013

   "Embedded Systems: Introduction to Arm Cortex M Microcontrollers",
   ISBN: 978-1469998749, Jonathan Valvano, copyright (c) 2013

 Copyright 2014 by Jonathan W. Valvano, valvano@mail.utexas.edu
    You may use, edit, run or distribute this file
    as long as the above copyright notice remains
 THIS SOFTWARE IS PROVIDED "AS IS".  NO WARRANTIES, WHETHER EXPRESS, IMPLIED
 OR STATUTORY, INCLUDING, BUT NOT LIMITED TO, IMPLIED WARRANTIES OF
 MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE APPLY TO THIS SOFTWARE.
 VALVANO SHALL NOT, IN ANY CIRCUMSTANCES, BE LIABLE FOR SPECIAL, INCIDENTAL,
 OR CONSEQUENTIAL DAMAGES, FOR ANY REASON WHATSOEVER.
 For more information about my classes, my research, and my books, see
 http://users.ece.utexas.edu/~valvano/
 */
// ******* Required Hardware I/O connections*******************
// Slide pot pin 1 connected to ground
// Slide pot pin 2 connected to PE2/AIN1
// Slide pot pin 3 connected to +3.3V
// fire button connected to PE0
// special weapon fire button connected to PE1
// 8*R resistor DAC bit 0 on PB0 (least significant bit)
// 4*R resistor DAC bit 1 on PB1
// 2*R resistor DAC bit 2 on PB2
// 1*R resistor DAC bit 3 on PB3 (most significant bit)
// LED on PB4
// LED on PB5

// Blue Nokia 5110
// ---------------
// Signal        (Nokia 5110) LaunchPad pin
// Reset         (RST, pin 1) connected to PA7
// SSI0Fss       (CE,  pin 2) connected to PA3
// Data/Command  (DC,  pin 3) connected to PA6
// SSI0Tx        (Din, pin 4) connected to PA5
// SSI0Clk       (Clk, pin 5) connected to PA2
// 3.3V          (Vcc, pin 6) power
// back light    (BL,  pin 7) not connected, consists of 4 white LEDs which draw ~80mA total
// Ground        (Gnd, pin 8) ground

// Red SparkFun Nokia 5110 (LCD-10168)
// -----------------------------------
// Signal        (Nokia 5110) LaunchPad pin
// 3.3V          (VCC, pin 1) power
// Ground        (GND, pin 2) ground
// SSI0Fss       (SCE, pin 3) connected to PA3
// Reset         (RST, pin 4) connected to PA7
// Data/Command  (D/C, pin 5) connected to PA6
// SSI0Tx        (DN,  pin 6) connected to PA5
// SSI0Clk       (SCLK, pin 7) connected to PA2
// back light    (LED, pin 8) not connected, consists of 4 white LEDs which draw ~80mA total
/*#include "Nokia5110.h"
#include "Random.h"
#include "TExaS.h"
#include "config.h"

void DisableInterrupts(void); // Disable interrupts
void EnableInterrupts(void);  // Enable interrupts
void Timer2_Init(unsigned long period,void(* Cbk_Ptr)(void));
void Delay100ms(unsigned long count); // time delay in 0.1 seconds
unsigned long TimerCount;
unsigned long Semaphore;


*/
