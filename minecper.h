
#ifndef MINECPER_H
#define MINECPER_H

static const char BAD_SELECTION[] = "Invalid selection.\n";

void initialize_board();
static void print_board();
void print_minefield();
static void reveal_mines();
static void flag_correct_mines();
static int calculate_mines(int, int);
int take_a_guess(char, int);
static int reveal_selection(int, int);
static void reveal_around_zero(int, int);

static void print_char_red(char);
static void print_char_blue(char);
static void print_char_yellow(char);
static void print_char_green(char);

#endif /* MINECPER_H */
