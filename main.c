#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ncurses.h>
#include <time.h>
#include "bibliotheque.h"

void menuPrincipal() {
    
    initscr();
    raw(); 
    keypad(stdscr, TRUE); 
    noecho(); 
    curs_set(0);


    int max_x, max_y;
    getmaxyx(stdscr, max_y, max_x);
    int center_x = (max_x) / 2;
    int center_y = (max_y) / 2;


    attron(A_BOLD);
    mvprintw(max_y/2 - 1, center_x-8, "Bienvenue sur Tetris - 2048");
    attroff(A_BOLD);

    mvprintw(max_y/2 + 20, center_x-18, "Appuyez sur n'importe quelle touche pour continuer...");
    getch();
    clear();

    attron(A_BOLD);
    mvprintw(max_y/2 - 10, center_x-10, "Bienvenue sur Tetris - 2048");
    attroff(A_BOLD);
    mvprintw(max_y/2, center_x-8, "Menu Principal");

    attron(A_REVERSE);
    mvprintw(max_y/2 + 2, center_x-8, "1 - Nouvelle Partie");
    attroff(A_REVERSE);

    mvprintw(max_y/2 + 3, center_x-8, "2 - Charger Partie");
    mvprintw(max_y/2 + 4, center_x-8, "3 - Regles du Jeu");
    mvprintw(max_y/2 + 5, center_x-8, "4 - Quitter");
    
    refresh();


    int choix = getch();
    int index = 0;


    while (choix != '\n') {
        if(choix == KEY_UP) {
            index--;
            if (index < 0) 
                index = 3;
        } else if (choix == KEY_DOWN) {
            index++;
            if (index > 3) 
                index = 0;
        }

        clear();

        
        mvprintw(max_y/2 - 10, center_x-10, "Bienvenue sur Tetris - 2048");
        mvprintw(max_y/2, center_x-8, "Menu Principal");

        char *options[4] = {"Nouvelle Partie", "Charger Partie", "Regles du Jeu", "Quitter"};

        for(int j = 0; j <= 3; j++){
            if (index == j){
                attron(A_REVERSE);
                mvprintw(max_y/2 + 2 + j, center_x-8, "%d - %s", j+1, options[j]);
                attroff(A_REVERSE);
            } else {
                mvprintw(max_y/2 + 2 + j, center_x-8, "%d - %s", j+1, options[j]);
            }
        }

        choix = getch();
        refresh();
    }
    
    choixMenuPrincipal(index);
}


void choixMenuPrincipal(int choix) {
    switch (choix) {
        case 0:
            nouvellePartie();
            break;
        case 1:
            chargerPartie();
            break;
        case 2:
            reglesDuJeu();
            break;
        case 3:
            quitter();
            break;
        default:
            break;
    }
}

void nouvellePartie(){
    clear();
    grille g;

    grilleVide(&g);
    jeu(&g);
}

void chargerPartie(){
    char dossier[50] = "Sauvegarde/";
    char nomFichier[50];

    clear();
    echo(); 
    curs_set(1);

    int max_x, max_y;
    getmaxyx(stdscr, max_y, max_x);

    

    attron(A_BOLD);
    mvprintw(max_y/2, max_x/2 - 8, "Entrez le nom du fichier : ");
    attroff(A_BOLD);

    scanw("%s", nomFichier);
    strcat(dossier, nomFichier);

    clear();
    noecho();
    curs_set(0);
    

    if (fichierExiste(dossier)) {
        grille g;
        chargerGrille(dossier, &g);
        jeu(&g);
    } else {
        clear();
        noecho();
        curs_set(0);

        attron(A_BOLD);
        mvprintw(max_y/2, max_x/2 - 8, "Le fichier n'existe pas\n");
        attroff(A_BOLD);
        
        mvprintw(max_y/2 + 20, max_x/2 -18, "Appuyez sur n'importe quelle touche pour continuer...");
        getch();
        clear();
        menuPrincipal();
    }
}

