#include "../Nokia5110.h"
#include "../Random.h"
#include "../TExaS.h"
#include "../HAL/inc/spaceInvaders.h"



int main(void){
  
	TExaS_Init(SSI0_Real_Nokia5110_Scope);  // set system clock to 80 MHz
	Nokia5110_Init();
  Nokia5110_ClearBuffer();
	game_Init();
  // Draw the player
	
  draw_player(player);
  
  // Game loop
  while (1) {
    
    
    // Add other game logic here
  }
}






