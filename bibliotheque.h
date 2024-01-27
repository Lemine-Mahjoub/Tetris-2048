
typedef struct {
    int colonne[10];
} ligne;

typedef struct {
    ligne ligne[15];
} grille;

typedef struct {
    int x;
    int y;
    int nombre;
    int tab[2][2];
} bloc;


void menuPrincipal();
void choixMenuPrincipal(int choix);
void nouvellePartie();
void chargerPartie();
void reglesDuJeu();
void quitter();

int fichierExiste(char nom[50]);
void chargerGrille(char nom[50], grille *g);
void sauvegarderGrille(grille g);

void grilleVide(grille *g);
void generationBloc(bloc *nouveauBloc);
void affichage(grille g, bloc bloc);
void afficherGrille(grille g);
void affichageBloc(bloc bloc);
void affichageCommande();
void jeu(grille *g);


bloc bonBloc(grille g, int i, int j);
int blocAutour(grille g, int x, int y, int pasverif, int compteur);
void deforestageGrille(grille *g, int i, int j);

void placerBloc(grille *g, bloc b);

void conditionVictoire(grille g);
void conditionDefaite(grille g);
void victoire();
void defaite();
