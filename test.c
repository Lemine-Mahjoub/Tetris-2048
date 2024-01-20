#include <ncurses.h>

int main() {
    initscr(); // initialise ncurses
    raw();    // met ncurses en mode brut
    keypad(stdscr, TRUE); // active le traitement des touches spéciales
    noecho(); // désactive l'affichage des caractères tapés

    start_color(); // initialise les couleurs

    // définition des paires de couleurs
    init_pair(1, COLOR_RED, COLOR_BLACK);
    init_pair(2, COLOR_GREEN, COLOR_BLACK);
    init_pair(3, COLOR_YELLOW, COLOR_BLACK);

    attron(COLOR_PAIR(1)); // active la paire de couleurs 1 (rouge sur noir)
    mvprintw(5, 10, "Couleur rouge");

    attroff(COLOR_PAIR(1)); // désactive la paire de couleurs 1
    attron(COLOR_PAIR(2)); // active la paire de couleurs 2 (vert sur noir)
    mvprintw(6, 10, "Couleur verte");

    attroff(COLOR_PAIR(2)); // désactive la paire de couleurs 2
    attron(COLOR_PAIR(3)); // active la paire de couleurs 3 (jaune sur noir)
    mvprintw(7, 10, "Couleur jaune");

    attroff(COLOR_PAIR(3)); // désactive la paire de couleurs 3

    getch(); // attend une touche pour fermer la fenêtre

    endwin(); // désactive ncurses

    return 0;
}