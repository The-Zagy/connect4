#ifndef CONNTECT_4_H_
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

enum Cols_name
{
  A,
  B,
  C,
  D,
  E,
  F,
  G,
  COL_NOT_VALID = -1
};

typedef enum Position_state
{
  EMPTY,
  PLAYER1_SLOT,
  PLAYER2_SLOT
} position_state_t;

extern Player player;

extern const unsigned char PlayerShip0[];

void draw_board(position_state_t board[ROWS_NUM][COLS_NUM]);
void draw_player(Player p);
void clear_player(Player p);
void move_left(void);
void move_right(void);
void game_Init(void);

#endif
