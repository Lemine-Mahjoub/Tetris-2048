#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "bibliotheque.h"



//==================================================================================================
// Fonction Menu Principal :
//==================================================================================================

// Fonction de Sarah :
// - Verification si un fichier texte non vide existe deja correspondants a la partie en cours
// - Si oui, affichage du menu principal avec les options : Nouvelle Partie, Charger Partie, Quitter
// - Si non, affichage du menu principal avec les options : Nouvelle Partie, Quitter
// - Fonction Recuperation partie en cours et affichage grille


//==================================================================================================



//==================================================================================================
// Fonction Affichage et Creation Grille : 
//==================================================================================================

int createtext (char str[])
{
    FILE * f  ;
    /// �crire dans un fichier
    f = fopen ("log.txt", "w") ;
    for (int i=0; i<strlen(str); i++)
    {
        fprintf (f, "%c",str[i]);
    }
    printf("%c",str);
    fclose (f) ;
    return 0 ;
}


void affichegrille(int table[][10])
{
    // Affichage avec une bordure en ASCII
    for (int i = 1; i < 15; i++) {
        // Bord tout en haut + milieu
        for (int j = 0; j < 10; j++)
        {
            printf("%c%c%c%c",(char)206,(char)205,(char)205,(char)205);
        }
        printf("%c\n",(char)206);

        // Valeurs + bords gauche et droit
        for (int j = 0; j < 10; j++)
        {
            if (table[i][j]==0)
            {
                printf("%c   ",(char)186);
            }
            else{
                printf("%c %d ", (char)186, table[i][j]);
            }
        }
        printf("%c\n",(char)186);
    }

    // Bord du bas
    for (int j = 0; j < 10; j++) {
        printf("%c%c%c%c",(char)206,(char)205,(char)205,(char)205);
    }
    printf("%c\n",(char)206);
}

//==================================================================================================



//==================================================================================================
// Fonction Placement Element : 
//==================================================================================================

// Fonction de lemine : 
// - Creation nouveaux element correspondants au bloc
// - Verification si le bloc peut etre place dans la grille
// - Placement random des blocs
// - Verification cas Gagnant et Perdant :