
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "minecper.h"


int main(int argc, char** argv) {
    
    /* Initialize rand */
    srand((unsigned int)time(NULL));
    
    int i;
    char c;
    char line[250];
    int cont = 1;
    
    initialize_board();
    print_minefield();
    
    while (cont) {
        
        /* Get user input */
        printf("Your move: ");
        if (fgets(line, sizeof(line), stdin)) {
            
            /* Check for quit */
            if ((strcmp(line, "Q\n") == 0) || (strcmp(line, "q\n") == 0)) {
                cont = 0;
            }
            
            /* Or try to read into variable */
            else if (sscanf(line, "%c %d", &c, &i) == 2) {
                cont = take_a_guess(c, i);
                
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

