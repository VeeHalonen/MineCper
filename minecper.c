
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#include "minecper.h"

static const int SIZE = 8;
static const int NO_OF_MINES = 10;
static int moves_left; /* N:o of non-mine squares left */
static int mines_left;
static const char UNREVEALED = '_';
static const char MINE = '*';
static const char FLAG = 'c';
static const char WRONG_FLAG = 'x';
static char board[SIZE][SIZE];
static char minefield[SIZE][SIZE];

void initialize_board() {
    
    int i, j, x, y;
    int mines_placed = 0;
    
    moves_left = SIZE*SIZE-NO_OF_MINES;
    mines_left = NO_OF_MINES;
    
    
    /* Player board */
    for (i = 0; i < SIZE; i++) {
        for (j = 0; j < SIZE; j++) {
            board[i][j] = UNREVEALED;
        }
    }
    
    /* Make sure all mines fit before adding */
    if (SIZE*SIZE < NO_OF_MINES)
        return;
    
    /* Clear/initialize minefield */
    for (i = 0; i < SIZE; i++) {
        for (j = 0; j < SIZE; j++) {
            minefield[i][j] = 'x';
        }
    }
    
    /* Mines */
    while (mines_placed < NO_OF_MINES) {
        
        /* Random index */
        x = (rand()%(SIZE));
        y = (rand()%(SIZE));
        
        /* Try to place mine */
        if (minefield[y][x] != MINE) {
            minefield[y][x] = MINE;
            mines_placed++;
        }
    }
    
    /* The rest */
    for (i = 0; i < SIZE; i++) {
        for (j = 0; j < SIZE; j++) {
            /* Calculate mines */
            if (minefield[i][j] != MINE) {
                minefield[i][j] = '0' + calculate_mines(i, j); /* Convert to ASCII */
            }
        }
    }
    print_board();
}

/* Prints the player board */
static void print_board() {
    
    printf(CLEAR_SCREEN);
    printf(WELCOME_MESSAGE);
    printf(INSTRUCTIONS);
    
    int i, j;
    char letter = 'A';
    
    /* First row */
    printf("\n      ");
    for (i = 1; i <= SIZE; i++) {
        printf("%d ", i);
    }
    printf("%c", '\n');
    
    /* The rest */
    for (i = 0; i < SIZE; i++) {
        printf("   %c ", letter);
        letter++;
        for (j = 0; j < SIZE; j++) {
            /* Print mines in red */
            printf("|");
            if (board[i][j] == MINE) {
                print_char_red(board[i][j]);
            }
            /* Print correct flags in blue */
            else if (board[i][j] == FLAG) {
                print_char_blue(board[i][j]);
            }
            /* Print wrong flags as yellow */
            else if (board[i][j] == WRONG_FLAG) {
                print_char_yellow(WRONG_FLAG);
            }
            else {
                printf("%c", board[i][j]);
            }
        }
        printf("|%c", '\n');
    }
    printf("%c", '\n');
    printf("Mines left: %d\n\n", mines_left);
}

/* Helper function, prints the minefield "cheat sheet" */
void print_minefield() {
    int i, j;
    char letter = 'A';
    
    /* First row */
    printf("    ");
    for (i = 1; i <= SIZE; i++) {
        printf("%d ", i);
    }
    printf("%c", '\n');
    
    /* The rest */
    for (i = 0; i < SIZE; i++) {
        printf(" %c ", letter);
        letter++;
        for (j = 0; j < SIZE; j++) {
            printf("|");
            if (minefield[i][j] == MINE) {
                print_char_red(minefield[i][j]);
            }
            else {
                printf("%c", minefield[i][j]);
            }
        }
        printf("|%c", '\n');
    }
    printf("%c", '\n');

}

static void reveal_mines() {
    int i, j;
    
    /* Mark mines and wrong flags */
    for (i = 0; i < SIZE; i++) {
        for (j = 0; j < SIZE; j++) {
            if (minefield[i][j] == MINE && board[i][j] != FLAG)
                board[i][j] = MINE;
            if (minefield[i][j] != MINE && board[i][j] == FLAG) {
                board[i][j] = WRONG_FLAG;
                mines_left++; /* Add mine back since the flag was wrong */
            }
        }
    }
    print_board();
}


/* Flags unflagged mines at the end of a game */
static void flag_correct_mines() {
    int i, j;
    
    for (i = 0; i < SIZE; i++) {
        for (j = 0; j < SIZE; j++) {
            if (minefield[i][j] == MINE && board[i][j] != FLAG)
                board[i][j] = FLAG;
            /* Also marks wrong flags, though there should never be any at this point */
            if (minefield[i][j] != MINE && board[i][j] == FLAG)
                board[i][j] = WRONG_FLAG;
        }
    }
    print_board();
}


/* Calculates and returns the number of mines around given index */
static int calculate_mines(int row, int col) {
    
    int count = 0;
    
    /* Set bounds to be within array indices */
    
    int i, j, start_j, end_i, end_j;
    
    if ((row-1) < 0)
        i = 0;
    else
        i = row-1;
    
    if ((col-1) < 0)
        start_j = 0;
    else
        start_j = col-1;
    
    if ((row+1) >= SIZE)
        end_i = SIZE-1;
    else
        end_i = row+1;
    
    if ((col+1) >= SIZE)
        end_j = SIZE-1;
    else
        end_j = col+1;
    
    /* Loop through the area to find mines */
    for (; i <= end_i; i++) {
        for (j = start_j; j <= end_j; j++) {
            if (minefield[i][j] == MINE) {
                count++;
            }
            
        }
    }
    return count;
}

