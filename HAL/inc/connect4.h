#ifndef CONNTECT_4_H_
#include "../MCAL/PORT/Inc/Port_Cfg.h"
#define CONNTECT_4_H_
#define ROWS_NUM 6
#define COLS_NUM 7
#define CELL_WIDTH 12
#define CELL_HEIGHT 6
#define PLAYERW ((unsigned char)PlayerShip0[18])
#define PLAYERH ((unsigned char)PlayerShip0[22])
#define SCREEN_WIDTH 84
#define SCREEN_HEIGHT 48
#define PLAYER_WIDTH 18
#define PLAYER_HEIGHT 8

extern Port_ConfigType Move_Right_Button;
extern Port_ConfigType Move_Left_Button;
extern Port_ConfigType Action_Button;

extern GPIO_EXTI_ConfigType EXTI_Right_Button;
extern GPIO_EXTI_ConfigType EXTI_Left_Button;
extern GPIO_EXTI_ConfigType EXTI_Action_Button;

extern IntCtr_Config Int_Right_Button;
extern IntCtr_Config Int_Left_Button;
extern IntCtr_Config Int_Action_Button;
// Define a struct to store player position
typedef struct
{
  int x;
  int y;
} Player;
typedef enum Boolean
{
  FALSE_t,
  TRUE_t
} bool_t;

typedef enum Cols_name
{
  A,
  B,
  C,
  D,
  E,
  F,
  G,
  COL_NOT_VALID = -1
} cols_name_t;
typedef enum Game_state
{
  GAME_SELECT_MODE,
  GAME_PLAYER1_TURN,
  GAME_PLAYER2_TURN,
  GAME_AI_TURN,
  GAME_START,
  GAME_FINISHED
} game_state_t;

typedef enum Position_state
{
  EMPTY,
  PLAYER1_SLOT,
  PLAYER2_SLOT,
  AI_SLOT
} position_state_t;

typedef enum Game_mode
{
  SINGLE_PLAYER,
  MULTI_PLAYER
} game_mode_t;

typedef struct Game_data
{
  position_state_t boards[ROWS_NUM][COLS_NUM];
  game_state_t game_state;
  game_mode_t game_mode;
} game_data_t;

extern Player player;

extern const unsigned char PlayerShip0[];

void draw_board(position_state_t board[ROWS_NUM][COLS_NUM], enum Cols_name arrow_position, enum Game_state game_state);
void game_Init(void);
void starting_screen(void);
void select_mode(game_mode_t mode);
bool_t insert_token(position_state_t board[ROWS_NUM][COLS_NUM], position_state_t state, enum Cols_name col_num, unsigned row_num);
bool_t check_for_winner(position_state_t board[ROWS_NUM][COLS_NUM], position_state_t piece);
#endif
