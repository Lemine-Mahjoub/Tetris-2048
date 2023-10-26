# Projet SAE-1 :

## 1. Objectif : Developper un Jeu tetris 2048 :
- Propose en début de jeu un menu. Ce menu va permettre de choisir de commencer une
nouvelle partie ou de charger une partie en cours. Une partie en cours devra être
stockée dans un fichier texte.
- Représente une grille de Tetris avec 10 colonnes et 15 lignes,
- Fait apparaitre en haut de la grille un nouveau bloc de nombres
- Permet à un joueur de choisir dans quelle colonne placer le nouvel élément. La sélection
de la colonne est laissée libre (utilisation des flèches ou utilisation du numéro de la
colonne),
- Mets à jour la grille avec le nouveau bloc
- Fait les changements en cascade si besoin,
- Permet de déterminer qu’un joueur a gagné (s’il fait appaitre le nombre 2048 dans la
grille),
- Permet de sauvegarder dans un fichier texte une partie en cours.

## 1.1 Extensions Possible
- Gérer les couleurs,
- Ajouter des combinaisons de blocs,
- Changer les dimensions de la grille,
- Etc…

## 2. Contrainte : 
- Le programme doit être écrit dans le langage C,
- Le programme doit s’exécuter en mode console,
- Le jeu sera testé sur une machine tournant avec Windows : si vous la codez sur une
machine sous Linux ou sous Mac alors vous devrez faire très attention à ce point,
- D’une manière générale, un découpage fonctionnel est attendu. Le découpage en
fonctions facilite l’écriture et la compréhension de votre code. Aucune fonction ne devra
dépasser 100 lignes. Un découpage fonctionnel implique souvent la présence de
plusieurs fichiers sources et en-têtes. Des commentaires sont attendus dans votre code.
Chaque fonction sera précédée d’un en-tête que vous prendrez soin de compléter :
```
Fonction : nom de la fonction/procedure
Auteur : nom de la ou des auteurs de la fonction/procédure
Param : signification des paramètres
Traitrement : résumé succint de son traitement
Retour : signification des valeurs retournées
```

## 3. Cahier des Charges et Repartition des Taches :

### 3.1 Cahier des Charges :
- #### Menu Principal (Nouvelle Partie, Charger une Nouvelle Partie)
- #### Reprensenter une grille (10 colonnes et 15 lignes pour le moment)
- #### Faire apparaitre en haut de la grille un nouveau bloc de nombres (avec les nombres corespondant)
- #### Commande pour que le joueur puissent deplacer les blocs (fleches ou nombre de la colonne)
- #### Actualiser la grille et l'ajout et la suppression de chaque colonne et les changements de blocs si besoin
- #### Sauvegarder la partie en cours dans un fichiers texte, et le formatter d'une manière correcte

### 3.2 Repartition des Taches (l, f, s)
- #### Menu Principal (Nouvelle Partie, Charger une Nouvelle Partie) -> (S)
- #### Reprensenter une grille (10 colonnes et 15 lignes pour le moment) -> (F)
- #### Faire apparaitre en haut de la grille un nouveau bloc de nombres (avec les nombres corespondant) -> (L)
- #### Commande pour que le joueur puissent deplacer les blocs (fleches ou nombre de la colonne) -> (S)
- #### Actualiser la grille et l'ajout et la suppression de chaque colonne et les changements de blocs si besoin -> (L)
- #### Sauvegarder la partie en cours dans un fichiers texte, et le formatter d'une manière correcte -> (F)