void reglesDuJeu(){
    clear();

    int max_x, max_y;
    getmaxyx(stdscr, max_y, max_x);

    attron(A_BOLD);
    mvprintw(10, 10, "Regles du Jeu :");
    attroff(A_BOLD);

    mvprintw(12, 10, "Le but du jeu est de faire d'obtenir un nombre avec le nombre 2048");
    mvprintw(13, 10, "Pour cela, vous devez combiner les nombres entre eux, et ceci seront additionner");

    attron(A_BOLD);
    mvprintw(16, 10, "Commandes Utilisateur :");
    attroff(A_BOLD);

    mvprintw(19, 10, "Fleche Bas - Deplacement Bas");
    mvprintw(20, 10, "Fleche Gauche - Deplacement Gauche");
    mvprintw(21, 10, "Fleche Droite - Deplacement Droite");
    mvprintw(22, 10, "Q - Quitter Sans Sauvegarder");
    mvprintw(23, 10, "S - Sauvegarder et Quitter");

    mvprintw(max_y - 10, 10, "Appuyez sur n'importe quelle touche pour continuer...");

    getch();
    clear();
    endwin();
    menuPrincipal();
}

void quitter(){
    clear();
    endwin();
    exit(0);
}

int fichierExiste(char nom[50]) {
    FILE *fichier;
    fichier = fopen(nom, "r");

    if (fichier != NULL) {
        return 1;
    } else {
        return 0;
    }
}

void sauvegarderGrille(grille g) {
    echo();
    curs_set(1);
    char nom[50];
    char path[100] = "Sauvegarde/";
    int max_x, max_y;
    getmaxyx(stdscr, max_y, max_x);

    mvprintw(max_y-3, 10, "Entrez le nom du fichier : ");
    mvscanw(max_y-2, 10, "%s", &nom);

    strcat(path, nom);
    strcat(path, ".txt");

    FILE *fichier;
    fichier = fopen(path, "w");

    if (fichier != NULL) {
        for (int i = 0; i < 15; i++) {
            for (int j = 0; j < 10; j++) {
                fprintf(fichier, "%d,", g.ligne[i].colonne[j]);
            }
        }
    }
}

void chargerGrille(char nom[50], grille *g) {
    FILE *fichier;
    fichier = fopen(nom, "r");
    initscr();
    raw();
    keypad(stdscr, TRUE);
    noecho();
    curs_set(0);


    clear();
    if (fichier != NULL) {
        for(int i = 0; i < 15; i++){
            for(int j = 0; j < 10; j++){
                fscanf(fichier, "%d,", &g->ligne[i].colonne[j]);
            }
        }

    }

    refresh();
    getch();

}

void grilleVide(grille *g){
    for(int i = 0; i < 15; i++){
        for(int j = 0; j < 10; j++){
            g->ligne[i].colonne[j] = 0;
        }
    }
}


void generationBloc(bloc *nouveauBloc){

    srand(time(NULL));

    int tableauValeur[4] = {2, 4, 8, 16};
    int valeur = rand()%4;
    nouveauBloc->nombre = tableauValeur[valeur];

    for(int i = 0; i < 2; i++){
        for (int j = 0; j < 2; j++){
            nouveauBloc->tab[i][j] = 0;
        }
    }

    nouveauBloc->x = 4;
    nouveauBloc->y = 0;

    int forme = rand()%4;
    switch (forme) {
        case 0:
            nouveauBloc->tab[0][0] = tableauValeur[valeur];  // **
            nouveauBloc->tab[0][1] = tableauValeur[valeur];  // *
            nouveauBloc->tab[1][0] = tableauValeur[valeur];
            break;
        case 1:
            nouveauBloc->tab[0][0] = tableauValeur[valeur];  // ** 
            nouveauBloc->tab[0][1] = tableauValeur[valeur];  //  *
            nouveauBloc->tab[1][1] = tableauValeur[valeur];
            break;
        case 2:
            nouveauBloc->tab[0][0] = tableauValeur[valeur];  // *
            nouveauBloc->tab[1][0] = tableauValeur[valeur];  // **
            nouveauBloc->tab[1][1] = tableauValeur[valeur];
            break;
        case 3:
            nouveauBloc->tab[0][1] = tableauValeur[valeur]; //  *
            nouveauBloc->tab[1][0] = tableauValeur[valeur]; // **
            nouveauBloc->tab[1][1] = tableauValeur[valeur];
            break;
        
    }
}

void affichage(grille g, bloc bloc){
    initscr();
    raw();
    keypad(stdscr, TRUE);
    noecho();
    curs_set(0);
    clear();


    affichageBloc(bloc);
    afficherGrille(g);
    affichageCommande();
}

