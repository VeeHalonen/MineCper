
#ifndef MINECPER_H
#define MINECPER_H

#define CLEAR_SCREEN "\033[1;1H\033[2J"
#define BAD_SELECTION "\nInvalid selection.\n\n"

#define WELCOME_MESSAGE "\n\
c * c * c * c * c * c * c\n\
   Welcome to MineCper   \n\
c * c * c * c * c * c * c\n\n"

#define INSTRUCTIONS "\
     A1 to reveal A1.\n\
     A1* to flag A1.\n\
     Q to quit game.\n"

void initialize_board();
static void print_board();
void print_minefield();
static void reveal_mines();
static void flag_correct_mines();
static int calculate_mines(int, int);
void place_flag(char, int);
int take_a_guess(char, int);
int get_row(char);
static int reveal_selection(int, int);
static void reveal_around_zero(int, int);

static void print_char_red(char);
static void print_char_blue(char);
static void print_char_yellow(char);
static void print_char_green(char);

#endif /* MINECPER_H */
