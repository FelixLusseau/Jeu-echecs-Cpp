#pragma once

#include <iostream>
#include <string>

#include "piece.h"
#include "square.h"

using namespace std;

class Echiquier {
  private:
    Piece *echiquier[NBCOL][NBCOL];
    Piece *piecesb[NBCOL];
    Piece *piecesn[NBCOL];
    Piece *pionsb[NBCOL];
    Piece *pionsn[NBCOL];

  public:
    Echiquier();

    ~Echiquier();

    /**
     * @brief Retourne le pointeur vers la pièce depuis un Square.
     *
     * @param pos
     * @return Piece*
     */
    Piece *get_piece(Square pos);

    /**
     * @brief Retourne le pointeur vers la pièce depuis un couple de
     * coordonnées.
     *
     * @param ligne
     * @param colonne
     * @return Piece*
     */
    Piece *get_piece(int ligne, int colonne);

    /**
     * @brief Pose la pièce sur l'échiquer.
     *
     * @param piece
     */
    void pose_piece(Piece *piece);

    /**
     * @brief Déplace la pièce sur l'échiquier et vérifie que le mouvement ne
     * met pas en échec.
     *
     * @param orig
     * @param dest
     * @return true
     * @return false
     */
    bool deplace(Square orig, Square dest);

    /**
     * @brief Met à jour l'échiquier en supprimant le pion pris en passant.
     *
     * @param ligne
     * @param colonne
     */
    void prise_en_passant(int ligne, int colonne);

    /**
     * @brief Demande à l'utilisateur quelle pièce il souhaite promouvoir si un
     * pion arrive à la dernière ligne en face de lui et met à jour l'échiquier
     * et le tableau de pions en conséquence.
     *
     * @param couleur
     * @param pos
     * @return true
     * @return false
     */
    bool promotion(Couleur couleur, Square pos);

    /**
     * @brief Vérifie si une pièce en saute une autre lors de son mouvement.
     *
     * @param orig
     * @param dest
     * @param test_echec
     * @return true
     * @return false
     */
    bool verif_saut(Square &orig, Square &dest, bool test_echec);

    /**
     * @brief Teste l'échec pour la couleur sélectionnée.
     *
     * @param couleur
     * @param test_echec_et_mat
     * @return true
     * @return false
     */
    bool echec(Couleur couleur, bool test_echec_et_mat);

    /**
     * @brief Teste le mat ou le pat pour la couleur sélectionnée.
     *
     * @param couleur
     * @param test_pat
     * @return true
     * @return false
     */
    bool mat_ou_pat(Couleur couleur, bool test_pat);

    /**
     * @brief Affiche l'échiquier à l'écran.
     *
     */
    void affiche() const;

    /**
     * @brief Récupère le nom pgn de la pièce.
     *
     * @param name
     * @param view_pawn
     * @param view_color
     * @return string
     */
    string pgn_piece_name(string name, bool view_pawn, bool view_color) const;

    /**
     * @brief Affiche la grille sous forme canonique.
     *
     * @return string
     */
    string canonical_position();
};