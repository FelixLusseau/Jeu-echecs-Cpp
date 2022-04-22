#include "square.h"

Square::Square(string entree) : ligne(entree[1] - '1'), colonne(entree[0] - 'a') {}

Square::Square(int ligne, int colonne) : ligne(ligne), colonne(colonne) {}

string Square::to_string() const {
    char colonne_lettre = colonne + 'a';
    string s;
    s += colonne_lettre;
    s += std::to_string(ligne + 1);
    return s;
}

int Square::get_ligne() const { return ligne; }

int Square::get_colonne() const { return colonne; }