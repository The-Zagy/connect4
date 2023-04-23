#include <stdio.h>
#define ROWS_NUM 6
#define COLS_NUM 7

enum Position_state
{
    EMPTY,
    PLAYER1_SLOT,
    PLAYER2_SLOT
};

enum Game_state
{
    START,
    PLAYER1_TURN,
    PLAYER2_TURN,
    FINISHED
} game_state;

enum Cols_name
{
    A,
    B,
    C,
    D,
    E,
    F,
    G
};

void printGameBoard(enum Position_state board[ROWS_NUM][COLS_NUM]);
// void insertToken(enum Position_state state, int board[ROWS_NUM][COLS_NUM]);

int main()
{
    enum Position_state board[ROWS_NUM][COLS_NUM];
    // init the board
    int i, j;
    for (i = 0; i < 6; i++)
    {
        for (j = 0; j < 7; j++)
        {
            board[i][j] = EMPTY;
        }
    }
    printGameBoard(board);
    return 0;
}

void printGameBoard(enum Position_state board[ROWS_NUM][COLS_NUM])
{
    int i, j;
    printf("\tA |\tB |\tC |\tD |\tE |\tF |\tG |");
    printf("\n----------------------------------------------------------\n");

    for (i = 0; i < ROWS_NUM; i++)
    {
        printf("%i |", i + 1);
        for (j = 0; j < COLS_NUM; j++)
        {
            if (board[i][j] == EMPTY)
            {
                printf("\tZ |");
            }
            else if (board[i][j] == PLAYER1_SLOT)
            {
                printf("\tX |");
            }
            else
            {
                printf("\tY |");
            }
        }
        printf("\n----------------------------------------------------------\n");
    }
}