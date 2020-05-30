
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "minecper.h"

#define MENU_OPTIONS "(N)ew Game\n(Q)uit\n: "


int main(int argc, char** argv) {
    
    /* Initialize rand */
    srand((unsigned int)time(NULL));
    
    int col;
    char row;
    char flag;
    const char FLAG_MARK = '*';
    char line[250];
    int main_cont = 1;
    int game_cont;
    
    
    /* MAIN LOOP*/
    while (main_cont) {
        
        printf(CLEAR_SCREEN);
        printf(WELCOME_MESSAGE);
        printf(MENU_OPTIONS);
        
        game_cont = 0;
        if (fgets(line, sizeof(line), stdin)) {
            /* Quit */
            if ((strcmp(line, "Q\n") == 0) || (strcmp(line, "q\n") == 0)) {
                game_cont = 0;
                main_cont = 0;
                printf("\nFarewell!\n\n");
            }
            /* New game */
            else if ((strcmp(line, "N\n") == 0) || (strcmp(line, "n\n") == 0)) {
                game_cont = 1;
                initialize_board();
            }
        }   
        
        /* GAME LOOP */
        while (game_cont) {

            /* Get user input */
            printf("Your move: ");
            if (fgets(line, sizeof(line), stdin)) {

                flag = '-';

                /* Check for quit */
                if ((strcmp(line, "Q\n") == 0) || (strcmp(line, "q\n") == 0)) {
                    game_cont = 0;
                }

                /* Or try to read into variable */

                /* Flag */
                else if (sscanf(line, "%c %d %c", &row, &col, &flag) == 3) {
                    if (flag == FLAG_MARK)
                        place_flag(row, col);
                    else
                        printf(BAD_SELECTION);
                }
                else if (sscanf(line, "%d %c %c", &col, &row, &flag) == 3) {
                    if (flag == FLAG_MARK)
                        place_flag(row, col);
                    else
                        printf(BAD_SELECTION);
                }

                /* Reveal */
                else if (sscanf(line, "%c %d", &row, &col) == 2) {
                    
                    game_cont = take_a_guess(row, col);
                    
                    if (game_cont == 0) {
                        printf("(Press ENTER to continue...)");
                        fgets(line, sizeof(line), stdin); /* Press enter to continue */
                    }

                }
                else if (sscanf(line, "%d %c", &col, &row) == 2) {
                    
                    game_cont = take_a_guess(row, col);
                    
                    if (game_cont == 0) {
                        printf("(Press ENTER to continue...)");
                        fgets(line, sizeof(line), stdin);
                    }
                }
                else {
                    printf(BAD_SELECTION);
                }
            }
            else {
                printf(BAD_SELECTION);
            }
        }
    }
    
    return (EXIT_SUCCESS);
}

