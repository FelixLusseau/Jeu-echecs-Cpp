#pragma once

#include <iostream>
#include <string>

#include "echiquier.h"
#include "square.h"

using namespace std;

/**
 * @brief Classe codant la gestion du jeu, des règles etc...
 *
 */
class Jeu {
  private:
    Echiquier echiquier;

  public:
    /**
     * @brief Appelle la fonction echec de l'échiquier pour la couleur donnée.
     * Le booléen permet de ne pas montrer les affichages de cette fonction lors
     * de son appel dans mat_ou_pat_ou_egalite.
     *
     * @param couleur
     * @param test_echec_et_mat
     * @return true
     * @return false
     */
    bool test_echec(Couleur couleur, bool test_echec_et_mat);

    /**
     * @brief Appelle la fonction mat_ou_pat_ou_egalite de l'échiquier pour la couleur
     * donnée.
     *
     * @param couleur
     * @return true
     * @return false
     */
    bool test_mat(Couleur couleur);

    /**
     * @brief Appelle la fonction mat_ou_pat_ou_egalite de l'échiquier pour la couleur
     * donnée et lui transmet le compteur de coups sans prise ou déplacement de pion.
     *
     * @param couleur
     * @param compteur
     * @return true
     * @return false
     */
    bool test_pat_ou_egalite(Couleur couleur, int compteur);

    /**
     * @brief Récupère un mouvement syntaxiquement valide depuis le terminal dans le main et
     * contrôle sa validité avant de l'effectuer en faisant appel aux fonctions de l'échiquier.
     *
     * @param couleur
     * @param str_orig
     * @param str_dest
     * @param coup_prec
     * @param prise_ou_pion
     * @return true
     * @return false
     */
    bool execution(Couleur couleur, string str_orig, string str_dest, string coup_prec, bool *prise_ou_pion);

    /**
     * @brief Déplace une pièce sans vérification.
     *
     * @param orig
     * @param dest
     */
    void force_deplace(Square orig, Square dest);

    /**
     * @brief Donne le pointeur vers la pièce à cette case en appelant la
     * fonction get_piece de l'échiquier.
     *
     * @param pos
     * @return Piece*
     */
    Piece *get_piece(Square pos);

    /**
     * @brief Appelle la fonction affiche de l'échiquier
     *
     */
    void affiche() const;

    /**
     * @brief Effectue les vérifications et procède au petit roque.
     *
     * @param couleur
     * @return true
     * @return false
     */
    bool petit_roque(Couleur couleur);

    /**
     * @brief Effectue les vérifications et procède au grand roque.
     *
     * @param couleur
     * @return true
     * @return false
     */
    bool grand_roque(Couleur couleur);

    /**
     * @brief Appelle la fonction canonical_position de l'échiquier.
     *
     * @return string
     */
    string canonical_position();

    /**
     * @brief Affiche le résultat et l'échiquier sous forme canonique.
     *
     * @param couleur
     * @param stop
     * @param pat
     */
    void fin_de_partie(Couleur couleur, bool stop, bool pat);
};
