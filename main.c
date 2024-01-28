#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curses.h>
#include <time.h>
#include <unistd.h>
#include "bibliotheque.h"


// ==== Menu Principal ====

// =================================================================== //


/**
* Menu Principal
* @author Sarah Barlatier
* @brief Permet d'afficher un menu principal navigable, puis appelle une fonction pour faire les choix
* @param None
* @return None
*/
void menuPrincipal() {

    // Start Fonction
    initscr();
    raw();
    keypad(stdscr, TRUE);
    noecho();
    curs_set(0);
    // End Fonction


    int max_x, max_y;
    getmaxyx(stdscr, max_y, max_x);
	// Les deux variables suivantes devraient être des globales
    int center_x = (max_x) / 2;
    int center_y = (max_y) / 2;

    // Start Fonction
    attron(A_BOLD);
    mvprintw(max_y/2 - 1, center_x-8, "Bienvenue sur Tetris - 2048");
    attroff(A_BOLD);

    mvprintw(max_y/2 + 20, center_x-18, "Appuyez sur n'importe quelle touche pour continuer...");
    getch();
    clear();
    // End Fonction


	// Tu devrais faire une fonction print_bold(char *texte)
	// qui fait un attron(A_BOLD) puis un printw(texte) puis un
	// attroff(A_BOLD) en utilisant les globales center_x et center_y
    attron(A_BOLD);
    mvprintw(max_y/2 - 10, center_x-10, "Bienvenue sur Tetris - 2048");
    attroff(A_BOLD);
    mvprintw(max_y/2, center_x-8, "Menu Principal");

    attron(A_REVERSE);
    mvprintw(max_y/2 + 2, center_x-8, "1 - Nouvelle Partie"); // Tu devrais faire un tableau de char *menu[4] = {"Nouvelle Partie", "Charger Partie", "Regles du Jeu", "Quitter"};
    attroff(A_REVERSE);

    mvprintw(max_y/2 + 3, center_x-8, "2 - Charger Partie");
    mvprintw(max_y/2 + 4, center_x-8, "3 - Regles du Jeu");
    mvprintw(max_y/2 + 5, center_x-8, "4 - Quitter");

    refresh();


    int choix = getch();
    int index = 0;


    while (choix != '\n') { // Code de boucle trop longue
        // Start Fonction
		if(choix == KEY_UP) {
            index--;
            if (index < 0)
                index = 3;
        } else if (choix == KEY_DOWN) {
            index++;
            if (index > 3)
                index = 0;
        }
        // End Fonction

        clear();


        // Start Fonction print_menu(char *title, char* subtitle,char **options)
        mvprintw(max_y/2 - 10, center_x-10, "Bienvenue sur Tetris - 2048");
        mvprintw(max_y/2, center_x-8, "Menu Principal");

		// bien mais tu utilises deux techniques differentes ca aurait value le coup de le faire aussi en haut
        char *options[4] = {"Nouvelle Partie", "Charger Partie", "Regles du Jeu", "Quitter"};
		// Declares toutes tes variables le plus en haut de leur scope
		// PS : Ca vaut aussi le coup de faire une global const
		for(int j = 0; j <= 3; j++){
            if (index == j){
                attron(A_REVERSE); // Tu devrais faire une fonction print_reverse(char *texte)
                mvprintw(max_y/2 + 2 + j, center_x-8, "%d - %s", j+1, options[j]);
                attroff(A_REVERSE);
            } else {
                mvprintw(max_y/2 + 2 + j, center_x-8, "%d - %s", j+1, options[j]);
            }
        }
		// End Fonction

        choix = getch();
        refresh();
    }

    choixMenuPrincipal(index);
}


