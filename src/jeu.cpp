#include "jeu.h"

using namespace std;

bool Jeu::test_echec(Couleur couleur, bool test_echec_et_mat) { return echiquier.echec(couleur, test_echec_et_mat); }

bool Jeu::test_mat(Couleur couleur) { return echiquier.mat_ou_pat_ou_egalite(couleur, false, 0); }

bool Jeu::test_pat_ou_egalite(Couleur couleur, int compteur) { return echiquier.mat_ou_pat_ou_egalite(couleur, true, compteur); }

bool Jeu::execution(Couleur couleur, string str_orig, string str_dest, string coup_prec, bool *prise_ou_pion) {
    Square orig(str_orig), dest(str_dest);
    if (str_orig == str_dest) {
        cerr << endl << ANSI_COLOR_RED << "Mouvement ne déplaçant pas la pièce (si elle existe), veuillez réessayer ! " << ANSI_COLOR_RESET << endl;
        return false;
    } else if (dest.get_ligne() < 0 || dest.get_ligne() >= NBCOL || dest.get_colonne() < 0 || dest.get_colonne() >= NBCOL) {
        cerr << endl << ANSI_COLOR_RED << "Mouvement en dehors de la grille, veuillez réessayer ! " << ANSI_COLOR_RESET << endl;
        return false;
    } else if (echiquier.get_piece(orig) == nullptr) {
        cerr << endl << ANSI_COLOR_RED << "La case d'origine est vide ! " << ANSI_COLOR_RESET << endl;
        return false;
    } else if (echiquier.get_piece(orig)->get_couleur() != couleur) {
        cerr << endl << ANSI_COLOR_RED << "Cette pièce ne vous appartient pas, veuillez réessayer ! " << ANSI_COLOR_RESET << endl;
        return false;
    } else if (echiquier.get_piece(orig)->est_mouvement_legal(str_orig, str_dest)) { // Cas où le mouvement est légal dans un échiquier vide

        if (echiquier.get_piece(dest) == nullptr) { // Si la case de destination est vide
            /* Implémentation de la prise en passant */
            if (echiquier.get_piece(orig)->get_type() == "Pion" &&
                (orig.get_colonne() - dest.get_colonne() == 1 || orig.get_colonne() - dest.get_colonne() == -1)) {
                string str_cp_orig(coup_prec.substr(0, 2)), str_cp_dest(coup_prec.substr(2, 2));
                Square cp_orig(str_cp_orig), cp_dest(str_cp_dest);

                if (dest.get_ligne() == 5 && cp_orig.get_colonne() == dest.get_colonne() && cp_orig.get_ligne() == 6 && cp_dest.get_ligne() == 4) {
                    echiquier.prise_en_passant(cp_dest.get_ligne(), cp_dest.get_colonne());
                    *prise_ou_pion = true;
                } else if (dest.get_ligne() == 2 && cp_orig.get_colonne() == dest.get_colonne() && cp_orig.get_ligne() == 1 &&
                           cp_dest.get_ligne() == 3) {
                    echiquier.prise_en_passant(cp_dest.get_ligne(), cp_dest.get_colonne());
                    *prise_ou_pion = true;
                } else {
                    cerr << endl
                         << ANSI_COLOR_RED << "Déplacement en diagonale invalide pour un pion, veuillez réessayer ! " << ANSI_COLOR_RESET << endl;
                    return false;
                }
            }

            if (!echiquier.verif_saut(orig, dest, false))
                return false;
            if (echiquier.deplace(orig, dest) == false) {
                return false;
            };

            if (echiquier.get_piece(dest)->get_type() == "Pion")
                *prise_ou_pion = true;

            if (echiquier.get_piece(dest)->get_type() == "Pion" && echiquier.get_piece(dest)->get_couleur() == Blanc && dest.get_ligne() == 7) {
                if (!echiquier.promotion(Blanc, dest))
                    return false;
            } else if (echiquier.get_piece(dest)->get_type() == "Pion" && echiquier.get_piece(dest)->get_couleur() == Noir && dest.get_ligne() == 0) {
                if (!echiquier.promotion(Noir, dest))
                    return false;
            }
            return true;
        } else if (echiquier.get_piece(dest)->get_couleur() == couleur) { // Si la case de destination est occupée par une pièce de la même couleur
            /* Avertissement si déplacement d'un pion en diagonale */
            if (echiquier.get_piece(orig)->get_type() == "Pion" &&
                (orig.get_colonne() - dest.get_colonne() == 1 || orig.get_colonne() - dest.get_colonne() == -1)) {
                cerr << endl << ANSI_COLOR_RED << "Déplacement en diagonale invalide pour un pion, veuillez réessayer ! " << ANSI_COLOR_RESET << endl;
                return false;
            }
            cerr << endl
                 << ANSI_COLOR_RED << "La case de destination est occupée par une de vos pièces, veuillez réessayer ! " << ANSI_COLOR_RESET << endl;
            return false;
        } else { // Si la case de destination est occupée par une pièce de la couleur opposée
            if (echiquier.get_piece(orig)->get_type() == "Pion" && orig.get_colonne() - dest.get_colonne() == 0) {
                cerr << endl << ANSI_COLOR_RED << "Prise en avançant invalide pour un pion, veuillez réessayer ! " << ANSI_COLOR_RESET << endl;
                return false;
            }

            if (!echiquier.verif_saut(orig, dest, false))
                return false;

            echiquier.get_piece(dest)->set_prise(true);
            if (echiquier.deplace(orig, dest) == false) {
                return false;
            };
            cout << endl << ANSI_COLOR_GREEN << "Vous avez pris une pièce ! " << ANSI_COLOR_RESET << endl;
            *prise_ou_pion = true;

            /* Implémentation de la promotion */
            if (echiquier.get_piece(dest)->get_type() == "Pion" && echiquier.get_piece(dest)->get_couleur() == Blanc && dest.get_ligne() == 7) {
                if (!echiquier.promotion(Blanc, dest))
                    return false;
            } else if (echiquier.get_piece(dest)->get_type() == "Pion" && echiquier.get_piece(dest)->get_couleur() == Noir && dest.get_ligne() == 0) {
                if (!echiquier.promotion(Noir, dest))
                    return false;
            }
            return true;
        }
    } else {
        cerr << endl << ANSI_COLOR_RED << "Mouvement invalide, veuillez réessayer ! " << ANSI_COLOR_RESET << endl;
        return false;
    }
}

