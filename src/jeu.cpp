#include "jeu.h"

using namespace std;

bool Jeu::test_echec(Couleur couleur, bool test_echec_et_mat) {
    return echiquier.echec(couleur, test_echec_et_mat);
}

bool Jeu::test_mat(Couleur couleur) { return echiquier.mat(couleur); }

bool Jeu::deplace(Couleur couleur, string str_orig, string str_dest,
                  string coup_prec) {
    Square orig(str_orig), dest(str_dest);
    /*     if (echiquier.echec(couleur))
            return false; */
    if (str_orig == str_dest) {
        cout << endl
             << ANSI_COLOR_RED
             << "Mouvement ne déplaçant pas la pièce (si elle existe), "
                "veuillez réessayer ! "
             << ANSI_COLOR_RESET << endl;
        return false;
    } else if (dest.get_x() < 0 || dest.get_x() >= NBCOL || dest.get_y() < 0 ||
               dest.get_y() >= NBCOL) {
        cout << endl
             << ANSI_COLOR_RED
             << "Mouvement en dehors de la grille, veuillez réessayer ! "
             << ANSI_COLOR_RESET << endl;
        return false;
    } else if (echiquier.get_piece(orig) == nullptr) {
        cout << endl
             << ANSI_COLOR_RED << "La case d'origine est vide ! "
             << ANSI_COLOR_RESET << endl;
        return false;
    } else if (echiquier.get_piece(orig)->get_couleur() != couleur) {
        cout << endl
             << ANSI_COLOR_RED
             << "Cette pièce ne vous appartient pas, veuillez réessayer ! "
             << ANSI_COLOR_RESET << endl;
        return false;
    } else if (echiquier.get_piece(orig)->est_mouvement_legal(str_orig,
                                                              str_dest)) {
        for (int d(orig.get_x()); d < orig.get_x(); d++) {
            if (echiquier.get_piece(d, orig.get_y())) {
                cout << endl
                     << ANSI_COLOR_RED
                     << "Vous sautez une pièce, veuillez réessayer ! "
                     << ANSI_COLOR_RESET << endl;
                return false;
            }
        }

        if (echiquier.get_piece(dest) == nullptr) {
            if ((echiquier.get_piece(orig)->affiche() == "\u2659" ||
                 echiquier.get_piece(orig)->affiche() == "\u265F") &&
                (orig.get_y() - dest.get_y() == 1 ||
                 orig.get_y() - dest.get_y() == -1)) {
                string str_cp_orig = coup_prec.substr(0, 2);
                string str_cp_dest = coup_prec.substr(2, 2);
                Square cp_orig(str_cp_orig), cp_dest(str_cp_dest);

                if (dest.get_x() == 5 && cp_orig.get_y() == dest.get_y() &&
                    cp_orig.get_x() == 6 && cp_dest.get_x() == 4) {
                    cout << endl
                         << ANSI_COLOR_GREEN << "Prise en passant ! "
                         << ANSI_COLOR_RESET << endl;
                    echiquier.get_piece(cp_dest.get_x(), cp_dest.get_y())
                        ->set_prise(true);
                    echiquier.prise_en_passant(cp_dest.get_x(),
                                               cp_dest.get_y());
                } else if (dest.get_x() == 2 &&
                           cp_orig.get_y() == dest.get_y() &&
                           cp_orig.get_x() == 1 && cp_dest.get_x() == 3) {
                    cout << endl
                         << ANSI_COLOR_GREEN << "Prise en passant ! "
                         << ANSI_COLOR_RESET << endl;
                    echiquier.get_piece(cp_dest.get_x(), cp_dest.get_y())
                        ->set_prise(true);
                    echiquier.prise_en_passant(cp_dest.get_x(),
                                               cp_dest.get_y());
                } else {
                    cout << endl
                         << ANSI_COLOR_RED
                         << "Déplacement en diagonale invalide pour un pion, "
                            "veuillez réessayer ! "
                         << ANSI_COLOR_RESET << endl;
                    return false;
                }
            }
            if (!echiquier.verif_saut(orig, dest, false))
                return false;
            echiquier.deplace(orig, dest);

            if (echiquier.get_piece(dest)->affiche() == "\u2659" &&
                dest.get_x() == 7) {
                if (!echiquier.promotion(Blanc, dest))
                    return false;
            } else if (echiquier.get_piece(dest)->affiche() == "\u265F" &&
                       dest.get_x() == 0) {
                if (!echiquier.promotion(Noir, dest))
                    return false;
            }
            return true;
        } else if (echiquier.get_piece(dest)->get_couleur() == couleur) {
            if ((echiquier.get_piece(orig)->affiche() == "\u2659" ||
                 echiquier.get_piece(orig)->affiche() == "\u265F") &&
                (orig.get_y() - dest.get_y() == 1 ||
                 orig.get_y() - dest.get_y() == -1)) {
                cout << endl
                     << ANSI_COLOR_RED
                     << "Déplacement en diagonale invalide pour un pion, "
                        "veuillez réessayer ! "
                     << ANSI_COLOR_RESET << endl;
                return false;
            }
            cout << endl
                 << ANSI_COLOR_RED
                 << "La case de destination est occupée par une de vos "
                    "pièces, veuillez réessayer ! "
                 << ANSI_COLOR_RESET << endl;
            return false;
        } else {
            if ((echiquier.get_piece(orig)->affiche() == "\u2659" ||
                 echiquier.get_piece(orig)->affiche() == "\u265F") &&
                orig.get_y() - dest.get_y() == 0) {
                cout << endl
                     << ANSI_COLOR_RED
                     << "Prise en avançant invalide pour un pion, veuillez "
                        "réessayer ! "
                     << ANSI_COLOR_RESET << endl;
                return false;
            }
            if (!echiquier.verif_saut(orig, dest, false))
                return false;
            echiquier.get_piece(dest)->set_prise(true);
            echiquier.deplace(orig, dest);
            cout << endl
                 << ANSI_COLOR_GREEN << "Vous avez pris une pièce ! "
                 << ANSI_COLOR_RESET << endl;

            if (echiquier.get_piece(dest)->affiche() == "\u2659" &&
                dest.get_x() == 7) {
                if (!echiquier.promotion(Blanc, dest))
                    return false;
            } else if (echiquier.get_piece(dest)->affiche() == "\u265F" &&
                       dest.get_x() == 0) {
                if (!echiquier.promotion(Noir, dest))
                    return false;
            }
            return true;
        }
    } else {
        cout << endl
             << ANSI_COLOR_RED << "Mouvement invalide, veuillez réessayer ! "
             << ANSI_COLOR_RESET << endl;
        return false;
    }
}