void affichageBloc(bloc bloc){

    mvprintw(5, 10, "Bloc :");

    start_color();
    init_pair(1, COLOR_BLACK, COLOR_WHITE);
    for(int i = 0; i < 2; i++){
        for (int j = 0; j < 2; j++){
            if(bloc.tab[i][j] != 0){
                attron(COLOR_PAIR(1));
                mvprintw(8+i*2, 10+j*6, "x-----x");
                if(bloc.tab[i][j] < 10)
                    mvprintw(8+i*2+1, 10+j*6, "|  %d  |", bloc.tab[i][j]);
                else 
                    mvprintw(8+i*2+1, 10+j*6, "| %d  |", bloc.tab[i][j]);
                mvprintw(8+i*2+2, 10+j*6, "x-----x");
                attroff(COLOR_PAIR(1));
            }

        }
    }
}


void affichageCommande(){
    mvprintw(15, 10, "Commande :");
    mvprintw(17, 10, "Fleche Bas - Deplacement Bas");
    mvprintw(18, 10, "Fleche Gauche - Deplacement Gauche");
    mvprintw(19, 10, "Fleche Droite - Deplacement Droite");
    mvprintw(20, 10, "Q - Quitter Sans Sauvegarder");
    mvprintw(21, 10, "S - Sauvegarder et Quitter");
}

void afficherGrille(grille g){

    int max_x, max_y;
    getmaxyx(stdscr, max_y, max_x);
    int center_x = (max_x) / 2;

    for(int i = 0; i < 10; i++){
        start_color();
        init_pair(10, COLOR_RED, COLOR_BLACK);
        init_pair(1, COLOR_GREEN, COLOR_WHITE);
        init_pair(2, COLOR_YELLOW, COLOR_WHITE);
        init_pair(3, COLOR_BLUE, COLOR_WHITE);
        init_pair(4, COLOR_MAGENTA, COLOR_WHITE);
        init_pair(5, COLOR_CYAN, COLOR_WHITE);
        init_pair(6, COLOR_BLACK, COLOR_WHITE);


        attron(COLOR_PAIR(10));
        mvprintw(2, center_x-25+i*6,"x-----x");
        mvprintw(3, center_x-25+i*6,"|  %d  |", i);
        mvprintw(4, center_x-25+i*6,"x-----x");
        attroff(COLOR_PAIR(10));
        mvprintw(5, center_x-25+i*6,"     ", i);
        mvprintw(6, center_x-25+i*6,"     ");
        
    }
    int k = 10;
    
    for(int i = 0; i < 15; i++){
        for(int j = 0; j < 10; j++){
            int valeur = g.ligne[i].colonne[j];
            if(valeur != 0){
                attron(COLOR_PAIR(valeur % 6 + 1));
            }            
            if (valeur < 10){
                mvprintw(k, center_x-25+j*6,"x-----x");
                mvprintw(k+1, center_x-25+j*6,"|  %i  |", valeur);
                mvprintw(k+2, center_x-25+j*6,"x-----x");
            }
            else if(valeur < 100){
                mvprintw(k, center_x-25+j*6,"x-----x");
                mvprintw(k+1, center_x-25+j*6,"|  %i |", valeur);
                mvprintw(k+2, center_x-25+j*6,"x-----x");
            }
            else if(valeur < 1000){
                mvprintw(k, center_x-25+j*6,"x-----x");
                mvprintw(k+1, center_x-25+j*6,"| %i |", valeur);
                mvprintw(k+2, center_x-25+j*6,"x-----x");
            }
            else{
                mvprintw(k, center_x-25+j*6,"x-----x");
                mvprintw(k+1, center_x-25+j*6,"|%i |", valeur);
                mvprintw(k+2, center_x-25+j*6,"x-----x");
            }
            if(valeur != 0){
                attroff(COLOR_PAIR(valeur % 6 + 1));
            } 
        }
        
        mvprintw(k+10, center_x-25+10*6,"\n");
        k = k + 2;
    }
}



