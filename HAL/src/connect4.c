
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
#define ROWS_NUM 6
#define COLS_NUM 7
#define AC_WHITE "\x1b[37m"
#define AC_RED "\x1b[31m"
#define AC_GREEN "\x1b[32m"
#define AC_YELLOW "\x1b[33m"

// Define the push button inputs
#define MOVE_LEFT_BUTTON_PIN   4
#define MOVE_RIGHT_BUTTON_PIN  0

// Define a global variable to hold the current column name
enum Cols_name current_col = C;

// Define the game board array
position_state_t board[ROWS_NUM][COLS_NUM];

/**
 * insert new position state in certian column, and row number is managed by gravity [first empty row in this column], the row_num state from which row start searching for correct position in recursive
 * return TRUE if inserted successfully
 */
bool_t insertToken(position_state_t board[ROWS_NUM][COLS_NUM], position_state_t state, enum Cols_name col_num, unsigned row_num);
bool_t check_for_winner(position_state_t board[ROWS_NUM][COLS_NUM], position_state_t piece);
void draw_board(position_state_t board[ROWS_NUM][COLS_NUM], enum Cols_name arrow_position, enum Game_state game_state);
void init_GPIO_interrupt(void);
void draw_arrow_indicator(enum Cols_name current_col);
void draw_board_with_indicator(position_state_t board[ROWS_NUM][COLS_NUM], enum Cols_name current_col, enum Game_state game_state);
/**********************************************************************************************************************
 *  LOCAL MACROS CONSTANT\FUNCTION
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  LOCAL DATA
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL DATA
 *********************************************************************************************************************/
// image of the player's ship
// includes two blacked out columns on the left and right sides of the image to prevent smearing when moved 2 pixels to the left or right
// width=18 x height=8
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

extern Port_ConfigType Move_Right_Button;
extern Port_ConfigType Move_Left_Button;

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

// Interrupt handler for PORTF
void PortF_Handler(void)
{
    // Check if the move left button was pressed
    if (GPIO_PORTF_RIS_R & (1 << MOVE_LEFT_BUTTON_PIN))
    {
        // Clear the interrupt flag
        GPIO_PORTF_ICR_R |= (1 << MOVE_LEFT_BUTTON_PIN);
        
        // Move the player left
        move_left();
        
        // Update the current column name
        if (current_col > A)
        {
            current_col--;
        }
				draw_board_with_indicator(board,current_col,1);

    }
    
    // Check if the move right button was pressed
    if (GPIO_PORTF_RIS_R & (1 << MOVE_RIGHT_BUTTON_PIN))
    {
        // Clear the interrupt flag
        GPIO_PORTF_ICR_R |= (1 << MOVE_RIGHT_BUTTON_PIN);
        
        // Move the player right
        move_right();
        
        // Update the current column name
        if (current_col < G)
        {
            current_col++;
        }
				draw_board_with_indicator(board,current_col,1);

    }
}

void game_Init(void)
{
  Port_Init(&Move_Right_Button);
  Port_Init(&Move_Left_Button);
  IntCtrl_EnableIRQ(GPIO_PortF_IRQn);
}

void draw_player(Player p)
{
}

// Clear the player from the screen
void clear_player(Player p)
{
}

// Move the player left
void move_left(void)
{
  clear_player(player);
  player.x -= 1;
  draw_player(player);
}

// Move the player right
void move_right(void)
{
  clear_player(player);
  player.x += 1;
  draw_player(player);
}

bool_t insertToken(position_state_t board[ROWS_NUM][COLS_NUM], position_state_t state, enum Cols_name col_num, unsigned row_num)
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
    return insertToken(board, state, col_num, row_num + 1);
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
  if (game_state == GAME_PLAYER1_TURN)
  {
    Nokia5110_OutString("P1");
  }
  else
  {
    Nokia5110_OutString("P2");
  }
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
