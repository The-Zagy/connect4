#include "../Nokia5110.h"
#include "../Random.h"
#include "../TExaS.h"
#include "../HAL/inc/connect4.h"

extern int move_right_flag;
extern int move_left_flag;
int main(void)
{
  cols_name_t cur_col = A;
  game_mode_t game_mode = MULTI_PLAYER;
  position_state_t board[ROWS_NUM][COLS_NUM] = {EMPTY};
  TExaS_Init(SSI0_Real_Nokia5110_Scope); // set system clock to 80 MHz
  Nokia5110_Init();
  Nokia5110_ClearBuffer();
  game_Init();
  starting_screen();
  Nokia5110_ClearBuffer();
  // select_mode(game_mode);
  // draw_board(board, cur_cell, 1);
  // endScreen();

  // Game loop
  while (1)
  {
    //* example use left to insert, and right to move
    if (move_right_flag == 1)
    {
      // do move right code
      cur_col = (cur_col + 1) % 7;
      move_right_flag = 0;
      Nokia5110_ClearBuffer();
      draw_board(board, cur_col, 1);
    }
    if (move_left_flag == 1)
    {
      // do insert logic
      move_left_flag = 0;
      insert_token(board, PLAYER2_SLOT, cur_col, 0);
      Nokia5110_ClearBuffer();
      Nokia5110_Clear();
      draw_board(board, cur_col, 1);
    }

    //* choose mode example
    // if (move_right_flag == 1)
    // {
    //   // do move right code
    //   game_mode = (game_mode + 1) % 2;
    //   move_right_flag = 0;
    //   Nokia5110_ClearBuffer();
    //   Nokia5110_Clear();
    //   select_mode(game_mode);
    // }
    // if (move_left_flag == 1)
    // {
    //   // do move left work
    //   game_mode = MULTI_PLAYER;
    //   move_left_flag = 0;
    //   Nokia5110_Clear();
    //   Nokia5110_ClearBuffer();
    //   select_mode(game_mode);
    // }

    //* move column for insert example
    // if (move_right_flag == 1)
    // {
    //   // do move right code
    //   cur_col = (cur_col + 1) % 7;
    //   move_right_flag = 0;
    //   Nokia5110_ClearBuffer();
    //   draw_board(board, cur_col, 1);
    // }
    // if (move_left_flag == 1)
    // {
    //   // do move left work
    //   cur_col = (cur_col - 1) % 7;
    //   move_left_flag = 0;
    //   Nokia5110_ClearBuffer();
    //   draw_board(board, cur_col, 1);
    // }
    // Add other game logic here
  }
}
