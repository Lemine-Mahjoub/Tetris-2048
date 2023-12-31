# Projet SAE-1 : Tetris - 2048

## 1 - Description du projet :

Le projet consiste à réaliser un jeu de Tetris ou 2048 en langage C.
Le jeu doit être jouable en mode console et doit être codé en C.



## 2 - Objectifs :
L’objectiif de ce projet est de coder un jeu du Tetris version 2048 et de permettre à une
personne d’y jouer. Il faut donc écrire un code qui :
- Propose en début de jeu un menu. Ce menu va permettre de choisir de commencer une
nouvelle partie ou de charger une partie en cours. Une partie en cours devra être
stockée dans un fichier texte.
- Représente une grille de Tetris avec 10 colonnes et 15 lignes
- Fait apparaitre en haut de la grille un nouveau bloc de nombres
- Permet à un joueur de choisir dans quelle colonne placer le nouvel élément. La sélection
de la colonne est laissée libre (utilisation des flèches ou utilisation du numéro de la
colonne).
- Mets à jour la grille avec le nouveau bloc
- Fait les changements en cascade si besoin,
- Permet de déterminer qu’un joueur a gagné (s’il fait appaitre le nombre 2048 dans la
grille).
- Permet de sauvegarder dans un fichier texte une partie en cours.

## 3 - Contraintes :
- Le programme doit être écrit dans le langage C.
- Le programme doit s’exécuter en mode console.
- Le jeu sera testé sur une machine tournant avec Windows : si vous la codez sur une
machine sous Linux ou sous Mac alors vous devrez faire très attention à ce point.
- D’une manière générale, un découpage fonctionnel est attendu. Le découpage en
fonctions facilite l’écriture et la compréhension de votre code. Aucune fonction ne devra
dépasser 100 lignes. Un découpage fonctionnel implique souvent la présence de
plusieurs fichiers sources et en-têtes. Des commentaires sont attendus dans votre code.
Chaque fonction sera précédée d’un en-tête que vous prendrez soin de compléter :

//*
Fonction : nom de la fonction
Auteur : nom de l’auteur
Param : signification des paramètres
Traitements : description des traitements effectués par la fonction
Retour : signification de la valeur de retour
*//

## 4 - Extensions :
- Gérer les couleurs,
- Ajouter des combinaisons de blocs,
- Changer les dimensions de la grille,
- etc.

## 5 - Gestion du Projet :

### 5.1 - Organisation du projet :

Le projet tetris - 2048 est organisé en plusieurs parties,
- Le Menu Principal
  - Nouvelle Partie
  - Charger Partie
  - Quitter la partie
- Le Jeu
  - Affichage de la grille
  - Affichage du bloc
  - Déplacement du bloc
  - Gestion des collisions
  - Gestion des combinaisons
  - Gestion de la victoire
  - Gestion de la defaite
  - Sauvegarde de la partie
  - Quitter la partie
- Gestion des fichiers
  - Sauvegarde de la partie
  - Lecture Fichier
  - Ecriture Fichier
  - Replacer les blocs

### 5.2 - Répartition des tâches :

- Menu Principal : **Sarah Barlatier**
- Jeu : **Lemine Mahjoub**
- Gestion des fichiers : **Fabrice Gerbaud**

### 5.3 - Planning :


- 01/12/2023 : Reunification des parties
- 16/01/2024 : Dernier Test, Verification du code et de la documentation
- 30/01/2024 : Rendu Final de la SAE-1 et Presentation Orales