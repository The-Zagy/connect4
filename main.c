#include <stdio.h>
#include <stdlib.h>

#define ROWS_NUM 6
#define COLS_NUM 7
#define AC_WHITE "\x1b[37m"
#define AC_RED "\x1b[31m"
#define AC_GREEN "\x1b[32m"
#define AC_YELLOW "\x1b[33m"


typedef enum Boolean
{
    FALSE,
    TRUE
} bool_t;   

typedef enum Position_state
{
    EMPTY,
    PLAYER1_SLOT,
    PLAYER2_SLOT
} position_state_t;

enum Game_state
{
    GAME_START,
    GAME_PLAYER1_TURN,
    GAME_PLAYER2_TURN,
    GAME_FINISHED
} game_state;

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

void printGameBoard(position_state_t board[ROWS_NUM][COLS_NUM]);
/**
 * insert new position state in certian column, and row number is managed by gravity [first empty row in this column], the row_num state from which row start searching for correct position in recursive
 * return TRUE if inserted successfully
 */
bool_t insertToken(position_state_t board[ROWS_NUM][COLS_NUM], position_state_t state, enum Cols_name col_num, size_t row_num);
int ai_player(position_state_t board[ROWS_NUM][COLS_NUM]);
/**
 * return Cols_name or -1 if not valid input
 */
enum Cols_name parseInput(char c);
bool_t check_for_winner(position_state_t board[ROWS_NUM][COLS_NUM], position_state_t piece);

int main()
{
    position_state_t board[ROWS_NUM][COLS_NUM];
    char input;
    enum Cols_name parsed_input;
    // init the board
    int i, j;
    for (i = 0; i < 6; i++)
    {
        for (j = 0; j < 7; j++)
        {
            board[i][j] = EMPTY;
        }
    }
    game_state = GAME_START;

    // game loop
    while (game_state != GAME_FINISHED)
    {
        // manage turn between players?
        if (game_state == GAME_START)
        {
            game_state = GAME_PLAYER1_TURN;
        }
        else if (game_state == GAME_PLAYER1_TURN)
        {
            game_state = GAME_PLAYER2_TURN;
        }
        else if (game_state == GAME_PLAYER2_TURN)
        {
            game_state = GAME_PLAYER1_TURN;
        }
        else
        {
            game_state = GAME_FINISHED;
        }

        // print
        system("clear");
        system("cls");
        printGameBoard(board);

        // try to take input until it's valid one
        while (1)
        {
            // take input based on the turn
            if (game_state == GAME_PLAYER1_TURN)
            {
                puts("PLAYER 1: ");
                input = getchar();
            }
            else if (game_state == GAME_PLAYER2_TURN)
            {
                puts("PLAYER 2: ");
                input = ai_player(board);
            }
            if (game_state == GAME_PLAYER1_TURN){ getchar();}
            // if valid break out
            parsed_input = parseInput(input);
            if (parsed_input != COL_NOT_VALID)
            {
                break;
            }
            puts("Enter Valid COlumn name \"A, B, C, D, E, F, G\"\n");
        }

        // the previous while won't let us get here unless we do have valid column name
        insertToken(board, game_state == GAME_PLAYER1_TURN ? PLAYER1_SLOT : PLAYER2_SLOT, parsed_input, 0);
        system("clear");
        system("cls");
        printGameBoard(board);

        // check for win, if win set game state to finish
        if (
            check_for_winner(board, game_state == GAME_PLAYER1_TURN ? PLAYER1_SLOT : PLAYER2_SLOT) == TRUE)
        {
            if (game_state == GAME_PLAYER1_TURN)
            {
                puts("PLAYER1 WINS");
            }
            else
            {
                puts("PLAYER2 WINS");
            }
            game_state = GAME_FINISHED;
        }
    }

    return 0;
}

void printGameBoard(position_state_t board[ROWS_NUM][COLS_NUM])
{
    int i, j;
    printf("%s\tA |\tB |\tC |\tD |\tE |\tF |\tG |", AC_WHITE);
    printf("\n----------------------------------------------------------\n");

    for (i = 0; i < ROWS_NUM; i++)
    {
        printf("%s%i |", AC_WHITE, i + 1);
        for (j = 0; j < COLS_NUM; j++)
        {
            if (board[i][j] == EMPTY)
            {
                printf("%s\t  |", AC_YELLOW);
            }
            else if (board[i][j] == PLAYER1_SLOT)
            {
                printf("%s\tX |", AC_GREEN);
            }
            else
            {
                printf("%s\tY |", AC_RED);
            }
        }
        printf("\n----------------------------------------------------------\n");
    }
    printf("\n");
}

