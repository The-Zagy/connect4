#include "../Nokia5110.h"
#include "../Random.h"
#include "../TExaS.h"
#include "../HAL/inc/connect4.h"

extern int move_right_flag;
extern int move_left_flag;
extern int done = 0;
int main(void)
{
  game_state_t game_state = GAME_SELECT_MODE;
  game_mode_t game_mode = MULTI_PLAYER;
  cols_name_t cur_col = A;
  position_state_t board[ROWS_NUM][COLS_NUM] = {EMPTY};
  TExaS_Init(SSI0_Real_Nokia5110_Scope); // set system clock to 80 MHz
  Nokia5110_Init();
  Nokia5110_ClearBuffer();
  game_Init();
  starting_screen();
  Nokia5110_ClearBuffer();
	Nokia5110_Clear();
  select_mode(1);
 endScreen();

  while (game_state == GAME_SELECT_MODE)
  {

    if (move_right_flag == 1)
    {
      move_right_flag = 0;
      game_mode = (game_mode + 1) % 2;

      Nokia5110_ClearBuffer();
      Nokia5110_Clear();
      select_mode(game_mode);
    }
    if (move_left_flag == 1)
    {
      // commit mode
      move_right_flag = 0;
     
      game_state = GAME_PLAYER1_TURN;
    
    }
  }

  while (1)
  {
    position_state_t slot;
    if (game_state == GAME_PLAYER1_TURN)
    {
      slot = PLAYER1_SLOT;
    }
    else if (game_state == GAME_PLAYER2_TURN)
    {
      slot = PLAYER2_SLOT;
    }
    else if (game_state == GAME_AI_TURN)
    {
      slot = PLAYER2_SLOT;
      cur_col=ai_player(board);
    }
   
    if (move_right_flag == 1 )
    {
      // do move right code
     if(game_state != GAME_AI_TURN){ cur_col = (cur_col + 1) % 7; }
      move_right_flag = 0;
      Nokia5110_ClearBuffer();
      draw_board(board, cur_col, game_state);
    }
    if (move_left_flag == 1)
    {
      // do insert logic
      move_left_flag = 0;
      insert_token(board, slot, cur_col, 0);
      Nokia5110_ClearBuffer();
      Nokia5110_Clear();
      if (check_for_winner(board, slot) == TRUE)
      {
        // todo print winner
        done=1;
        return 0;
      };
      if (game_state == GAME_PLAYER1_TURN )
      {
       if(game_mode == MULTI_PLAYER){ game_state = GAME_PLAYER2_TURN;}else{game_state = GAME_AI_TURN;}
      }
      else
      {
        game_state = GAME_PLAYER1_TURN;
      }
      
      draw_board(board, cur_col, game_state);
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
