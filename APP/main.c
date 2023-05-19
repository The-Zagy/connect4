#include "../Nokia5110.h"
#include "../Random.h"
#include "../TExaS.h"
#include "../HAL/inc/connect4.h"

extern int move_right_flag;
extern int move_left_flag;
int main(void)
{
  int i, j;
  game_state_t game_state = GAME_SELECT_MODE;
  game_mode_t game_mode = SINGLE_PLAYER;
  cols_name_t cur_col = A;
  position_state_t board[ROWS_NUM][COLS_NUM] = {EMPTY};
  position_state_t slot;

  TExaS_Init(SSI0_Real_Nokia5110_Scope); // set system clock to 80 MHz
  Nokia5110_Init();
  Nokia5110_ClearBuffer();
  game_Init();
  starting_screen();
  Nokia5110_ClearBuffer();
  Nokia5110_Clear();
  select_mode(game_mode);

  while (1)
  {
    // stuck until choose mode
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
        move_left_flag = 0;
        game_mode = (game_mode + 1) % 2;
        Nokia5110_ClearBuffer();
        Nokia5110_Clear();
        select_mode(game_mode);
      }

      if (action_flag == 1)
      {
        // commit mode
        action_flag = 0;
        game_state = GAME_PLAYER1_TURN;
        draw_board(board, cur_col, game_state);
      }
    }

    if (game_state == GAME_PLAYER1_TURN)
    {
      slot = PLAYER1_SLOT;
    }
    else if (game_state == GAME_PLAYER2_TURN || game_state == GAME_AI_TURN)
    {
      slot = PLAYER2_SLOT;
    }

    if (move_right_flag == 1)
    {
      move_right_flag = 0;
      cur_col = (cur_col + 1) % 7;
      Nokia5110_ClearBuffer();
      Nokia5110_Clear();
      draw_board(board, cur_col, game_state);
    }

    if (move_left_flag == 1)
    {
      move_left_flag = 0;
      cur_col = (cur_col + 1) % 7;
      Nokia5110_ClearBuffer();
      Nokia5110_Clear();
      draw_board(board, cur_col, game_state);
    }

    if (action_flag == 1 || game_state == GAME_AI_TURN)
    {
      action_flag = 0;
      if (game_mode == SINGLE_PLAYER && game_state == GAME_AI_TURN)
      {
        cur_col = ai_player(board);
      }
      insert_token(board, slot, cur_col, 0);
      Nokia5110_ClearBuffer();
      Nokia5110_Clear();
      draw_board(board, cur_col, game_state);

      // check for winner
      if (check_for_winner(board, slot) == TRUE)
      {
        game_state = slot == PLAYER1_SLOT ? GAME_PLAYER1_WON : GAME_PLAYER2_WON;
        endScreen(game_state);
        game_state = GAME_SELECT_MODE;
        Nokia5110_ClearBuffer();
        Nokia5110_Clear();
        select_mode(game_mode);
        for (i = 0; i < ROWS_NUM; ++i)
        {
          for (j = 0; j < COLS_NUM; ++j)
          {
            board[i][j] = EMPTY;
          }
        }
        game_mode = SINGLE_PLAYER;
        cur_col = A;
      }
      // switch turns at the end of each run
      else if (game_state == GAME_PLAYER1_TURN)
      {
        if (game_mode == MULTI_PLAYER)
        {
          game_state = GAME_PLAYER2_TURN;
        }
        else
        {
          game_state = GAME_AI_TURN;
        }
        draw_board(board, cur_col, game_state);
      }
      else
      {
        game_state = GAME_PLAYER1_TURN;
        draw_board(board, cur_col, game_state);
      }
    }
  }
}
