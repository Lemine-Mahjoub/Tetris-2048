#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ncurses.h>
#include "bibliotheque.h"



//===================================================================================================
/*
    Fonction : GrilleVide
    Auteur : Lemine Mahjoub
    Param : Aucun Paramètre
    Traitements :
        - Initialise la grille a vide
    Retour : Aucun Retour

    typedef struct {
    int *tab[10];
} colonne;

typedef struct {
    colonne *tab[15];
} grille;
*/

void grilleVide(grille *grille) {
    for(int i = 0; i < 15; i++) {
        colonne colonneVide;
        for(int j = 0; j < 10; j++) {
            colonneVide.tab[j] = 0;
        }
        grille->tab[i] = colonneVide;
    }

}


int main() {
    grille grille;
    bloc nouveauBloc;
    initscr();
    grilleVide(&grille);
    generationBloc(&nouveauBloc);
    commandeUtilisateur(&grille, nouveauBloc);
    affichageGrille(grille);
    return 0;
}
//===================================================================================================



//===================================================================================================
/*
    Fonction : GrilleFichier
    Auteur : Lemine Mahjoub
    Param : Aucun Paramètre
    Traitements :
        - Initialise une Grille avec un fichier
    Retour : Aucun Retour
*/

void grilleFichier() {

}



//===================================================================================================
/*
    Fonction : Affichage Grille
    Auteur : Lemine Mahjoub
    Param : Aucun Paramètre
    Traitements :
        - Affichage du tableau representant la grille
    Retour : Aucun Retour
*/

void affichageGrille(grille grille) {
    initscr();

    printw("Affichage Grille\n\n");
    printw("0 1 2 3 4 5 6 7 8 9\n\n\n");
    for(int i = 0; i < 15; i++) {
        
        for(int j = 0; j < 10; j++) {
            printw("%d", grille.tab[i].tab[j]);
            printw(" ");
        }
        printw("\n");
    }
    refresh();
}

//===================================================================================================



//===================================================================================================
/*
    Fonction : ChangementGrille
    Auteur : Lemine Mahjoub
    Param : Aucun Paramètre
    Traitements :
        - Permet de faire des changements sur la grille (ajout de bloc / modification de bloc)
    Retour : Aucun Retour
*/

void changementGrille(grille *grille, bloc bloc, int colonne) {
    
    int ligne = 0;
    while(ligne < 15 && grille->tab[ligne].tab[colonne] == 0) {
        ligne++;
    }
    
    for(int i = 0; i < 3; i++){
        for(int j = 0; j < 3; j++){
            grille->tab[ligne - i - 1].tab[colonne + j] = bloc.tab[i][j];
        }
    }
    
}

//===================================================================================================


//===================================================================================================
/*
    Fonction : commandeUtilisateur
    Auteur : Lemine Mahjoub
    Param : Aucun Paramètre
    Traitements :
        - Permet a l'utilisateur de saisir un nombre entre 1 et 9 pour choisir la grille
        - Permet a l'utilisateur de quitter sans sauvegarder en appuyant sur q ou quitter en sauvegardant en appuyant sur s
    Retour : Aucun Retour
*/

void commandeUtilisateur(grille *grille, bloc bloc) {
    char choixStr;
    initscr();
    printw("Que voulez vous faire ?\n");
    printw("Placer un bloc : 0 1 2 3 4 5 6 7 8 9\n");
    printw("Quitter sans sauvegarder : q\n");
    printw("Quitter en sauvegardant : s\n");
    printw("Votre choix : ");
    scanw("%d", &choixStr);
    refresh();

    switch (choixStr) {
        case 'q':
            printw("Vous avez quitter sans sauvegarder\n");
            break;
        case 's':
            printw("Vous avez quitter en sauvegardant\n");
            break;
        default:
            int choixInt = choixStr;
            printf("%i", choixInt);
            changementGrille(grille, bloc, choixInt+1);
            break;
    }
}

//===================================================================================================



//===================================================================================================
/*
    Fonction : verificationGrille
    Auteur : Lemine Mahjoub
    Param : Aucun Paramètre
    Traitements :
        - Verifie si la grille est correcte
    Retour : Aucun Retour
*/

void verificationBloc() {

}

//===================================================================================================



//===================================================================================================
/*
    Fonction : generationBloc
    Auteur : Lemine Mahjoub
    Param : Aucun Paramètre
    Traitements :
        - Genere un bloc aleatoirement
    Retour : Aucun Retour
*/

#include <stdio.h>
#include <stdlib.h>


void generationBloc(bloc *nouveauBloc) {

    srand(time(NULL));

    int indexAleatoire = rand() % 4;
    int valeurAutoriser[4] = {2, 4, 8, 16};
    int valeur = valeurAutoriser[indexAleatoire];
    int indexAleatoireForme = rand() % 6;

    nouveauBloc->nombre = valeur;

    // Initialiser le tableau avec des zéros
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            nouveauBloc->tab[i][j] = 0;
        }
    }

    switch (indexAleatoireForme) {
        case 0:
            nouveauBloc->tab[1][1] = valeur;
            nouveauBloc->tab[1][2] = valeur;
            nouveauBloc->tab[2][1] = valeur;
            break;
        case 1:
            nouveauBloc->tab[1][0] = valeur;
            nouveauBloc->tab[1][1] = valeur;
            nouveauBloc->tab[2][1] = valeur;
            break;
        case 2:
            nouveauBloc->tab[1][1] = valeur;
            nouveauBloc->tab[2][1] = valeur;
            nouveauBloc->tab[2][2] = valeur;
            break;
        case 3:
            nouveauBloc->tab[1][1] = valeur;
            nouveauBloc->tab[2][1] = valeur;
            nouveauBloc->tab[2][2] = valeur;
            break;
        case 4:
            nouveauBloc->tab[0][1] = valeur;
            nouveauBloc->tab[1][1] = valeur;
            nouveauBloc->tab[2][1] = valeur;
            break;
        case 5:
            nouveauBloc->tab[2][2] = valeur;
            nouveauBloc->tab[2][1] = valeur;
            nouveauBloc->tab[2][0] = valeur;
            break;
    }
}

//===================================================================================================


void affichageBloc(bloc bloc) {
    initscr();

    printw("Affichage Bloc\n\n");
    for(int i = 0; i < 3; i++) {
        
        for(int j = 0; j < 3; j++) {
            printw("%d", bloc.tab[i][j]);
            printw(" ");
        }
        printw("\n");
    }
    refresh();
}


//===================================================================================================
/*
    Fonction : verificationVictoire
    Auteur : Lemine Mahjoub
    Param : Aucun Paramètre
    Traitements :
        - Verifie si un bloc est a 2048
    Retour : Aucun Retour
*/

void verificationVictoire() {

}

//===================================================================================================



//===================================================================================================
/*
    Fonction : verificationDefaite
    Auteur : Lemine Mahjoub
    Param : Aucun Paramètre
    Traitements :
        - Verifie si la grille est pleine
    Retour : Aucun Retour
*/

void verificationDefaite() {

}

//===================================================================================================



//===================================================================================================
/*
    Fonction : Victoire
    Auteur : Lemine Mahjoub
    Param : Aucun Paramètre
    Traitements :
        - Ecran de victoire
    Retour : Aucun Retour
*/

void victoire() {

}

//===================================================================================================



//===================================================================================================

/*
    Fonction : Defaite
    Auteur : Lemine Mahjoub
    Param : Aucun Paramètre
    Traitements :
        - Ecran de defaite
    Retour : Aucun Retour
*/

void defaite() {

}

//===================================================================================================