/* Converts given character into row index.
   Returns -1 if not found. */
int get_row(char row) {
    
    int row_int;
    char row_indexer = 'A';
    char selection = toupper(row);  /* Ignore case */
    
    /* If corresponding row is found, return it */
    for (row_int = 0; row_int < SIZE; row_int++) {
        if (row_indexer == selection) {
            return row_int;
        }
        row_indexer++;
    }
    
    /* If not found, return -1 */
    return -1;
    
}

/* Places a flag on the board */
void place_flag(char row, int col) {
    
    int row_i;
    int col_i = col-1;
    
    /* Check that index is valid before proceeding */
    if ((col <= 0) || (col > SIZE)) {
        printf(BAD_SELECTION);
        return;
    }
    row_i = get_row(row);
    if (row_i == -1) {
        printf(BAD_SELECTION);
        return;
    }
    
    /* If there was already a flag, remove it */
    if (board[row_i][col_i] == FLAG) {
        board[row_i][col_i] = UNREVEALED;
        mines_left++; /* Add mine back */
    }
    /* Or place new flag if possible */
    else if (board[row_i][col_i] == UNREVEALED) {
        board[row_i][col_i] = FLAG;
        mines_left--;
    }
    
    print_board();
    
}

/* Converts user's selection, e.g. A1, into an array index, e.g. [0][0].
   Also calls reveal_selection to handle user selection.
   Returns the number of available moves - 0 means game over. */
int take_a_guess(char row, int col) {
    
    int row_int;
    
    /* Check that column index is valid before proceeding */
    if ((col <= 0) || (col > SIZE)) {
        printf(BAD_SELECTION);
        return 1;
    }
    
    row_int = get_row(row);
    if (row_int == -1) {
        printf(BAD_SELECTION);
        return 1;
    }
    
    return reveal_selection(row_int, col-1);
}

/* Reveals all the fields around the given index, returns moves left */
static int reveal_selection(int row, int col) {
    
    /* Selected square already open? Simply return */
    if (minefield[row][col] == board[row][col]) {
        return moves_left;
    }
    /* Selected square flagged? Return */
    if (board[row][col] == FLAG) {
        return moves_left;
    }
    
    /* If no mines around, reveal all fields around as well */
    if (minefield[row][col] == '0') {
        reveal_around_zero(row, col);
    }
    /* If user hits a mine, game over */
    else if (minefield[row][col] == MINE) {
        moves_left = 0;
        reveal_mines();
        printf("GAME OVER!\n\n");
        return moves_left;
    }
    /* In other cases, reveal the selection and update board */
    else {
        board[row][col] = minefield[row][col];
        moves_left--;
    }
    
    /* If there are no moves left, it's a victory! Return game over. */
    if (moves_left == 0) {
        flag_correct_mines();
        printf("YOU WIN!\n\n");
    }
    else {
        print_board();
    }
    
    return moves_left;
}

static void reveal_around_zero(int row, int col) {
    
    /* Do not reveal if flagged */
    if(board[row][col] == FLAG)
        return;
    
    /* Reveal current if not already revealed */
    if (board[row][col] != minefield[row][col]) {
        board[row][col] = minefield[row][col];
        moves_left--;
    }
    
    /* Recursively reveal around all other revealed zero-fields as well */
    if (minefield[row][col] == '0') {
        
        /* Find surrounding cells */
    
        int i, j, start_j, end_i, end_j;
        
        if ((row-1) < 0)
            i = 0;
        else
            i = row-1;

        if ((col-1) < 0)
            start_j = 0;
        else
            start_j = col-1;

        if ((row+1) >= SIZE)
            end_i = SIZE-1;
        else
            end_i = row+1;

        if ((col+1) >= SIZE)
            end_j = SIZE-1;
        else
            end_j = col+1;
        
        for (; i <= end_i; i++) {
            for (j = start_j; j <= end_j; j++) {
                /* Recursion time! */
                if ((minefield[i][j] == '0') && (board[i][j] != minefield[i][j])) {
                    reveal_around_zero(i, j);
                }
                if (board[i][j] != minefield[i][j] && board[i][j] != FLAG) {
                    board[i][j] = minefield[i][j];
                    moves_left--;
                }
            }
        }
    }
}


/* Prints given character in red */
static void print_char_red(char c) {
    printf("\033[1;31m");
    printf("%c", c);
    printf("\033[0m");
}

/* Prints given character in blue */
static void print_char_blue(char c) {
    printf("\033[1;34m");
    printf("%c", c);
    printf("\033[0m");
}

/* Prints given character in yellow */
static void print_char_yellow(char c) {
    printf("\033[1;33m");
    printf("%c", c);
    printf("\033[0m");
}

/* Prints given character in green */
static void print_char_green(char c) {
    printf("\033[1;32m");
    printf("%c", c);
    printf("\033[0m");
}

