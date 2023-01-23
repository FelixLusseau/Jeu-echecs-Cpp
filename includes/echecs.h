#pragma once

#include <iostream>
#include <queue>
#include <string>

#include "couleur.h"
#include "jeu.h"

/**
 * @brief Vérifie si le mouvement est correctement saisi. Ex : a2a4
 *
 * @param cmd
 * @return true
 * @return false
 */
bool saisie_correcte(string const &cmd);

/**
 * @brief Vérifie si la commande du petit roque est correctement saisie.
 *
 * @param cmd
 * @return true
 * @return false
 */
bool saisie_correcte_petitroque(string const &cmd);

/**
 * @brief Vérifie si la commande du grand roque est correctement saisie.
 *
 * @param cmd
 * @return true
 * @return false
 */
bool saisie_correcte_grandroque(string const &cmd);

/**
 * @brief Appelle la fonction grand_roque de la classe Jeu si celui-ci est légal.
 *
 * @param monjeu
 * @param couleur
 * @param roqueb
 * @param roquen
 * @return true
 * @return false
 */
bool grand_roque(Jeu *monjeu, Couleur couleur, bool *roqueb, bool *roquen);

/**
 * @brief Appelle la fonction petit_roque de la classe Jeu si celui-ci est légal.
 *
 * @param monjeu
 * @param couleur
 * @param roqueb
 * @param roquen
 * @return true
 * @return false
 */
bool petit_roque(Jeu *monjeu, Couleur couleur, bool *roqueb, bool *roquen);

/**
 * @brief Gère l'historique des échiquiers successifs sous forme canonique dans une file FIFO afin de détecter
 * une répétition de 3 échiquiers identiques successifs.
 *
 * @param fifo
 * @param monjeu
 * @return true
 * @return false
 */
bool gestion_fifo(queue<string> &fifo, Jeu *monjeu);
