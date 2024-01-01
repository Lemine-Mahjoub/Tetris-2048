#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <ncurses.h>

int main() {
    // Initialize ncurses
    initscr();
    noecho();
    curs_set(0);
    keypad(stdscr, TRUE); // Enable keyboard input

    // Menu items
    char *menu_items[] = {"Nouvelle Partie", "Charger Partie", "Quitter"};
    int n_menu_items = sizeof(menu_items) / sizeof(menu_items[0]);
    int current_row = 0;

    while (1) {
        // Clear screen and print menu
        clear();
        for (int i = 0; i < n_menu_items; ++i) {
            if (i == current_row) {
                attron(A_REVERSE); // Highlight selected item
            }
            mvprintw(i + 1, 1, "%s", menu_items[i]);
            if (i == current_row) {
                attroff(A_REVERSE);
            }
        }

        // User input
        int ch = getch();

        // Keyboard navigation
        switch (ch) {
            case KEY_UP:
                if (current_row > 0) current_row--;
                break;
            case KEY_DOWN:
                if (current_row < n_menu_items - 1) current_row++;
                break;
            case 10: // Enter key
                mvprintw(n_menu_items + 2, 1, "Vous avez choisi '%s'", menu_items[current_row]);
                refresh();
                getch(); // Wait for another key press
                goto end; // Break out of the loop
        }
    }

end:
    endwin(); // End ncurses mode
    return 0;
}