#include "../Nokia5110.h"
#include "../Random.h"
#include "../TExaS.h"
#include "../HAL/inc/connect4.h"

extern int move_right_flag;
extern int move_left_flag;
int main(void)
{
  int cur_cell = 0;
  game_mode_t game_mode = SINGLE_PLAYER;
  position_state_t board[ROWS_NUM][COLS_NUM] = {EMPTY};

  TExaS_Init(SSI0_Real_Nokia5110_Scope); // set system clock to 80 MHz
  Nokia5110_Init();
  Nokia5110_ClearBuffer();
  game_Init();
  starting_screen();
  Nokia5110_ClearBuffer();
  // select_mode(game_mode);
  draw_board(board, cur_cell, 1);
  // endScreen();

  // Game loop
  while (1)
  {
    if (move_right_flag == 1)
    {
      // do move right code
      cur_cell = (cur_cell + 1) % 7;
      move_right_flag = 0;
      Nokia5110_ClearBuffer();
      draw_board(board, cur_cell, 1);
    }
    if (move_left_flag == 1)
    {
      // do move left work
      cur_cell = (cur_cell - 1) % 7;
      move_left_flag = 0;
      Nokia5110_ClearBuffer();
      draw_board(board, cur_cell, 1);
    }
    // Add other game logic here
  }
}
