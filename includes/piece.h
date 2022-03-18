#pragma once

#include <string>

// class Piece; // forward declaration

#include "couleur.h"
#include "square.h"

#define NBCOL 8

using namespace std;

class Piece {
  protected:
    string nom;
    Couleur couleur;
    Square position;
    bool a_bouge;
    bool prise;

  public:
    Piece(Couleur couleur, string nom, Square position);
    virtual ~Piece();

    string affiche();
    virtual bool est_mouvement_legal(string case_orig, string case_dest) = 0;
    Square get_pos();
    void set_pos(Square pos);
    Couleur get_couleur();
    string to_string();
    virtual string get_type() = 0;
    bool get_a_bouge();
    bool get_prise();
    void set_prise(bool flag);
};

class Tour : public Piece {
  private:
    bool a_bouge;

  public:
    Tour(Couleur couleur, string nom, Square position);
    bool est_mouvement_legal(string case_orig, string case_dest);
    string get_type();
};

class Cavalier : public Piece {

  public:
    Cavalier(Couleur couleur, string nom, Square position);

    bool est_mouvement_legal(string case_orig, string case_dest);
    string get_type();
};

class Fou : public Piece {

  public:
    Fou(Couleur couleur, string nom, Square position);

    bool est_mouvement_legal(string case_orig, string case_dest);
    string get_type();
};

class Dame : public Piece {

  public:
    Dame(Couleur couleur, string nom, Square position);

    bool est_mouvement_legal(string case_orig, string case_dest);
    string get_type();
};

class Roi : public Piece {

  public:
    Roi(Couleur couleur, string nom, Square position);

    bool est_mouvement_legal(string case_orig, string case_dest);
    string get_type();
};

class Pion : public Piece {

  public:
    Pion(Couleur couleur, string nom, Square position);

    bool est_mouvement_legal(string case_orig, string case_dest);
    string get_type();
};