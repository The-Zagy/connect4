#ifndef SPACE_INVADERS_H_
#define SPACE_INVADERS_H_

#define PLAYERW    	 			((unsigned char)PlayerShip0[18])
#define PLAYERH     			((unsigned char)PlayerShip0[22])
#define SCREEN_WIDTH 			84
#define SCREEN_HEIGHT 		48
#define PLAYER_WIDTH 			18
#define PLAYER_HEIGHT 		8

// Define a struct to store player position
typedef struct {
  int x;
  int y;
} Player;

extern Player player;

extern const unsigned char PlayerShip0[] ;

void draw_player(Player p) ;
void clear_player(Player p); 
void move_left(void); 
void move_right(void);
void game_Init(void);

#endif
