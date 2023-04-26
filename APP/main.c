#include "../Nokia5110.h"
#include "../Random.h"
#include "../TExaS.h"
#include "../HAL/inc/connect4.h"



int main() {
  
	game_Init();
  TExaS_Init(SSI0_Real_Nokia5110_Scope);  // set system clock to 80 MHz
  Nokia5110_Init();
  Nokia5110_ClearBuffer();
  // Draw the player
	
  draw_player(player);
  
  // Game loop
  while (1) {
    
    
    // Add other game logic here
  }
}






