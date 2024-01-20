#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ncurses.h>
#include <time.h>
#include "bibliotheque.h"
#include "gestionnaireFichier.c"


void grilleVide(grille *g){
    for(int i = 0; i < 15; i++){
        for(int j = 0; j < 10; j++){
            g->tab[i].tab[j]= 0;
        }
    }
}

void afficherGrille(grille g){
    initscr();
    raw();
    keypad(stdscr, TRUE);
    noecho();
    curs_set(0);
    int max_x, max_y;
    getmaxyx(stdscr, max_y, max_x);
    int center_x = (max_x) / 2;

    for(int i = 0; i < 10; i++){
        start_color();
        init_pair(1, COLOR_RED, COLOR_BLACK);
        attron(COLOR_PAIR(1));
        mvprintw(2, center_x-25+i*6,"x-----x");
        mvprintw(3, center_x-25+i*6,"|  %d  |", i);
        mvprintw(4, center_x-25+i*6,"x-----x");
        attroff(COLOR_PAIR(1));
        mvprintw(5, center_x-25+i*6,"     ", i);
        mvprintw(6, center_x-25+i*6,"     ");
        
    }
    int k = 7;
    for(int i = 0; i < 15; i++){
        for(int j = 0; j < 10; j++){
            start_color();
            init_pair(1, COLOR_RED, COLOR_BLACK);
            init_pair(2, COLOR_GREEN, COLOR_BLACK);
            init_pair(3, COLOR_YELLOW, COLOR_BLACK);
            init_pair(4, COLOR_BLUE, COLOR_BLACK);
            init_pair(5, COLOR_MAGENTA, COLOR_BLACK);
            init_pair(6, COLOR_CYAN, COLOR_BLACK);

            if (g.tab[i].tab[j] < 10){

                mvprintw(k, center_x-25+j*6,"x-----x");
                mvprintw(k+1, center_x-25+j*6,"|  %i  |", g.tab[i].tab[j]);
                mvprintw(k+2, center_x-25+j*6,"x-----x");
            }
            else if(g.tab[i].tab[j] < 100){
                mvprintw(k, center_x-25+j*6,"x-----x");
                mvprintw(k+1, center_x-25+j*6,"|  %i |", g.tab[i].tab[j]);
                mvprintw(k+2, center_x-25+j*6,"x-----x");
            }
            else if(g.tab[i].tab[j] < 1000){
                mvprintw(k, center_x-25+j*6,"x-----x");
                mvprintw(k+1, center_x-25+j*6,"| %i |", g.tab[i].tab[j]);
                mvprintw(k+2, center_x-25+j*6,"x-----x");
            }
            else{
                mvprintw(k, center_x-25+j*6,"x-----x");
                mvprintw(k+1, center_x-25+j*6,"|%i |", g.tab[i].tab[j]);
                mvprintw(k+2, center_x-25+j*6,"x-----x");
            }
        }
        
        mvprintw(k+10, center_x-25+10*6,"\n");
        k = k + 2;
    }
    getch();
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

void placeBloc(grille *grille, bloc bloc, int colonne) {
    
    int ligne = 0;
    if(colonne == 9) {
        colonne = 8;
    }
    if (bloc.tab[1][0] == 0) {
        while(ligne < 13 && grille->tab[ligne+1].tab[colonne] == 0  && grille->tab[ligne+2].tab[colonne+1] == 0) {
            ligne++;
        }
    } else if (bloc.tab[1][1] == 0) {
        while(ligne < 13 && grille->tab[ligne+2].tab[colonne] == 0  && grille->tab[ligne+1].tab[colonne+1] == 0) {
            ligne++;
        }
    } else {
        while(ligne < 13 && grille->tab[ligne+2].tab[colonne] == 0  && grille->tab[ligne+2].tab[colonne+1] == 0) {
            ligne++;
        }
    }


    for(int i = 0; i < 2; i++) {
        for(int j = 0; j < 2; j++){
            if(bloc.tab[i][j] != 0){
                grille->tab[ligne+i].tab[colonne+j] = bloc.tab[i][j];
            }
            
        }
    }
    
}

void affichageBloc(bloc bloc) {
    initscr();


    for(int i = 0; i < 2; i++) {
        
        for(int j = 0; j < 2; j++) {
            mvprintw(i*4,j*4,"%d", bloc.tab[i][j]);
        
        }
        printw("\n");
    }
    refresh();
    getch();
}

int commandeUtilisateur(){
    initscr();
    clear();
    int commande;

    mvprintw(0, 0, "Commande : ");
    commande = getch();
    clear();
    return commande - '0';
    
}

void transformationBloc(grille *g){
    //  Dès que 3 cases minimum avec le même nombre 
    //se touchent, elle disparaissent pour être remplacées par la puissance de deux suivante : trois 
    //cases ou plus avec un 2 sont remplacées par une case avec un 4, trois cases ou plus avec un 4 
    //sont remplacées par une case avec un 8, etc. La nouvelle case qui va remplacer les ancienne 
    //doit être placée dans la case le plus en bas à gauche possible.
    int valeur = 0;
    for(int i = 0; i < 15; i++){
        for(int j = 0; j < 10; j++){
            if(g->tab[i].tab[j] == g->tab[i].tab[j+1] && g->tab[i].tab[j] == g->tab[i].tab[j+2] && g->tab[i].tab[j] != 0){
                valeur = g->tab[i].tab[j];
                g->tab[i].tab[j] = 0;
                g->tab[i].tab[j+1] = 0;
                g->tab[i].tab[j+2] = 0;
                g->tab[i].tab[j+3] = valeur*2;
            }
        }
    }

}

int main() {
    
    grille g;
    bloc bloc;
    grilleVide(&g);
    for(int i = 0; i < 15; i++){
        generationBloc(&bloc);
        
        int c = commandeUtilisateur();

        placeBloc(&g, bloc, c);
        transformationBloc(&g);
        afficherGrille(g);
    }

    return 0;
}