# Connect 4


## Introduction:

### Connect 4 is a classic two-player board game where the objective is to be the first player to form a line of four tokens in a row, column, or diagonal on a grid. The game is played on a 7x6 grid, and each player takes turns dropping their colored tokens into one of the columns. The game ends when one player successfully connects four tokens or when the grid is full and no more moves can be made.

* Game Components:

## Grid: 
### The game is played on a rectangular grid consisting of 7 columns and 6 rows. Each cell of the grid can be empty or filled with a token of a player.


* Game Flow:

## Starting the Game: 
### The game begins with a starting screen that welcomes the players and displays the game logo. The players have the option to select the game mode, such as Player vs. AI or Player vs. Player.

## Player Turns: 
### The players take turns placing their tokens on the grid. The first player usually starts with red tokens. The current player selects a column to drop their token into by pressing the corresponding button on the game interface.

##Validating Moves: 
### Before placing a token, the game checks if the selected column is not full. If the column is already filled, the player is prompted to select a different column.
Updating the Grid: Once a valid move is made, the grid is updated with the player's token placed in the lowest available position in the selected column.
Checking for Winning Move: After each move, the game checks if the current player has formed a line of four tokens in any row, column, or diagonal. If a winning move is detected, the game declares the current player as the winner and ends.
Game Over: If no winning move is found and the grid is filled entirely, the game ends in a draw, indicating that no player has won.
AI Mode: In Player vs. AI mode, an artificial intelligence algorithm controls the AI player's movements. The AI algorithm evaluates the current state of the board and decides the best move to make. It checks for winning moves and tries to block the opponent's potential winning moves.
Restarting the Game: After a game ends, the players have the option to restart the game and play again.
Additional Features:

Arrow Indicator: The game interface includes an arrow indicator that shows the current column selection. The indicator moves horizontally as the players navigate through the columns before making their move.
Starting Screen: The game starts with a visually appealing starting screen that displays the game logo and a welcome message. The screen fades out gradually to transition to the game interface.
User Interface: The game utilizes a graphical interface, most likely implemented on a Nokia 5110 LCD display. The interface shows the grid, tokens, arrow indicator, and game messages. It provides a user-friendly interaction experience for the players.
GPIO and Interrupts: The game employs GPIO (General Purpose Input/Output) pins and interrupts to handle player input from physical buttons for selecting the column to drop the token into. The buttons are connected to the PORTF module and trigger interrupts on the falling edge.
Randomization: The game utilizes a random number generator to determine the starting player or make random moves in certain situations, such as the AI player selecting a random valid move when no winning move is available.
