typedef struct {
    int *tab[10];
} colonne;

typedef struct {
    colonne tab[15];
} grille;

typedef struct {
    int nombre;
    int tab[2][2];
} bloc;


// Menu Principal
void menuPrincipal();
void nouvellePartie();
void chargerPartie();
void quitter();
void reglesDuJeu();

// Gestionnaire fichier
void chargerFichier();
int fichierExiste(char nom[50]);

// Jeu
void grilleVide(grille *grille);
void generationBloc(bloc *nouveauBloc);
void placeBloc(grille *grille, bloc bloc, int colonne);
void affichageBloc(bloc bloc);

