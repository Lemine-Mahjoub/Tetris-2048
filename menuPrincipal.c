#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ncurses.h>
#include "bibliotheque.h"
#include "gestionnaireFichier.c"


//===================================================================================================

/*
    Fonction : Menu Principal
    Auteur : Lemine Mahjoub
    Param : Aucun Paramètre
    Traitements :
        - Affichage du menu principal
        - Choix de l'utilisateur entre les options :
            - Nouvelle Partie
            - Charger Partie
            - Quitter
    Retour : Aucun Retour
*/

void menuPrincipal() {
    
    initscr();
    raw(); 
    keypad(stdscr, TRUE); 
    noecho(); 
    curs_set(0);
    int max_x, max_y;
    getmaxyx(stdscr, max_y, max_x);
    int center_x = (max_x) / 2;
    attron(A_BOLD);
    mvprintw(max_y/2 - 1, center_x-8, "Bienvenue sur Tetris - 2048");
    attroff(A_BOLD);
    mvprintw(max_y/2 + 20, center_x-18, "Appuyez sur n'importe quelle touche pour continuer...");
    getch();
    clear();

    mvprintw(max_y/2 - 1, center_x-8, "Bienvenue sur Tetris - 2048");
    mvprintw(max_y/2, center_x-8, "Menu Principal");
    mvprintw(max_y/2 + 2, center_x-8, "1 - Nouvelle Partie");
    mvprintw(max_y/2 + 3, center_x-8, "2 - Charger Partie");
    mvprintw(max_y/2 + 4, center_x-8, "3 - Regles du Jeu");
    mvprintw(max_y/2 + 5, center_x-8, "4 - Quitter");
    
    refresh();
    int choix = getch();
    int i = 0;
    while (choix != '1' && choix != '2' && choix != '3' && choix != '4' && choix != '\n') {
        if(choix == KEY_UP) {
            i--;
            if (i < 0) {
                i = 3;
            }
        } else if (choix == KEY_DOWN) {
            i++;
            if (i > 3) {
                i = 0;
            }
        }
        clear();

        mvprintw(max_y/2, center_x-8, "Menu Principal");
        mvprintw(max_y/2 - 1, center_x-8, "Bienvenue sur Tetris - 2048");
        if (i == 0) {
            attron(A_REVERSE);
            mvprintw(max_y/2 + 2, center_x-8, "1 - Nouvelle Partie");
            attroff(A_REVERSE);
        } else {
            mvprintw(max_y/2 + 2, center_x-8, "1 - Nouvelle Partie");
        }

        if (i == 1) {
            attron(A_REVERSE);
            mvprintw(max_y/2 + 3, center_x-8, "2 - Charger Partie");
            attroff(A_REVERSE);
        } else {
            mvprintw(max_y/2 + 3, center_x-8, "2 - Charger Partie");
        }

        if (i == 2) {
            attron(A_REVERSE);
            mvprintw(max_y/2 + 4, center_x-8, "3 - Regles du Jeu");
            attroff(A_REVERSE);
        } else {
            mvprintw(max_y/2 + 4, center_x-8, "3 - Regles du Jeu");
        }

        if (i == 3) {
            attron(A_REVERSE);
            mvprintw(max_y/2 + 5, center_x-8, "4 - Quitter");
            attroff(A_REVERSE);
        } else {
            mvprintw(max_y/2 + 5, center_x-8, "4 - Quitter");
        }
        choix = getch();
        refresh();
    }

    if (choix == '1' || (choix == '\n' && i == 0)) {
        nouvellePartie();
    } else if (choix == '2' || (choix == '\n' && i == 1)) {
        chargerPartie();
    } else if (choix == '3' || (choix == '\n' && i == 2)) {
        reglesDuJeu();
    } else if (choix == '4' || (choix == '\n' && i == 3)) {
        quitter();
    } else {
        if (i == 0) {
            nouvellePartie();
        } else if (i == 1) {
            chargerPartie();
        } else if (i == 2) {
            reglesDuJeu();
        } else if (i == 3) {
            quitter();
        }
    }


    endwin();
}

//===================================================================================================



//===================================================================================================

/*
    Fonction : Nouvelle Partie
    Auteur : Lemine Mahjoub
    Param : Aucun Paramètre
    Traitements :
        - Lancement d'une nouvelle partie
    Retour : Aucun Retour
*/

void nouvellePartie() {
    printf("Nouvelle Partie\n");
}
//===================================================================================================



//===================================================================================================
/*
    Fonction : Charger Partie
    Auteur : Lemine Mahjoub
    Param : Aucun Paramètre
    Traitements :
        - Charge une partie a partir d'un fichier
    Retour : Aucun Retour
*/

void chargerPartie() {
    char dossier[50] = "Sauvegarde/";
    char nomFichier[50];
    clear();
    echo(); 
    curs_set(1);
    int max_x, max_y;
    getmaxyx(stdscr, max_y, max_x);

    refresh();
    attron(A_BOLD);
    mvprintw(max_y/2, max_x/2 - 8, "Entrez le nom du fichier : ");
    attroff(A_BOLD);
    scanw("%s", nomFichier);
    strcat(dossier, nomFichier);
    printw("%s\n", dossier);
    if (fichierExiste(dossier)) {
        printf("Le fichier existe\n");
    } else {
        noecho(); 
        curs_set(0);
        clear();
        attron(A_BOLD);
        mvprintw(max_y/2, max_x/2 - 8, "Le fichier n'existe pas\n");
        attroff(A_BOLD);
        
        mvprintw(max_y/2 + 20, max_x/2 -18, "Appuyez sur n'importe quelle touche pour continuer...");
        getch();
        clear();
        menuPrincipal();
    }
    refresh();
}
//===================================================================================================



//===================================================================================================
/*
    Fonction : Quitter
    Auteur : Lemine Mahjoub
    Param : Aucun Paramètre
    Traitements :
        - Quitte le jeu
    Retour : Aucun Retour
*/

void quitter() {
    endwin();
}

//===================================================================================================


void reglesDuJeu(){
    clear();
    
    printw("Regles du Jeu\n");
    printw("Le jeu se joue sur une grille de 4x4 cases. Chaque case possede un numero qui est une puissance de 2.\n");
    printw("A chaque tour, le joueur peut faire glisser les cases vers la gauche, la droite, le haut ou le bas.\n");
    printw("Lorsque deux cases identiques se touchent, elles fusionnent en une seule qui a pour numero la somme des deux numeros de depart.\n");
    printw("Le but du jeu est d'obtenir une case ayant pour numero 2048.\n");
    printw("Si la grille est pleine et qu'aucun mouvement n'est possible, la partie est perdue.\n");
    printw("Bonne chance !\n");

    printw("\n\nAppuyez sur n'importe quelle touche pour revenir au menu principal...");
    getch();
    clear();
    menuPrincipal();
}


int main() {
    menuPrincipal();
    return 0;
}