# Jeu d'échecs en C++ de Félix Lusseau

## Compilation

Pour compiler le jeu, faire `make` dans le répertoire principal. <br>
Pour compiler la documentation avec Doxygen, faire `make doc`. Celle-ci se trouve dans `html/index.html`

## Lancement du jeu

Le binaire produit par la compilation est `echecs` dans le répertoire principal. <br>
Il peut être lancé avec `./echecs` ou en lui fournissant des coups avec par exemple `cat partie.txt | ./echecs`.

## Visuels

Il est recommandé de lancer le jeu dans une fenêtre assez grande afin de voir l'affichage complet.

## Commentaires

L'ensemble des fonctionnalités attendues a été codé. <br>
La classe **Echiquier** contient les fonctions de gestion des pièces, déplacements et échecs. <br>
La classe **Jeu** appelle les fonctions de l'échiquier et gère les règles du jeu. <br>
Le **main** gère le déroulement du jeu, l'alternance des coups, les roques, la vérification de saisie, l'absence de répétition et l'affichage de la fin de partie. <br>
La classe **Piece** contient les attributs et méthodes communs et spécifiques à chaque type de pièce. <br>
La classe **Square** permet de gérer les cases stockées dans les pièces. <br>