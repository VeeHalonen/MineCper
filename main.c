
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "minecper.h"


int main(int argc, char** argv) {
    
    /* Initialize rand */
    srand((unsigned int)time(NULL));
    
    int col;
    char row;
    char flag;
    const char FLAG_MARK = '*';
    char line[250];
    int cont = 1;
    
    initialize_board();
    print_minefield();
    
    while (cont) {
        
        /* Get user input */
        printf("Your move: ");
        if (fgets(line, sizeof(line), stdin)) {
            
            flag = '-';
            
            /* Check for quit */
            if ((strcmp(line, "Q\n") == 0) || (strcmp(line, "q\n") == 0)) {
                cont = 0;
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
                cont = take_a_guess(row, col);
                
            }
            else if (sscanf(line, "%d %c", &col, &row) == 2) {
                cont = take_a_guess(row, col);
            }
            else {
                printf(BAD_SELECTION);
            }
        }
        else {
            printf(BAD_SELECTION);
        }
    }
    
    return (EXIT_SUCCESS);
}