void commandeUtilisateur(bloc *b, grille *g){

    int choix = getch();
    if(b->tab[0][0] != 0)
        g->ligne[b->y].colonne[b->x] = 0;
    if(b->tab[0][1] != 0)
        g->ligne[b->y].colonne[b->x+1] = 0;
    if(b->tab[1][0] != 0)
        g->ligne[b->y+1].colonne[b->x] = 0;
    if(b->tab[1][1] != 0)
        g->ligne[b->y+1].colonne[b->x+1] = 0;
    switch (choix) {


        case KEY_DOWN:
            if(b->y <= 12){
                if(b->tab[1][0] != 0 && b->tab[1][1] != 0 && g->ligne[b->y+2].colonne[b->x] != 0 && g->ligne[b->y+2].colonne[b->x] == 0){
                    b->y = b->y + 1;
                }
                else if(b->tab[1][0] != 0 && (g->ligne[b->y+2].colonne[b->x] == 0 || g->ligne[b->y+1].colonne[b->x+1] == 0)){
                    b->y = b->y + 1;
                }
                else if(b->tab[1][1] != 0 && (g->ligne[b->y+2].colonne[b->x] == 0 || g->ligne[b->y+1].colonne[b->x] == 0)){
                    b->y = b->y + 1;
                }
                
            }
            
            break;
        case KEY_LEFT:
            if(b->x >= 1){
                if(b->tab[0][0] != 0 && b->tab[1][0] != 0 && g->ligne[b->y].colonne[b->x-1] == 0 && g->ligne[b->y+1].colonne[b->x-1] == 0){
                    b->x = b->x - 1;
                }
                else if(b->tab[0][0] != 0 && g->ligne[b->y].colonne[b->x-1] == 0){
                    b->x = b->x - 1;
                }
                else if(b->tab[0][1] != 0 && g->ligne[b->y+1].colonne[b->x-1] == 0){
                    b->x = b->x - 1;
                }
            }
            break;
        case KEY_RIGHT:
            if(b->x < 8){
                if(b->tab[1][0] != 0 && b->tab[1][1] != 0 && g->ligne[b->y].colonne[b->x+2] == 0 && g->ligne[b->y+1].colonne[b->x+2] == 0){
                    b->x = b->x + 1;
                }
                else if(b->tab[1][0] != 0 && g->ligne[b->y].colonne[b->x+2] == 0){
                    b->x = b->x + 1;
                }
                else if(b->tab[1][1] != 0 && g->ligne[b->y+1].colonne[b->x+2] == 0){
                    b->x = b->x + 1;
                }
            }
            break;
        case 'q':
            quitter();
            break;
        case 's':
            sauvegarderGrille(*g);
            quitter();
            break;
        default:
            break;
    }
    
    
}

void changementBloc(grille *g, bloc *b){
    // Les blocs ce transforme, si 4 chiffre de meme valeur sont cote a cote, ils fusionnent, cela supprime tout les nombres du meme chiffre 
    // et les remplace par un nombre superieur tout en bas a gauche et supprime les autres et les met a 0
    // on va verifier pour chaque piece du bloc tant que il y'a un bloc a cote de lui a gauche droite ou en bas on va le transformer  en 0
    for(int i = 0; i < 15; i++){
        for(int j = 0; j < 10; j++){
            if(g->ligne[i].colonne[j] != 0 && i != 14 && j != 9){
                int compteur = blocAutour(*g, i, j, 0, 0);
                int valeur = g->ligne[i].colonne[j]; 
                if(compteur >= 3){
                    bloc b = bonBloc(*g, i, j);
                    int x = b.x;
                    int y = b.y;
                    deforestageGrille(g, x, y);
                    g->ligne[x].colonne[y] = valeur*2;
                }
            }
        }
    }
}


int blocAutour(grille g, int x, int y, int pasverif, int compteur){
    // 1 = haut
    // 2 = bas
    // 3 = gauche
    // 4 = droite
    if(x+1 >= 14 || y+1 >= 9 || x-1 <= 0 || y-1 <= 0 || compteur >= 3)
        return compteur;

    if(pasverif != 1 && g.ligne[x].colonne[y] == g.ligne[x+1].colonne[y])
        blocAutour(g, x+1, y, 2, compteur+1);


    if(pasverif != 2 && g.ligne[x].colonne[y] == g.ligne[x-1].colonne[y])
        blocAutour(g, x-1, y, 1, compteur+1);

    if(pasverif != 3 && g.ligne[x].colonne[y] == g.ligne[x].colonne[y+1])
        blocAutour(g, x, y+1, 4, compteur+1);

    if(pasverif != 4 && g.ligne[x].colonne[y] == g.ligne[x].colonne[y-1])
        blocAutour(g, x, y-1, 3, compteur+1);



    return compteur;


}


bloc bonBloc(grille g, int i, int j){
    // le bon bloc est le bloc coller le plus en bas a gauche ayant les meme valeur
    int x, y;
    x = i;
    y = j;
    while(g.ligne[i].colonne[j] == g.ligne[i+1].colonne[j]){
        i++;
    }
    while(g.ligne[i].colonne[j] == g.ligne[i].colonne[j-1]){
        j--;
    }

    x = i;
    y = j;
    bloc b;
    b.x = i;
    b.y = j;
    return b;
}