/**
* choix menu principal
* @author Sarah Barlatier
* @brief Permet de recuperer un entier choix, et a partir de ce choix lancer une fonction, 1: Nouvelle Partie, 2: Charger Partie, 3: Regles, 4: Quitter
* @param choix --> int : Choix de l'utilisateur
* @return None
*/
void choixMenuPrincipal(int choix) {

	// Ca c'est un tableau de pointeurs de fonctions ( ca scale mieux que les switchs )
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


/**
* Nouvelle Partie
* @author : Sarah Barlatier
* @brief Permet de lancer une nouvelle partie, en creant une grille vide, puis en lancant la fonction jeu
* @param  None
* @return Aucun
*/
void nouvellePartie(){

    clear();
    grille g;
    attenteDebut();
    grilleVide(&g);
    jeu(&g);
}


/**
* Charger Partie
* @author : Sarah Barlatier
* @brief Permet de lancer une charger partie, en verifiant d'abord si le fichier existe, puis initialisant le fichier dans une grille, puis en lancant la fonction jeu
* @param  None
* @return Aucun
*/
void chargerPartie(){
    /*
    * Char
    * @auteur : Sarah Barlatier
    * @traitement : Permet d'afficher un menu principal navigable, puis appelle une fonction pour faire les choix
    * @parametre : None
    * @retour : None
    */
    char dossier[50] = "Sauvegarde/"; // 50 ???
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
        grille g; // ca doit etre allouer dynamiquement ca
        chargerGrille(dossier, &g);
        attenteDebut();
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

/**
* Attente Debut
* @author : Sarah Barlatier
* @brief Permet d'attendre 3 secondes, avant de lancer une partie
* @param  None
* @return Aucun
*/
void attenteDebut(){
    clear();
    int max_x, max_y;
    getmaxyx(stdscr, max_y, max_x);
    int center_x = (max_x) / 2;
    int center_y = (max_y) / 2;
    for(int i = 3; i > 0; i--){
        clear();
        attron(A_BOLD);
        mvprintw(center_y, center_x, "%d", i);
        attroff(A_BOLD);
        refresh();
        sleep(1);
    }
}


/**
* Regles du Jeu
* @author : Sarah Barlatier
* @brief Permet de lancer une nouvelle partie, en creant une grille vide, puis en lancant la fonction jeu
* @param  None
* @return Aucun
*/
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


/**
* Quitter
* @author : Sarah Barlatier
* @brief Permet de quiter le jeu
* @param  None
* @return Aucun
*/
void quitter(){
    clear();
    endwin();
    exit(0);
}

// =================================================================== //


// ==== Gestionnaire Fichier ==== //

/**
* fichier existe ?
* @author : Fabrice Gerbaud
* @brief Permet verifier si un fichier existe a l'aide d'un nom de fichier
* @param  nom > char : Nom du fichier
* @return int : 1 si le fichier existe, 0 sinon
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


/**
* charger grille
* @author : Fabrice Gerbaud
* @brief Permet de remplir une grille a l'aide d'un fichier
* @param  nom > char : Nom du fichier,
* @param  g > grille : Grille a remplir
* @return None
*/
void chargerGrille(char nom[50], grille *g) {
    FILE *fichier;
    fichier = fopen(nom, "r");
	//Check si le fichier est bien ouvert ici et gestion erreur
    initscr();
    raw();
    keypad(stdscr, TRUE);
    noecho();
    curs_set(0);


    clear();
    if (fichier != NULL) {
        for(int i = 0; i < 15; i++){ // 15 devrais etre une global pour ajuster la taille de la grille (scalling)
            for(int j = 0; j < 10; j++){ // 10 pareil
                fscanf(fichier, "%d,", &g->ligne[i].colonne[j]);
            }
        }

    }

    refresh();
    getch();

}
/**
* Sauvegarder Grille
* @author : Fabrice Gerbaud
* @brief Permet de Sauvegarder une grille dans un fichier, attention : on ajoute de base l'extension txt a la fin de ce fichier
* @param  g > grille : grille de valeur a sauvegarder
* @return None
*/
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

// =================================================================== //




// ==== Jeu ==== //

// =================================================================== //

/**
* Grille Vide
* @author : Lemine Mahjoub
* @brief Permet de remplir une grille de 0
* @param  *g > grille : grille a remplir
* @return None
*/
void grilleVide(grille *g){
    for(int i = 0; i < 15; i++){
        for(int j = 0; j < 10; j++){
            g->ligne[i].colonne[j] = 0;
        }
    }
}

/**
* Generation Bloc
* @author : Lemine Mahjoub
* @brief Permet de creer un nouveau bloc aleatoire avec des valeurs initialiser a 2, 4, 8 ou 16 et une forme aleatoire
* @param  *nouveauBloc > bloc : bloc aleatoire
* @return None
*/
void generationBloc(bloc *nouveauBloc){

    srand(time(NULL)); // Faire une fonction init_rand() qui est appeler une fois au debut du programme pour la verbosite

	// Start Fonction new_bloc(bloc *bloc)
    int tableauValeur[4] = {2, 4, 8, 16};
    int valeur = rand()%4;
    nouveauBloc->nombre = tableauValeur[valeur];


    for(int i = 0; i < 2; i++){ // Fonction init_bloc(bloc *bloc)
        for (int j = 0; j < 2; j++){
            nouveauBloc->tab[i][j] = 0;
        }
    }

    nouveauBloc->x = 4;
    nouveauBloc->y = 0;
	// End Fonction
	// Start Fonction forme_bloc(bloc *bloc)
    int forme = rand()%4;
    switch (forme) { // Tableau de pointeurs de fonctions avec les shapes (ca scale mieux que les switchs)
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
	// End Fonction
}

/**
* estplacer
* @author : Lemine Mahjoub
* @brief  Permet de verifier si un bloc est placer dans la grille
* @param  g > grille : grille
* @param  bloc > bloc : bloc
* @return int : 1 si le bloc est placer, 0 sinon
*/
int estplacer(grille g, bloc b){

	// Incomprensible, il faut du code plus verbeux
	// Pour le style tu peux faire un tableau de conditions et tu boucles dessus

	/*
	Bien sur il faut faire des jolies conditions verbeuse (avec des noms de fonctions de conditions bien explicite)
	bool conditions[] = {
		(b.y + 2 > 14),
		(b.tab[1][0] != 0 && b.tab[1][1] != 0 && (g.ligne[b.y+2].colonne[b.x] != 0 || g.ligne[b.y+2].colonne[b.x+1] != 0)),
		(b.tab[1][0] != 0 && b.tab[1][1] == 0 && (g.ligne[b.y+2].colonne[b.x] != 0 || g.ligne[b.y+1].colonne[b.x+1] != 0)),
		(b.tab[1][0] == 0 && b.tab[1][1] != 0 && (g.ligne[b.y+2].colonne[b.x+1] != 0 || g.ligne[b.y+1].colonne[b.x] != 0))
	}

	for(int i = 0; i < 4; i++){
		if(conditions[i])
			return 0;
	}
	return 1;
	*/

    if(b.y + 2 > 14)
        return 0;
    if(b.tab[1][0] != 0 && b.tab[1][1] != 0 && (g.ligne[b.y+2].colonne[b.x] != 0 || g.ligne[b.y+2].colonne[b.x+1] != 0)) // Fonction pour tes conditions
        return 0;
    if (b.tab[1][0] != 0 && b.tab[1][1] == 0 && (g.ligne[b.y+2].colonne[b.x] != 0 || g.ligne[b.y+1].colonne[b.x+1] != 0))
        return 0;
    if (b.tab[1][0] == 0 && b.tab[1][1] != 0 && (g.ligne[b.y+2].colonne[b.x+1] != 0 || g.ligne[b.y+1].colonne[b.x] != 0))
        return 0;
    return 1;
}

/**
* Affichage
* @author : Lemine Mahjoub
* @brief Appelle les fonctions d'affichage de la grille, du bloc et des commandes
* @param  g > grille : grille a afficher
* @param  bloc > bloc : bloc a afficher
* @return None
*/
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


/**
* Affichage Bloc
* @author : Lemine Mahjoub
* @brief Permet d'afficher un bloc a l'ecran
* @param  bloc > bloc : bloc a afficher
* @return None
*/
void affichageBloc(bloc bloc){

    mvprintw(5, 10, "Bloc :");

    start_color();
    init_pair(1, COLOR_BLACK, COLOR_WHITE);
    for(int i = 0; i < 2; i++){
        for (int j = 0; j < 2; j++){
            if(bloc.tab[i][j] != 0){
                start_color();
				// Start Fonction
                init_pair(1, COLOR_WHITE, COLOR_GREEN);
                init_pair(2, COLOR_WHITE, COLOR_YELLOW);
                init_pair(3, COLOR_WHITE, COLOR_BLUE);
                init_pair(4, COLOR_WHITE, COLOR_MAGENTA);
				// End Fonction

                int valeur = bloc.nombre;
                // Start Fonction
				// Tableau de pointeurs de fonctions avec les couleurs (ca scale mieux que les switchs)
				if(valeur == 2){
                    attron(COLOR_PAIR(1));
                }
                if (valeur == 4){
                    attron(COLOR_PAIR(2));
                }
                if (valeur == 8){
                    attron(COLOR_PAIR(3));
                }
                if (valeur == 16){
                    attron(COLOR_PAIR(4));
                }
				// End Fonction
				// Start Fonction
                mvprintw(8+i*2, 10+j*6, "x-----x");
                if(bloc.tab[i][j] < 10)
                    mvprintw(8+i*2+1, 10+j*6, "|  %d  |", bloc.tab[i][j]);
                else
                    mvprintw(8+i*2+1, 10+j*6, "| %d  |", bloc.tab[i][j]);
                mvprintw(8+i*2+2, 10+j*6, "x-----x");
				// End Fonction
				// C'est le meme code que plus haut ???
                attroff(COLOR_PAIR(1));
                if(valeur == 2){
                    attron(COLOR_PAIR(1));
                }
                if (valeur == 4){
                    attron(COLOR_PAIR(2));
                }
                if (valeur == 8){
                    attron(COLOR_PAIR(3));
                }
                if (valeur == 16){
                    attron(COLOR_PAIR(4));
                }
            }
        }
    }
}

/**
* Affichage Commande
* @author : Lemine Mahjoub
* @brief Permet d'afficher les commandes a l'ecran
* @param  None
* @return None
*/
void affichageCommande(){
	// Good
	// DEFINE pour les positions

    mvprintw(15, 10, "Commande :");
    mvprintw(17, 10, "Fleche Bas - Deplacement Bas");
    mvprintw(18, 10, "Fleche Gauche - Deplacement Gauche");
    mvprintw(19, 10, "Fleche Droite - Deplacement Droite");
    mvprintw(20, 10, "Q - Quitter Sans Sauvegarder");
    mvprintw(21, 10, "S - Sauvegarder et Quitter");
}


/**
* Affichage Grille
* @author : Lemine Mahjoub
* @brief Permet d'afficher la grile a l'ecran
* @param  g > grille : grille a afficher
* @return None
*/
void afficherGrille(grille g){

	// Impossible a faire scale, la fonction est bcp trop grosse
    int max_x, max_y;
    getmaxyx(stdscr, max_y, max_x);
    int center_x = (max_x) / 2; // Tout l'interet de l'avoir en global
    for(int i = 0; i < 10; i++){ // Fonction afficher_grille(grille *g)
        start_color();
        init_pair(10, COLOR_RED, COLOR_BLACK);
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
            start_color();
            init_pair(1, COLOR_WHITE, COLOR_GREEN);
            init_pair(2, COLOR_WHITE, COLOR_YELLOW);
            init_pair(3, COLOR_WHITE, COLOR_BLUE);
            init_pair(4, COLOR_WHITE, COLOR_MAGENTA);
            init_pair(5, COLOR_WHITE, COLOR_CYAN);
            init_pair(6, COLOR_WHITE, COLOR_WHITE);
			// Tu init les memes paires de couleurs plusieurs fois dans le prg (ca scale pas), c'est un soucis de perf en plus
			// Il faut les init une fois au debut du programme
			// Les stocker dans une global
			// Faire des defines sur les pairs de couleurs
			/*
				#DEFINE WHITE_PAIR 1
				#DEFINE GREEN_PAIR 2
				etc etc
			*/
			// Start Fonction couleur_bloc(int valeur)
			/*
				bool colors[] = {
					(valeur == 2 || valeur == 64),
					(valeur == 4 || valeur == 128),
					(valeur == 8 || valeur == 256),
					(valeur == 16 || valeur == 512),
					(valeur == 32 || valeur == 1024),
					(valeur == 2048)
				}
				for (int i = 0; i < 6; i++){
					if(colors[i])
						attron(COLOR_PAIR(i+1));
				}

			*/
            if(valeur == 2 || valeur == 64)
                attron(COLOR_PAIR(1));
            if (valeur == 4 || valeur == 128)
                attron(COLOR_PAIR(2));
            if (valeur == 8 || valeur == 256)
                attron(COLOR_PAIR(3));
            if (valeur == 16 || valeur == 512)
                attron(COLOR_PAIR(4));
            if (valeur == 32 || valeur == 1024)
                attron(COLOR_PAIR(5));
            if(valeur == 2048)
                attron(COLOR_PAIR(6));
			// End Fonction
			// Start Fonction afficher_bloc(int valeur)
            mvprintw(k, center_x-25+j*6,"x-----x");
            if (valeur < 10)
                mvprintw(k+1, center_x-25+j*6,"|  %i  |", valeur);
            else if(valeur < 100)
                mvprintw(k+1, center_x-25+j*6,"|  %i |", valeur);
            else if(valeur < 1000)
                mvprintw(k+1, center_x-25+j*6,"| %i |", valeur);
            else
                mvprintw(k+1, center_x-25+j*6,"|%i |", valeur);
            mvprintw(k+2, center_x-25+j*6,"x-----x");
			// End Fonction
			// Meme code qu'en haut
            if(valeur == 2 || valeur == 64)
                attroff(COLOR_PAIR(1));
            if (valeur == 4 || valeur == 128)
                attroff(COLOR_PAIR(2));
            if (valeur == 8 || valeur == 256)
                attroff(COLOR_PAIR(3));
            if (valeur == 16 || valeur == 512)
                attroff(COLOR_PAIR(4));
            if (valeur == 32 || valeur == 1024)
                attroff(COLOR_PAIR(5));
            if(valeur == 2048)
                attroff(COLOR_PAIR(6));
        }
        mvprintw(k+10, center_x-25+10*6,"\n");
        k = k + 2;
    }
}


/**
* Commande Utilisateur
* @author : Lemine Mahjoub
* @brief Permet de recuperer les commandes utilisateur et de bouger le bloc en fonction de ces commandes, si le temps (initialiser a 1 seconde) est depasse, le bloc descend d'une case
* @param  *b > bloc : bloc a bouger
* @param  *g > grille : grille a modifier
* @return None
*/
void commandeUtilisateur(bloc *b, grille *g){ // Ho no , Ho no, Ho no no no no no no,  pas toi zizou, pas apres tout ce que tu as fait


    if(b->tab[0][0] != 0)
        g->ligne[b->y].colonne[b->x] = 0;
    if(b->tab[0][1] != 0)
        g->ligne[b->y].colonne[b->x+1] = 0;
    if(b->tab[1][0] != 0)
        g->ligne[b->y+1].colonne[b->x] = 0;
    if(b->tab[1][1] != 0)
        g->ligne[b->y+1].colonne[b->x+1] = 0;

    time_t debut, maintenant;
    time(&debut);
    timeout(1000);
    nodelay(stdscr, TRUE);
    int choix = getch();
    while(choix == ERR && difftime(time(&maintenant), debut) < 1){
        choix = getch();
    }

    nodelay(stdscr, FALSE);
    if(choix == ERR ){
		// Verbositer des conditions a ameliorer absolument, ca ne scale pas dans le temps ce genre de truc
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
        return;
    }
    switch (choix) { // ABOMINATION !!!
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
                if(b->tab[0][0] != 0 && b->tab[1][0] != 0 && g->ligne[b->y].colonne[b->x-1] == 0 && g->ligne[b->y+1].colonne[b->x-1] == 0 ){
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
                if(b->tab[1][0] != 0 && b->tab[1][1] != 0 && g->ligne[b->y].colonne[b->x+1] == 0 && g->ligne[b->y+1].colonne[b->x+1] == 0){
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

/**
* Placer Bloc
* @author : Lemine Mahjoub
* @brief Permet de placer un bloc dans la grille
* @param  b > bloc : bloc a bouger
* @param  *g > grille : grille a modifier
* @return None
*/
void placerBloc(grille *g, bloc b){
	// Il a l'air de manquer la gestion des erreur ici,
	// que se passe t'il si le bloc ne peut pas etre placer ?
    if(g->ligne[b.y].colonne[b.x] == 0)
        g->ligne[b.y].colonne[b.x] = b.tab[0][0];
    if(g->ligne[b.y].colonne[b.x+1] == 0)
        g->ligne[b.y].colonne[b.x+1] = b.tab[0][1];
    if(g->ligne[b.y+1].colonne[b.x] == 0)
        g->ligne[b.y+1].colonne[b.x] = b.tab[1][0];
    if(g->ligne[b.y+1].colonne[b.x+1] == 0)
        g->ligne[b.y+1].colonne[b.x+1] = b.tab[1][1];
}

/**
* Changement Bloc
* @author : Lemine Mahjoub
* @brief Permet de verifier si au moins 4 bloc de meme valeurs ce touche, si c'est le cas, on fusionne les blocs en un seul bloc de multiplier par 2 que l'on place tout en bas a gauche possible, puis on applique une graviter pour le faire tomber le plus bas possible
* @param  *b > bloc : bloc a bouger
* @param  *g > grille : grille a modifier
* @return None
*/
void changementBloc(grille *g, bloc *b){
    for(int i = 0; i < 15; i++){
        for(int j = 0; j < 10; j++){
			// Start Fonction
            if(g->ligne[i].colonne[j] != 0 && i != 14 && j != 9){
				// Start Fonction
                int valeur = g->ligne[i].colonne[j];
                int compteur = 1 + blocAutour(*g, i, j, 0, 0, valeur);

                if(compteur >= 4){
                    bloc b = bonBloc(*g, i, j);
                    int x = b.x;
                    int y = b.y;
                    deforestageGrille(g, x, y);
                    g->ligne[x].colonne[y] = valeur*2;
                    graviteGrille(g, x, y);
                }
				// End Fonction
            }
			// End Fonction
        }
    }
}


/**
* Bloc Autour
* @author : Lemine Mahjoub
* @brief Permet de calculer recursivement le nombre de bloc autour d'un bloc
* @param  g > grille : grille
* @param  x > int : position x du bloc
* @param  y > int : position y du bloc
* @param  pasverif > int : permet de verifier si on est deja passer par cette case, 0: non, 1: gauche, 2: droite, 3: haut, 4: bas
* @param  compteur > int : compteur de bloc similaire
* @param  valeur > int : valeur du bloc
* @return int : nombre de bloc similaire a coter
*/
int blocAutour(grille g, int x, int y, int pasverif, int compteur, int valeur){
    if(compteur >= 4)
        return compteur;
    if (x > 14 || y > 9 || x < 0 || y < 0 || g.ligne[x].colonne[y] != valeur)
        return 0;
    if(pasverif == 1)
        return blocAutour(g, x-1, y, 1, compteur+1, valeur) + blocAutour(g, x, y-1, 3, compteur+1, valeur) + blocAutour(g, x, y+1, 4, compteur+1, valeur);
    else if(pasverif == 2)
        return blocAutour(g, x+1, y, 2, compteur+1, valeur) + blocAutour(g, x, y-1, 3, compteur+1, valeur) + blocAutour(g, x, y+1, 4, compteur+1, valeur);
    else if(pasverif == 3)
        return blocAutour(g, x-1, y, 1, compteur+1, valeur) + blocAutour(g, x+1, y, 2, compteur+1, valeur) + blocAutour(g, x, y-1, 3, compteur+1, valeur);
    else if(pasverif == 4)
        return blocAutour(g, x-1, y, 1, compteur+1, valeur) + blocAutour(g, x+1, y, 2, compteur+1, valeur) + blocAutour(g, x, y+1, 4, compteur+1, valeur);
    else
        return blocAutour(g, x-1, y, 1, compteur+1, valeur) + blocAutour(g, x+1, y, 2, compteur+1, valeur) + blocAutour(g, x, y-1, 3, compteur+1, valeur) + blocAutour(g, x, y+1, 4, compteur+1, valeur);
}


/**
* Gravite Grille
* @author : Lemine Mahjoub
* @brief Permet de faire tomber un bloc le plus bas possible
* @param  *g > grille : grille a modifier
* @param  x > int : position x du bloc
* @param  y > int : position y du bloc
* @return None
*/
void graviteGrille(grille *g, int x, int y){
    if(g->ligne[x+1].colonne[y] == 0){
        g->ligne[x+1].colonne[y] = g->ligne[x].colonne[y];
        g->ligne[x].colonne[y] = 0;
        graviteGrille(g, x+1, y);
    }
}


/**
* Bon Bloc
* @author : Lemine Mahjoub
* @brief Permet de donner les cocordonnees du bloc le plus en bas a gauche possible
* @param  g > grille : grille
* @param  x > int : position x du bloc
* @param  y > int : position y du bloc
* @return bloc -> bloc le plus en bas a gauche possible
*/
bloc bonBloc(grille g, int i, int j){
    int x, y;
    x = i;
    y = j;
    while(g.ligne[i].colonne[j] == g.ligne[i].colonne[j-1] || g.ligne[i].colonne[j] == g.ligne[i+1].colonne[j]){
        while(g.ligne[i].colonne[j] == g.ligne[i+1].colonne[j]){
            i++;
        }
        while(g.ligne[i].colonne[j] == g.ligne[i].colonne[j-1]){
            j--;
        }
    }
    bloc b;
    b.x = i;
    b.y = j;
    return b;
}

/**
* deforestage Grille
* @author : Lemine Mahjoub
* @brief Permet de detruire tout les bloc ayant la meme valeur que le bloc en parametre et etant a coter de ce bloc recursivement
* @param  *g > grille : grille a modifier
* @param  i > int : position x du bloc
* @param  j > int : position y du bloc
* @return None
*/
void deforestageGrille(grille *g, int i, int j){
    // On est tout en bas a gauche, on souhaite vraiment detruire tout les bloc possible ayant la meme valeur que ce bloc
    // On va donc partir de ce bloc et detruire tout les bloc ayant la meme valeur que ce bloc
    int valeur = g->ligne[i].colonne[j];
    g->ligne[i].colonne[j] = 0;
    if(i < 0 || j < 0 || i > 14 || j > 9)
        return;
    if (g->ligne[i].colonne[j+1] == valeur)
        deforestageGrille(g, i, j+1);
    if (g->ligne[i].colonne[j-1] == valeur)
        deforestageGrille(g, i, j-1);
    if (g->ligne[i+1].colonne[j] == valeur)
        deforestageGrille(g, i+1, j);
    if (g->ligne[i-1].colonne[j] == valeur)
        deforestageGrille(g, i-1, j);
}

/**
* condition Victoire
* @author : Lemine Mahjoub
* @brief Permet de verifier si un bloc de valeur 2048 existe, si oui, on lance la fonction victoire
* @param  g > grille : grille
* @return None
*/
void conditionVictoire(grille g){
    for(int i = 0; i < 15; i++){
        for(int j = 0; j < 10; j++){
            if(g.ligne[i].colonne[j] == 2048){
                victoire();
            }
        }
    }
}

/**
* condition Defaite
* @author : Lemine Mahjoub
* @brief Permet de verifier si un bloc ne peut plus descendre, si oui, on lance la fonction defaite
* @param  g > grille : grille
* @return None
*/
void conditionDefaite(grille g){
    for(int i = 0; i < 10; i++){
        if(g.ligne[2].colonne[i] != 0){
            defaite();
        }
    }
}

/**
* Victoire
* @author : Lemine Mahjoub
* @brief Affiche un ecran de victoire, puis lance le menu principal
* @param  g > grille : grille
* @return None
*/
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

/**
* Defaite
* @author : Lemine Mahjoub
* @brief Affiche un ecran de defaite, puis lance le menu principal
* @param  g > grille : grille
* @return None
*/
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

/**
* jeu
* @author : Lemine Mahjoub
* @brief Permet de lancer une partie, en creant une grille vide, puis en lancant la fonction jeu, qui vas generer un bloc aleatoire, l'afficher, puis recuperer les commandes utilisateur, placer le bloc, verifier si il est placer, si oui, on recommence, sinon, on change de bloc, on verifie si on a perdu ou gagner, puis on recommence recursivement
* @param  *g > grille : grille  du jeu
* @return None
*/
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
    conditionDefaite(*g);
    conditionVictoire(*g);
    jeu(g);
}

// =================================================================== //

/**
* main
* @author : Lemine Mahjoub
* @brief Lance le menu principal
* @param  None
* @return int : 0
*/
int main() {
    menuPrincipal();
    return 0;
}


