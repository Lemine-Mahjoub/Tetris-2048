#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ncurses.h>



//===================================================================================================

/*
    Fonction : Sauvegarder Partie
    Auteur : Lemine Mahjoub
    Param : Aucun Paramètre
    Traitements :
        - Sauvegarde La partie deja en cours
    Retour : Aucun Retour
*/

void sauvegarderPartie() {

}

//===================================================================================================



//===================================================================================================
/*
    Fonction : charger fichier
    Auteur : Lemine Mahjoub
    Param : Aucun Paramètre
    Traitements :
        - charge une grille a partir d'un fichier
    Retour : Aucun Retour
*/

void chargerFichier() {

}

//===================================================================================================



//===================================================================================================
/*
    Fonction : fichier existe
    Auteur : Lemine Mahjoub
    Param : Aucun Paramètre
    Traitements :
        - Verifie si un fichier existe
    Retour : Aucun Retour
*/

int fichierExiste(char nom[50]) {
    FILE *fichier;
    fichier = fopen(nom, "r");

    if (fichier != NULL) {
        return 1;
    } else {
        return 0;
    }
}
//===================================================================================================
