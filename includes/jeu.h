#pragma once

#include <iostream>
#include <string>

#include "echiquier.h"
#include "square.h"

using namespace std;

class Jeu {
  private:
    Echiquier echiquier;

  public:
    bool test_echec(Couleur couleur, bool test_echec_et_mat);
    bool test_mat(Couleur couleur);
    bool test_pat(Couleur couleur);
    bool deplace(Couleur couleur, string str_orig, string str_dest,
                 string coup_prec);
    void force_deplace(Square orig, Square dest);
    Piece *get_piece(Square pos);
    void affiche();
    bool petit_roque(Couleur couleur);
    bool grand_roque(Couleur couleur);
    void fin_de_partie(Couleur couleur, bool stop);
};