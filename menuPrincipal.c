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
    int choix = 0;
    initscr();
    printw("Bienvenue sur Tetris - 2048\n");
    printw("1. Nouvelle Partie\n");
    printw("2. Charger Partie\n");
    printw("3. Quitter\n");
    printw("Choix : ");
    refresh();
    scanw("%d", &choix);
    
    switch (choix) {
        case 1:
            nouvellePartie();
            break;
        case 2:
            chargerPartie();
            break;
        case 3:
            quitter();
            break;
        default:
            clear();
            printw("Choix Invalide, Merci de bien vouloir reesayer\n\n\n");
            menuPrincipal();
    }
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
    refresh();
    printw("Charger Partie\n\n");
    printw("Merci de bien vouloir entrer le nom du fichier a charger : ");
    scanw("%s", nomFichier);
    strcat(dossier, nomFichier);
    printw("%s\n", dossier);
    if (fichierExiste(dossier)) {
        printw("Le fichier existe\n");
    } else {
        clear();
        printw("Le fichier choisis n'existe pas, Merci de bien vouloir reesayer\n\n\n");
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
    printf("Quitter\n");
    endwin();
}

//===================================================================================================



int main() {
    menuPrincipal();
    return 0;
}