void deforestageGrille(grille *g, int i, int j){
    // On est tout en bas a gauche, on souhaite vraiment detruire tout les bloc possible ayant la meme valeur que ce bloc
    // On va donc partir de ce bloc et detruire tout les bloc ayant la meme valeur que ce bloc
    int valeur = g->ligne[i].colonne[j];
    g->ligne[i].colonne[j] = 0;
    if (g->ligne[i].colonne[j+1] == valeur){
        deforestageGrille(g, i, j+1);
    }
    if (g->ligne[i].colonne[j-1] == valeur){
        deforestageGrille(g, i, j-1);
    }
    if (g->ligne[i+1].colonne[j] == valeur){
        deforestageGrille(g, i+1, j);
    }
    if (g->ligne[i-1].colonne[j] == valeur){
        deforestageGrille(g, i-1, j);
    }

}

void conditionVictoire(grille g){
    for(int i = 0; i < 15; i++){
        for(int j = 0; j < 10; j++){
            if(g.ligne[i].colonne[j] == 2048){
                victoire();
            }
        }
    }

}

void conditionDefaite(grille g){
    for(int i = 0; i < 10; i++){
        if(g.ligne[1].colonne[i] != 0){
            defaite();
        }
    }
}

void victoire(){
    clear();
    int max_x, max_y;
    getmaxyx(stdscr, max_y, max_x);
    int center_x = (max_x) / 2;
    int center_y = (max_y) / 2;

    attron(A_BOLD);
    mvprintw(center_y-1, center_x-8, "Vous avez gagne !");
    attroff(A_BOLD);

    mvprintw(max_y-1, 10, "Appuyez sur n'importe quelle touche pour continuer...");
    getch();
    clear();
    endwin();
    menuPrincipal();
}

void defaite(){
    clear();
    int max_x, max_y;
    getmaxyx(stdscr, max_y, max_x);
    int center_x = (max_x) / 2;
    int center_y = (max_y) / 2;

    attron(A_BOLD);
    mvprintw(center_y-1, center_x-8, "Vous avez perdu !");
    attroff(A_BOLD);

    mvprintw(max_y-1, 10, "Appuyez sur n'importe quelle touche pour continuer...");
    getch();
    clear();
    endwin();
    menuPrincipal();
}


int estplacer(grille g, bloc b){
    if(b.y + 2 > 14)
        return 0;
    if(b.tab[1][0] != 0 && b.tab[1][1] != 0 && (g.ligne[b.y+2].colonne[b.x] != 0 || g.ligne[b.y+2].colonne[b.x+1] != 0))
        return 0;
    if (b.tab[1][0] != 0 && b.tab[1][1] == 0 && (g.ligne[b.y+2].colonne[b.x] != 0 || g.ligne[b.y+1].colonne[b.x+1] != 0))
        return 0;
    if (b.tab[1][0] == 0 && b.tab[1][1] != 0 && (g.ligne[b.y+2].colonne[b.x+1] != 0 || g.ligne[b.y+1].colonne[b.x] != 0))
        return 0;

    return 1;
}

void placerBloc(grille *g, bloc b){

    if(g->ligne[b.y].colonne[b.x] == 0)
        g->ligne[b.y].colonne[b.x] = b.tab[0][0];
    if(g->ligne[b.y].colonne[b.x+1] == 0)
        g->ligne[b.y].colonne[b.x+1] = b.tab[0][1];
    if(g->ligne[b.y+1].colonne[b.x] == 0)
        g->ligne[b.y+1].colonne[b.x] = b.tab[1][0];
    if(g->ligne[b.y+1].colonne[b.x+1] == 0)
        g->ligne[b.y+1].colonne[b.x+1] = b.tab[1][1];
}

void jeu(grille *g){

    bloc bloc;
    generationBloc(&bloc); 
    affichage(*g, bloc); 
    while(estplacer(*g, bloc)){ 
        
        commandeUtilisateur(&bloc, g); 
        placerBloc(g, bloc); 
        affichage(*g, bloc); 
    }
    changementBloc(g, &bloc); 
    conditionVictoire(*g); 
    conditionDefaite(*g);

    jeu(g);

}

int main() {
    menuPrincipal();
    return 0;
}


