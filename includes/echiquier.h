#pragma once

// class Echiquier; // forward declaration

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
    /* Piece *promosb[NBCOL];
    int bpromues;
    Piece *promosn[NBCOL];
    int npromues; */

  public:
    Echiquier();

    ~Echiquier();

    Piece *get_piece(Square pos);

    Piece *get_piece(int x, int y);

    void pose_piece(Piece *piece);

    void deplace(Square orig, Square dest);

    void prise_en_passant(int x, int y);

    bool promotion(Couleur couleur, Square pos);

    bool verif_saut(Square &orig, Square &dest, bool test_echec);

    bool echec(Couleur couleur, bool test_echec_et_mat);

    bool mat(Couleur couleur);

    void affiche() const;

    string pgn_piece_name(string name, bool view_pawn, bool view_color) const;

    string canonical_position();
};