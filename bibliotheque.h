#ifndef bibliotheque_h
#define bibliotheque_h
// ==== Structure de Données ==== //
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

//================================//


// ==== Prototypes ==== //

// ==== Menu Principal ==== //
// Auteur : Sarah Barlatier

void menuPrincipal();
void choixMenuPrincipal(int choix);
void nouvellePartie();
void chargerPartie();
void attenteDebut();


void reglesDuJeu();
void quitter();



// ==== Gestionnaire de Fichier ==== //
// Auteur : Fabrice Gerbaud
int fichierExiste(char nom[50]);
void chargerGrille(char nom[50], grille *g);
void sauvegarderGrille(grille g);




// ==== Jeu ==== //
// Auteur : Lemine Mahjoub


void grilleVide(grille *g);
void generationBloc(bloc *nouveauBloc);

void affichage(grille g, bloc bloc);
void afficherGrille(grille g);
void affichageBloc(bloc bloc);
void affichageCommande();


void placerBloc(grille *g, bloc b);

void commandeUtilisateur(bloc *b, grille *g);
int blocAutour(grille g, int x, int y, int pasverif, int compteur, int valeur);
bloc bonBloc(grille g, int i, int j);
void deforestageGrille(grille *g, int i, int j);
void graviteGrille(grille *g, int x, int y);

void conditionVictoire(grille g);
void victoire();

void conditionDefaite(grille g);
void defaite();


void jeu(grille *g);

#endif 