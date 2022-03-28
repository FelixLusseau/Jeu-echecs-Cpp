#include "piece.h"

Piece::Piece(Couleur couleur, string nom, Square position)
    : nom(nom), couleur(couleur), position(position), a_bouge(false),
      prise(false) {}
Piece::~Piece() {}

string Piece::affiche() { return nom; }

Square Piece::get_pos() { return position; }

void Piece::set_pos(Square pos, bool test_mat) {
    position = pos;
    if (!test_mat)
        a_bouge = true;
}

Couleur Piece::get_couleur() { return couleur; }

string Piece::to_string() { return nom; }

bool Piece::get_a_bouge() { return a_bouge; }

bool Piece::get_prise() { return prise; }

void Piece::set_prise(bool flag) { prise = flag; }

// ---------------------------------------------------------------------------

Tour::Tour(Couleur couleur, string nom, Square position)
    : Piece(couleur, nom, position) {}

bool Tour::est_mouvement_legal(string case_orig, string case_dest) {
    if (case_orig[0] == case_dest[0]) {
        return true;
    } else if (case_orig[1] == case_dest[1]) {
        return true;
    } else
        return false;
}

string Tour::get_type() { return "Tour"; }

// ---------------------------------------------------------------------------

Cavalier::Cavalier(Couleur couleur, string nom, Square position)
    : Piece(couleur, nom, position) {}

bool Cavalier::est_mouvement_legal(string case_orig, string case_dest) {
    if ((case_orig[1] == case_dest[1] + 2 &&
         case_orig[0] == case_dest[0] + 1) ||
        (case_orig[1] == case_dest[1] + 2 &&
         case_orig[0] == case_dest[0] - 1) ||
        (case_orig[1] == case_dest[1] - 2 &&
         case_orig[0] == case_dest[0] + 1) ||
        (case_orig[1] == case_dest[1] - 2 && case_orig[0] == case_dest[0] - 1))
        return true;
    else if ((case_orig[1] == case_dest[1] + 1 &&
              case_orig[0] == case_dest[0] + 2) ||
             (case_orig[1] == case_dest[1] + 1 &&
              case_orig[0] == case_dest[0] - 2) ||
             (case_orig[1] == case_dest[1] - 1 &&
              case_orig[0] == case_dest[0] + 2) ||
             (case_orig[1] == case_dest[1] - 1 &&
              case_orig[0] == case_dest[0] - 2))
        return true;
    else
        return false;
}

string Cavalier::get_type() { return "Cavalier"; }

// ----------------------------------------------------------

Fou::Fou(Couleur couleur, string nom, Square position)
    : Piece(couleur, nom, position) {}

bool Fou::est_mouvement_legal(string case_orig, string case_dest) {
    for (int i(1); i < NBCOL; i++) {
        if ((case_orig[1] == case_dest[1] + i &&
             case_orig[0] == case_dest[0] + i) ||
            (case_orig[1] == case_dest[1] - i &&
             case_orig[0] == case_dest[0] + i) ||
            (case_orig[1] == case_dest[1] + i &&
             case_orig[0] == case_dest[0] - i) ||
            (case_orig[1] == case_dest[1] - i &&
             case_orig[0] == case_dest[0] - i))
            return true;
    }
    return false;
}

string Fou::get_type() { return "Fou"; }

// -------------------------------------------------------------------------

Dame::Dame(Couleur couleur, string nom, Square position)
    : Piece(couleur, nom, position) {}

bool Dame::est_mouvement_legal(string case_orig, string case_dest) {
    if (case_orig[0] == case_dest[0])
        return true;
    else if (case_orig[1] == case_dest[1])
        return true;
    else {
        for (int i(1); i < NBCOL; i++) {
            if ((case_orig[1] == case_dest[1] + i &&
                 case_orig[0] == case_dest[0] + i) ||
                (case_orig[1] == case_dest[1] - i &&
                 case_orig[0] == case_dest[0] + i) ||
                (case_orig[1] == case_dest[1] + i &&
                 case_orig[0] == case_dest[0] - i) ||
                (case_orig[1] == case_dest[1] - i &&
                 case_orig[0] == case_dest[0] - i))
                return true;
        }
        return false;
    }
}

string Dame::get_type() { return "Dame"; }

// ---------------------------------------------------------------

Roi::Roi(Couleur couleur, string nom, Square position)
    : Piece(couleur, nom, position) {}

bool Roi::est_mouvement_legal(string case_orig, string case_dest) {
    if ((case_orig[0] == case_dest[0] + 1 ||
         case_orig[0] == case_dest[0] - 1) &&
        case_orig[1] == case_dest[1]) {
        a_bouge = true;
        return true;
    } else if ((case_orig[1] == case_dest[1] + 1 ||
                case_orig[1] == case_dest[1] - 1) &&
               case_orig[0] == case_dest[0]) {
        return true;
    } else if ((case_orig[1] == case_dest[1] + 1 &&
                case_orig[0] == case_dest[0] + 1) ||
               (case_orig[1] == case_dest[1] + 1 &&
                case_orig[0] == case_dest[0] - 1) ||
               (case_orig[1] == case_dest[1] - 1 &&
                case_orig[0] == case_dest[0] + 1) ||
               (case_orig[1] == case_dest[1] - 1 &&
                case_orig[0] == case_dest[0] - 1)) {
        return true;
    } else
        return false;
}

string Roi::get_type() { return "Roi"; }

// ----------------------------------------------------------

Pion::Pion(Couleur couleur, string nom, Square position)
    : Piece(couleur, nom, position) {}

bool Pion::est_mouvement_legal(string case_orig, string case_dest) {
    if (couleur == Blanc) {
        if (case_orig[1] == case_dest[1] - 1 && case_orig[0] == case_dest[0])
            return true;
        else if ((case_orig[1] == case_dest[1] - 1 &&
                  case_orig[0] == case_dest[0] - 1) ||
                 (case_orig[1] == case_dest[1] - 1 &&
                  case_orig[0] == case_dest[0] + 1))
            return true;
        else if (case_orig[1] == '2' && case_orig[1] == case_dest[1] - 2 &&
                 case_orig[0] == case_dest[0])
            return true;
        else
            return false;
    } else if (couleur == Noir) {
        if (case_orig[1] == case_dest[1] + 1 && case_orig[0] == case_dest[0])
            return true;
        else if ((case_orig[1] == case_dest[1] + 1 &&
                  case_orig[0] == case_dest[0] - 1) ||
                 (case_orig[1] == case_dest[1] + 1 &&
                  case_orig[0] == case_dest[0] + 1))
            return true;
        else if (case_orig[1] == '7' && case_orig[1] == case_dest[1] + 2 &&
                 case_orig[0] == case_dest[0])
            return true;
        else
            return false;
    } else
        return false;
}

string Pion::get_type() { return "Pion"; }