void Jeu::affiche() { echiquier.affiche(); }

bool Jeu::petit_roque(Couleur couleur) {
    if (couleur == Blanc) {
        if ((echiquier.get_piece(0, 4) &&
             echiquier.get_piece(0, 4)->get_a_bouge()) ||
            (echiquier.get_piece(0, 7) &&
             echiquier.get_piece(0, 7)->get_a_bouge())) {
            cout << endl
                 << ANSI_COLOR_RED
                 << "Impossible de réaliser le petit roque, le roi ou la tour "
                    "a été déplacé, veuillez réessayer ! "
                 << ANSI_COLOR_RESET << endl;
            return false;
        } else if (echiquier.get_piece(0, 5) || echiquier.get_piece(0, 6)) {
            cout << endl
                 << ANSI_COLOR_RED
                 << "Impossible de réaliser le petit roque, les cases sont "
                    "occupées, veuillez réessayer ! "
                 << ANSI_COLOR_RESET << endl;
            return false;
        } else {
            echiquier.deplace(Square(0, 4), Square(0, 6));
            echiquier.deplace(Square(0, 7), Square(0, 5));
            return true;
        }
    } else {
        if ((echiquier.get_piece(7, 4) &&
             echiquier.get_piece(7, 4)->get_a_bouge()) ||
            (echiquier.get_piece(7, 7) &&
             echiquier.get_piece(7, 7)->get_a_bouge())) {
            cout << endl
                 << ANSI_COLOR_RED
                 << "Impossible de réaliser le petit roque, le roi ou la tour "
                    "a été déplacé, veuillez réessayer ! "
                 << ANSI_COLOR_RESET << endl;
            return false;
        } else if (echiquier.get_piece(7, 5) || echiquier.get_piece(7, 6)) {
            cout << endl
                 << ANSI_COLOR_RED
                 << "Impossible de réaliser le petit roque, les cases sont "
                    "occupées, veuillez réessayer ! "
                 << ANSI_COLOR_RESET << endl;
            return false;
        } else {
            echiquier.deplace(Square(7, 4), Square(7, 6));
            echiquier.deplace(Square(7, 7), Square(7, 5));
            return true;
        }
    }
}
bool Jeu::grand_roque(Couleur couleur) {
    if (couleur == Blanc) {
        if ((echiquier.get_piece(0, 4) &&
             echiquier.get_piece(0, 4)->get_a_bouge()) ||
            (echiquier.get_piece(0, 0) &&
             echiquier.get_piece(0, 0)->get_a_bouge())) {
            cout << endl
                 << ANSI_COLOR_RED
                 << "Impossible de réaliser le grand roque, le roi ou la tour "
                    "a été déplacé, veuillez réessayer ! "
                 << ANSI_COLOR_RESET << endl;
            return false;
        } else if (echiquier.get_piece(0, 1) || echiquier.get_piece(0, 2) ||
                   echiquier.get_piece(0, 3)) {
            cout << endl
                 << ANSI_COLOR_RED
                 << "Impossible de réaliser le grand roque, les cases sont "
                    "occupées, veuillez réessayer ! "
                 << ANSI_COLOR_RESET << endl;
            return false;
        } else {
            echiquier.deplace(Square(0, 4), Square(0, 2));
            echiquier.deplace(Square(0, 0), Square(0, 3));
            return true;
        }
    } else {
        if ((echiquier.get_piece(7, 4) &&
             echiquier.get_piece(7, 4)->get_a_bouge()) ||
            (echiquier.get_piece(7, 0) &&
             echiquier.get_piece(7, 0)->get_a_bouge())) {
            cout << endl
                 << ANSI_COLOR_RED
                 << "Impossible de réaliser le grand roque, le roi ou la tour "
                    "a été déplacé, veuillez réessayer ! "
                 << ANSI_COLOR_RESET << endl;
            return false;
        } else if (echiquier.get_piece(7, 1) || echiquier.get_piece(7, 2) ||
                   echiquier.get_piece(7, 3)) {
            cout << endl
                 << ANSI_COLOR_RED
                 << "Impossible de réaliser le grand roque, les cases sont "
                    "occupées, veuillez réessayer ! "
                 << ANSI_COLOR_RESET << endl;
            return false;
        } else {
            echiquier.deplace(Square(7, 4), Square(7, 2));
            echiquier.deplace(Square(7, 0), Square(7, 3));
            return true;
        }
    }
}

void Jeu::fin_de_partie() {
    cout << endl << echiquier.canonical_position() << endl;
}