bool_t insertToken(position_state_t board[ROWS_NUM][COLS_NUM], position_state_t state, enum Cols_name col_num, size_t row_num)
{
    // don't go out of scope
    if (col_num >= COLS_NUM || col_num < 0 || row_num >= ROWS_NUM || row_num < 0)
    {
        return FALSE;
    }
    // can't insert in full column
    // go down the rows until you find empty row and the one before it is full or you reached the floor

    // reached non empty field means no free space in this column
    if (board[row_num][col_num] != EMPTY)
    {
        return FALSE;
    }

    // empty then non-empty or ground is the one satisfy the gravity
    if (board[row_num][col_num] == EMPTY && (board[row_num + 1][col_num] != EMPTY || row_num == ROWS_NUM - 1))
    {
        board[row_num][col_num] = state;
        return TRUE;
    }
    else
    {
        return insertToken(board, state, col_num, row_num + 1);
    }
    return FALSE;
}

int ai_player(position_state_t board[ROWS_NUM][COLS_NUM]) {
    // Evaluate the current state of the board and make a decision
    // You can modify this part to implement your desired AI algorithm

    // Check for a winning move
    for (int col = 0; col < COLS_NUM; col++) {
        for (int row = 0; row < ROWS_NUM; row++) {
            if (board[row][col] == 0) {
                // Check horizontally
                if (col < COLS_NUM - 3 && board[row][col+1] == board[row][col+2] == board[row][col+3] && board[row][col+1] != 0) {
                    return col;
                }
                // Check vertically
                if (row < ROWS_NUM - 3 && board[row+1][col] == board[row+2][col] == board[row+3][col] && board[row+1][col] != 0) {
                    return col;
                }
                // Check diagonally (ascending)
                if (col < COLS_NUM - 3 && row > 2 && board[row-1][col+1] == board[row-2][col+2] == board[row-3][col+3] && board[row-1][col+1] != 0) {
                    return col;
                }
                // Check diagonally (descending)
                if (col < COLS_NUM - 3 && row < ROWS_NUM - 3 && board[row+1][col+1] == board[row+2][col+2] == board[row+3][col+3] && board[row+1][col+1] != 0) {
                    return col;
                }
            }
        }
    }

    // If no winning move is found, make a random valid move
    int valid_moves[COLS_NUM];
    int num_valid_moves = 0;

    // Find valid moves
    for (int col = 0; col < COLS_NUM; col++) {
        if (board[ROWS_NUM-1][col] == 0) {
            valid_moves[num_valid_moves] = col;
            num_valid_moves++;
        }
    }

    // Choose a random valid move
    int random_move_index = rand() % num_valid_moves;
    return valid_moves[random_move_index];
}

enum Cols_name parseInput(char c)
{
    if (c == 'a' || c == 'A' || c == 0)
    {
        return A;
    }
    if (c == 'b' || c == 'B' || c == 1)
    {
        return B;
    }
    if (c == 'c' || c == 'C' || c == 2)
    {
        return C;
    }
    if (c == 'd' || c == 'D' || c == 3)
    {
        return D;
    }
    if (c == 'e' || c == 'E' || c == 4)
    {
        return E;
    }
    if (c == 'f' || c == 'F' || c == 5)
    {
        return F;
    }
    if (c == 'g' || c == 'G' || c == 6)
    {
        return G;
    }
    return COL_NOT_VALID;
}

bool_t check_for_winner(position_state_t board[ROWS_NUM][COLS_NUM], position_state_t piece)
{
    // Check horizontal locations for win
    for (int c = 0; c < COLS_NUM - 3; c++)
    {
        for (int r = 0; r < ROWS_NUM; r++)
        {
            if (board[r][c] == piece && board[r][c + 1] == piece && board[r][c + 2] == piece && board[r][c + 3] == piece)
            {
                return TRUE;
            }
        }
    }

    // Check vertical locations for win
    for (int c = 0; c < COLS_NUM; c++)
    {
        for (int r = 0; r < ROWS_NUM - 3; r++)
        {
            if (board[r][c] == piece && board[r + 1][c] == piece && board[r + 2][c] == piece && board[r + 3][c] == piece)
            {
                return TRUE;
            }
        }
    }

    // Check positively sloped diagonals
    for (int c = 0; c < COLS_NUM - 3; c++)
    {
        for (int r = 0; r < ROWS_NUM - 3; r++)
        {
            if (board[r][c] == piece && board[r + 1][c + 1] == piece && board[r + 2][c + 2] == piece && board[r + 3][c + 3] == piece)
            {
                return TRUE;
            }
        }
    }

    // Check negatively sloped diagonals
    for (int c = 0; c < COLS_NUM - 3; c++)
    {
        for (int r = 3; r < ROWS_NUM; r++)
        {
            if (board[r][c] == piece && board[r - 1][c + 1] == piece && board[r - 2][c + 2] == piece && board[r - 3][c + 3] == piece)
            {
                return TRUE;
            }
        }
    }

    return FALSE;
}
