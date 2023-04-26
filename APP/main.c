#include "../Nokia5110.h"
#include "../Random.h"
#include "../TExaS.h"
#include "../HAL/inc/connect4.h"
extern const unsigned char empty_cell[];
extern const unsigned char PlayerShip0[];
int main(void)
{
  position_state_t board[ROWS_NUM][COLS_NUM] = {EMPTY};
  TExaS_Init(SSI0_Real_Nokia5110_Scope); // set system clock to 80 MHz
  Nokia5110_Init();
  Nokia5110_ClearBuffer();
  // game_Init();
  //  Draw the player
  // Nokia5110_PrintBMP(20, 20, empty_cell, 0);
  // Nokia5110_DisplayBuffer(); // draw buffer
  // Nokia5110_PrintBMP(20, 20, PlayerShip0, 0);
  // Nokia5110_DisplayBuffer(); // draw buffer
  draw_board(board, 3, 1);

  // Game loop
  while (1)
  {

    // Add other game logic here
  }
}