void Jeu::force_deplace(Square orig, Square dest) { echiquier.deplace(orig, dest); }

Piece *Jeu::get_piece(Square pos) { return echiquier.get_piece(pos); }

void Jeu::affiche() const { echiquier.affiche(); }

bool Jeu::petit_roque(Couleur couleur) {
    if (couleur == Blanc) {
        if (echiquier.echec(couleur, false)) {
            cerr << endl
                 << ANSI_COLOR_RED << "Impossible de réaliser le petit roque, votre roi est en échec, veuillez réessayer ! " << ANSI_COLOR_RESET
                 << endl;
            return false;
        } else if ((echiquier.get_piece(0, 4) && echiquier.get_piece(0, 4)->get_a_bouge()) || !echiquier.get_piece(0, 4) ||
                   (echiquier.get_piece(0, 7) && echiquier.get_piece(0, 7)->get_a_bouge()) || !echiquier.get_piece(0, 7)) {
            cerr << endl
                 << ANSI_COLOR_RED << "Impossible de réaliser le petit roque, le roi ou la tour a été déplacé, veuillez réessayer ! "
                 << ANSI_COLOR_RESET << endl;
            return false;
        } else if (echiquier.get_piece(0, 5) || echiquier.get_piece(0, 6)) {
            cerr << endl
                 << ANSI_COLOR_RED << "Impossible de réaliser le petit roque, les cases sont occupées, veuillez réessayer ! " << ANSI_COLOR_RESET
                 << endl;
            return false;
        } else {
            if (echiquier.deplace(Square(0, 4), Square(0, 5)) == false) {
                cerr << ANSI_COLOR_RED << "Impossible de réaliser le petit roque, votre roi est menacé à un moment, veuillez réessayer !"
                     << ANSI_COLOR_RESET << endl;
                return false;
            };
            if (echiquier.deplace(Square(0, 5), Square(0, 6)) == false) {
                force_deplace(Square(0, 5), Square(0, 4));
                cerr << ANSI_COLOR_RED << "Impossible de réaliser le petit roque, votre roi est menacé à un moment, veuillez réessayer !"
                     << ANSI_COLOR_RESET << endl;
                return false;
            };
            if (echiquier.deplace(Square(0, 7), Square(0, 5)) == false) {
                cerr << ANSI_COLOR_RED << "Impossible de réaliser le petit roque, votre roi est menacé à un moment, veuillez réessayer !"
                     << ANSI_COLOR_RESET << endl;
                return false;
            };
            return true;
        }
    } else {
        if (echiquier.echec(couleur, false)) {
            cerr << endl
                 << ANSI_COLOR_RED << "Impossible de réaliser le petit roque, votre roi est en échec, veuillez réessayer ! " << ANSI_COLOR_RESET
                 << endl;
            return false;
        } else if ((echiquier.get_piece(7, 4) && echiquier.get_piece(7, 4)->get_a_bouge()) || !echiquier.get_piece(7, 4) ||
                   (echiquier.get_piece(7, 7) && echiquier.get_piece(7, 7)->get_a_bouge()) || !echiquier.get_piece(7, 7)) {
            cerr << endl
                 << ANSI_COLOR_RED << "Impossible de réaliser le petit roque, le roi ou la tour a été déplacé, veuillez réessayer ! "
                 << ANSI_COLOR_RESET << endl;
            return false;
        } else if (echiquier.get_piece(7, 5) || echiquier.get_piece(7, 6)) {
            cerr << endl
                 << ANSI_COLOR_RED << "Impossible de réaliser le petit roque, les cases sont occupées, veuillez réessayer ! " << ANSI_COLOR_RESET
                 << endl;
            return false;
        } else {
            if (echiquier.deplace(Square(7, 4), Square(7, 5)) == false) {
                cerr << ANSI_COLOR_RED << "Impossible de réaliser le petit roque, votre roi est menacé à un moment, veuillez réessayer !"
                     << ANSI_COLOR_RESET << endl;
                return false;
            };
            if (echiquier.deplace(Square(7, 5), Square(7, 6)) == false) {
                force_deplace(Square(7, 5), Square(7, 4));
                cerr << ANSI_COLOR_RED << "Impossible de réaliser le petit roque, votre roi est menacé à un moment, veuillez réessayer !"
                     << ANSI_COLOR_RESET << endl;
                return false;
            };
            if (echiquier.deplace(Square(7, 7), Square(7, 5)) == false) {
                cerr << ANSI_COLOR_RED << "Impossible de réaliser le petit roque, votre roi est menacé à un moment, veuillez réessayer !"
                     << ANSI_COLOR_RESET << endl;
                return false;
            };
            return true;
        }
    }
}
bool Jeu::grand_roque(Couleur couleur) {
    if (couleur == Blanc) {
        if (echiquier.echec(couleur, false)) {
            cerr << endl
                 << ANSI_COLOR_RED << "Impossible de réaliser le grand roque, votre roi est en échec, veuillez réessayer ! " << ANSI_COLOR_RESET
                 << endl;
            return false;
        } else if ((echiquier.get_piece(0, 4) && echiquier.get_piece(0, 4)->get_a_bouge()) || !echiquier.get_piece(0, 4) ||
                   (echiquier.get_piece(0, 0) && echiquier.get_piece(0, 0)->get_a_bouge()) || !echiquier.get_piece(0, 0)) {
            cerr << endl
                 << ANSI_COLOR_RED << "Impossible de réaliser le grand roque, le roi ou la tour a été déplacé, veuillez réessayer ! "
                 << ANSI_COLOR_RESET << endl;
            return false;
        } else if (echiquier.get_piece(0, 1) || echiquier.get_piece(0, 2) || echiquier.get_piece(0, 3)) {
            cerr << endl
                 << ANSI_COLOR_RED << "Impossible de réaliser le grand roque, les cases sont occupées, veuillez réessayer ! " << ANSI_COLOR_RESET
                 << endl;
            return false;
        } else {
            if (echiquier.deplace(Square(0, 4), Square(0, 3)) == false) {
                cerr << ANSI_COLOR_RED << "Impossible de réaliser le grand roque, votre roi est menacé à un moment, veuillez réessayer !"
                     << ANSI_COLOR_RESET << endl;
                return false;
            };
            if (echiquier.deplace(Square(0, 3), Square(0, 2)) == false) {
                force_deplace(Square(0, 3), Square(0, 4));
                cerr << ANSI_COLOR_RED << "Impossible de réaliser le grand roque, votre roi est menacé à un moment, veuillez réessayer !"
                     << ANSI_COLOR_RESET << endl;
                return false;
            };
            if (echiquier.deplace(Square(0, 0), Square(0, 3)) == false) {
                cerr << ANSI_COLOR_RED << "Impossible de réaliser le grand roque, votre roi est menacé à un moment, veuillez réessayer !"
                     << ANSI_COLOR_RESET << endl;
                return false;
            };
            return true;
        }
    } else {
        if (echiquier.echec(couleur, false)) {
            cerr << endl
                 << ANSI_COLOR_RED << "Impossible de réaliser le grand roque, votre roi est en échec, veuillez réessayer ! " << ANSI_COLOR_RESET
                 << endl;
            return false;
        } else if ((echiquier.get_piece(7, 4) && echiquier.get_piece(7, 4)->get_a_bouge()) || !echiquier.get_piece(7, 4) ||
                   (echiquier.get_piece(7, 0) && echiquier.get_piece(7, 0)->get_a_bouge()) || !echiquier.get_piece(7, 0)) {
            cerr << endl
                 << ANSI_COLOR_RED << "Impossible de réaliser le grand roque, le roi ou la tour a été déplacé, veuillez réessayer ! "
                 << ANSI_COLOR_RESET << endl;
            return false;
        } else if (echiquier.get_piece(7, 1) || echiquier.get_piece(7, 2) || echiquier.get_piece(7, 3)) {
            cerr << endl
                 << ANSI_COLOR_RED << "Impossible de réaliser le grand roque, les cases sont occupées, veuillez réessayer ! " << ANSI_COLOR_RESET
                 << endl;
            return false;
        } else {
            if (echiquier.deplace(Square(7, 4), Square(7, 3)) == false) {
                cerr << ANSI_COLOR_RED << "Impossible de réaliser le grand roque, votre roi est menacé à un moment, veuillez réessayer !"
                     << ANSI_COLOR_RESET << endl;
                return false;
            };
            if (echiquier.deplace(Square(7, 3), Square(7, 2)) == false) {
                force_deplace(Square(7, 3), Square(7, 4));
                cerr << ANSI_COLOR_RED << "Impossible de réaliser le grand roque, votre roi est menacé à un moment, veuillez réessayer !"
                     << ANSI_COLOR_RESET << endl;
                return false;
            };
            if (echiquier.deplace(Square(7, 0), Square(7, 3)) == false) {
                cerr << ANSI_COLOR_RED << "Impossible de réaliser le grand roque, votre roi est menacé à un moment, veuillez réessayer !"
                     << ANSI_COLOR_RESET << endl;
                return false;
            };
            return true;
        }
    }
}

string Jeu::canonical_position() { return echiquier.canonical_position(); }

void Jeu::fin_de_partie(Couleur couleur, bool stop, bool pat) {
    if (!stop) {
        if (!pat)
            cout << endl << ANSI_COLOR_GREEN << "Le joueur " << (couleur ? "Noir" : "Blanc") << " a gagné ! " << ANSI_COLOR_RESET << endl;
        else
            cout << "Égalité ! " << endl;
    }
    cout << endl << echiquier.canonical_position() << endl;
}
