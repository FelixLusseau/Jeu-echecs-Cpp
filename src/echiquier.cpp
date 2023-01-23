#include <queue>

#include "echiquier.h"
#include "piece.h"
#include "square.h"

Echiquier::Echiquier() {
    /* Initialisation des cases à nullptr */
    for (int i = 0; i < NBCOL; i++) {
        for (int j = 0; j < NBCOL; j++) {
            echiquier[i][j] = nullptr;
        }
    }

    // Constructeur (couleur, nom_affiché, case)
    piecesb[0] = new Tour(Blanc, "\u265C", Square(0, 0));
    piecesb[1] = new Cavalier(Blanc, "\u265E", Square(0, 1));
    piecesb[2] = new Fou(Blanc, "\u265D", Square(0, 2));
    piecesb[3] = new Dame(Blanc, "\u265B", Square(0, 3));
    piecesb[4] = new Roi(Blanc, "\u265A", Square(0, 4));
    piecesb[5] = new Fou(Blanc, "\u265D", Square(0, 5));
    piecesb[6] = new Cavalier(Blanc, "\u265E", Square(0, 6));
    piecesb[7] = new Tour(Blanc, "\u265C", Square(0, 7));
    piecesn[0] = new Tour(Noir, "\u265C", Square(7, 0));
    piecesn[1] = new Cavalier(Noir, "\u265E", Square(7, 1));
    piecesn[2] = new Fou(Noir, "\u265D", Square(7, 2));
    piecesn[3] = new Dame(Noir, "\u265B", Square(7, 3));
    piecesn[4] = new Roi(Noir, "\u265A", Square(7, 4));
    piecesn[5] = new Fou(Noir, "\u265D", Square(7, 5));
    piecesn[6] = new Cavalier(Noir, "\u265E", Square(7, 6));
    piecesn[7] = new Tour(Noir, "\u265C", Square(7, 7));

    // allocation des pions
    for (unsigned char i(0); i < NBCOL; i++) {
        pionsb[i] = new Pion(Blanc, "\u265F", Square(1, i));
        pionsn[i] = new Pion(Noir, "\u265F", Square(6, i));
    }
    // Pose des pieces en position initiale
    for (unsigned char i(0); i < NBCOL; i++) {
        // met à jour le tableau echiquier, à la case donnée par
        // la position courante de la pièce obtenue avec
        // piecesb[i]->get_pos(),
        // avec le pointeur vers la pièce (piecesb[i] etc)
        pose_piece(piecesb[i]);
        pose_piece(piecesn[i]);
        pose_piece(pionsb[i]);
        pose_piece(pionsn[i]);
    }
}

Echiquier::~Echiquier() {
    for (unsigned char i(0); i < NBCOL; i++) {
        delete piecesb[i];
        delete piecesn[i];
        delete pionsb[i];
        delete pionsn[i];
    }
}

Piece *Echiquier::get_piece(Square pos) { return echiquier[pos.get_ligne()][pos.get_colonne()]; }

Piece *Echiquier::get_piece(int ligne, int colonne) { return echiquier[ligne][colonne]; }

void Echiquier::pose_piece(Piece *piece) { echiquier[piece->get_pos().get_ligne()][piece->get_pos().get_colonne()] = piece; }

bool Echiquier::deplace(Square orig, Square dest) {
    Piece *ancienne_piece_dest = get_piece(dest);
    Couleur couleur = get_piece(orig)->get_couleur();

    /* Déplacement de la pièce */
    echiquier[dest.get_ligne()][dest.get_colonne()] = echiquier[orig.get_ligne()][orig.get_colonne()];
    echiquier[orig.get_ligne()][orig.get_colonne()] = nullptr;
    echiquier[dest.get_ligne()][dest.get_colonne()]->set_pos(dest, false);

    /* Vérification de non mise en échec sinon annulation du coup */
    if (echec(couleur, false)) {
        echiquier[orig.get_ligne()][orig.get_colonne()] = echiquier[dest.get_ligne()][dest.get_colonne()];
        echiquier[dest.get_ligne()][dest.get_colonne()] = ancienne_piece_dest;
        echiquier[orig.get_ligne()][orig.get_colonne()]->set_pos(orig, false);
        cerr << endl
             << ANSI_COLOR_RED
             << "Votre roi est (toujours) en échec, veuillez "
                "réessayer ! "
             << ANSI_COLOR_RESET << endl;
        return false;
    }

    return true;
}

void Echiquier::prise_en_passant(int ligne, int colonne) {
    cout << endl << ANSI_COLOR_GREEN << "Prise en passant ! " << ANSI_COLOR_RESET;
    echiquier[ligne][colonne]->set_prise(true);
    echiquier[ligne][colonne] = nullptr;
}

bool Echiquier::promotion(Couleur couleur, Square pos) {
    char piece_promue;
    cout << "Choisissez une pièce à restaurer parmi Q, R, B et K : ";
    cin >> piece_promue;
    int pion_promu;

    if (couleur == Blanc) {
        /* Recherche du pion dans le tableaux des pions blancs */
        for (pion_promu = 0; pion_promu < NBCOL; pion_promu++) {
            if (pionsb[pion_promu] == get_piece(pos)) {
                break;
            }
        }

        Square ancienne_pos = pionsb[pion_promu]->get_pos();
        pionsb[pion_promu]->set_pos(pos, false);

        if (echec(couleur, false)) {
            pionsb[pion_promu]->set_pos(ancienne_pos, false);
            return false;
        }

        /* Suppression du pion et création de la pièce promue à sa position dans le tableau */
        switch (piece_promue) {
        case 'Q':
            delete pionsb[pion_promu];
            pionsb[pion_promu] = new Dame(Blanc, "\u265B", pos);
            pose_piece(pionsb[pion_promu]);
            break;
        case 'R':
            delete pionsb[pion_promu];
            pionsb[pion_promu] = new Tour(Blanc, "\u265C", pos);
            pose_piece(pionsb[pion_promu]);
            break;
        case 'B':
            delete pionsb[pion_promu];
            pionsb[pion_promu] = new Fou(Blanc, "\u265D", pos);
            pose_piece(pionsb[pion_promu]);
            break;
        case 'K':
            delete pionsb[pion_promu];
            pionsb[pion_promu] = new Cavalier(Blanc, "\u265E", pos);
            pose_piece(pionsb[pion_promu]);
            break;
        default:
            cerr << endl << ANSI_COLOR_RED << "Pièce sélectionnée invalide, veuillez réessayer ! " << ANSI_COLOR_RESET << endl;
            return false;
        }
    } else {
        /* Recherche du pion dans le tableaux des pions noirs */
        for (pion_promu = 0; pion_promu < NBCOL; pion_promu++) {
            if (pionsn[pion_promu] == get_piece(pos)) {
                break;
            }
        }

        Square ancienne_pos = pionsn[pion_promu]->get_pos();
        pionsn[pion_promu]->set_pos(pos, false);

        if (echec(couleur, false)) {
            pionsn[pion_promu]->set_pos(ancienne_pos, false);
            return false;
        }

        /* Suppression du pion et création de la pièce promue à sa position dans le tableau */
        switch (piece_promue) {
        case 'Q':
            delete pionsn[pion_promu];
            pionsn[pion_promu] = new Dame(Noir, "\u265B", pos);
            pose_piece(pionsn[pion_promu]);
            break;
        case 'R':
            delete pionsn[pion_promu];
            pionsn[pion_promu] = new Tour(Noir, "\u265C", pos);
            pose_piece(pionsn[pion_promu]);
            break;
        case 'B':
            delete pionsn[pion_promu];
            pionsn[pion_promu] = new Fou(Noir, "\u265D", pos);
            pose_piece(pionsn[pion_promu]);
            break;
        case 'K':
            delete pionsn[pion_promu];
            pionsn[pion_promu] = new Cavalier(Noir, "\u265E", pos);
            pose_piece(pionsn[pion_promu]);
            break;
        default:
            cerr << endl << ANSI_COLOR_RED << "Pièce sélectionnée invalide, veuillez réessayer ! " << ANSI_COLOR_RESET << endl;
            return false;
        }
    }
    return true;
}

bool Echiquier::verif_saut(Square &orig, Square &dest, bool test_echec) {
    int ligne_orig(orig.get_ligne()), ligne_dest(dest.get_ligne()), colonne_orig(orig.get_colonne()), colonne_dest(dest.get_colonne()), dligne,
        dcolonne;

    if (get_piece(ligne_orig, colonne_orig)->get_type() == "Cavalier" || get_piece(ligne_orig, colonne_orig)->get_type() == "Roi")
        return true;

    if (ligne_orig - ligne_dest == 0) {
        (colonne_orig < colonne_dest) ? dcolonne = 1 : dcolonne = -1; // Détermination du sens de déplacement

        for (int k(colonne_orig + dcolonne); k != colonne_dest; k += dcolonne) {
            if (test_echec) { // Dans le cas où on teste l'échec, travvaille sur les positions stockées dans les pièces
                for (int i(0); i < NBCOL; i++) {
                    if ((piecesb[i]->get_pos().get_ligne() == ligne_orig && piecesb[i]->get_pos().get_colonne() == k) ||
                        (piecesn[i]->get_pos().get_ligne() == ligne_orig && piecesn[i]->get_pos().get_colonne() == k) ||
                        (pionsb[i]->get_pos().get_ligne() == ligne_orig && pionsb[i]->get_pos().get_colonne() == k) ||
                        (pionsn[i]->get_pos().get_ligne() == ligne_orig && pionsn[i]->get_pos().get_colonne() == k)) {
                        if (!test_echec)
                            cerr << endl
                                 << ANSI_COLOR_RED
                                 << "Vous sautez une pièce, veuillez "
                                    "réessayer ! "
                                 << ligne_orig << k << ANSI_COLOR_RESET << endl;
                        return false;
                    }
                }
            } else { // Sinon travaille sur l'échiquier
                if (get_piece(ligne_orig, k) && get_piece(ligne_orig, k)->get_pos().get_ligne() == ligne_orig &&
                    get_piece(ligne_orig, k)->get_pos().get_colonne() == k) {
                    if (!test_echec)
                        cerr << endl
                             << ANSI_COLOR_RED
                             << "Vous sautez une pièce, veuillez "
                                "réessayer ! "
                             << ANSI_COLOR_RESET << endl;
                    return false;
                }
            }
        }
        return true;
    } else if (colonne_orig - colonne_dest == 0) {
        (ligne_orig < ligne_dest) ? dligne = 1 : dligne = -1;

        for (int k(ligne_orig + dligne); k != ligne_dest; k += dligne) {
            if (test_echec) {
                for (int i(0); i < NBCOL; i++) {
                    if ((piecesb[i]->get_pos().get_ligne() == k && piecesb[i]->get_pos().get_colonne() == colonne_orig) ||
                        (piecesn[i]->get_pos().get_ligne() == k && piecesn[i]->get_pos().get_colonne() == colonne_orig) ||
                        (pionsb[i]->get_pos().get_ligne() == k && pionsb[i]->get_pos().get_colonne() == colonne_orig) ||
                        (pionsn[i]->get_pos().get_ligne() == k && pionsn[i]->get_pos().get_colonne() == colonne_orig)) {
                        if (!test_echec)
                            cerr << endl
                                 << ANSI_COLOR_RED
                                 << "Vous sautez une pièce, veuillez "
                                    "réessayer ! "
                                 << ANSI_COLOR_RESET << endl;
                        return false;
                    }
                }
            } else {
                if (get_piece(k, colonne_orig) && get_piece(k, colonne_orig)->get_pos().get_colonne() == colonne_orig &&
                    get_piece(k, colonne_orig)->get_pos().get_ligne() == k) {
                    if (!test_echec)
                        cerr << endl
                             << ANSI_COLOR_RED
                             << "Vous sautez une pièce, veuillez "
                                "réessayer ! "
                             << ANSI_COLOR_RESET << endl;
                    return false;
                }
            }
        }
        return true;

    } else {
        (ligne_orig < ligne_dest) ? dligne = 1 : dligne = -1;
        (colonne_orig < colonne_dest) ? dcolonne = 1 : dcolonne = -1;

        for (int k(ligne_orig + dligne); k != ligne_dest; k += dligne) {
            for (int l(colonne_orig + dcolonne); l != colonne_dest; l += dcolonne) {
                if (test_echec) {
                    for (int i(0); i < NBCOL; i++) {
                        if ((piecesb[i]->get_pos().get_ligne() == k && piecesb[i]->get_pos().get_colonne() == l) ||
                            (piecesn[i]->get_pos().get_ligne() == k && piecesn[i]->get_pos().get_colonne() == l) ||
                            (pionsb[i]->get_pos().get_ligne() == k && pionsb[i]->get_pos().get_colonne() == l) ||
                            (pionsn[i]->get_pos().get_ligne() == k && pionsn[i]->get_pos().get_colonne() == l)) {
                            if (!test_echec)
                                cerr << endl
                                     << ANSI_COLOR_RED
                                     << "Vous sautez une pièce, veuillez "
                                        "réessayer ! "
                                     << ANSI_COLOR_RESET << endl;
                            return false;
                        }
                    }
                }

                else {
                    if (get_piece(k, l) && get_piece(k, l)->get_pos().get_colonne() == l && get_piece(k, l)->get_pos().get_ligne() == k) {
                        if (!test_echec)
                            cerr << endl
                                 << ANSI_COLOR_RED
                                 << "Vous sautez une pièce, veuillez "
                                    "réessayer ! "
                                 << ANSI_COLOR_RESET << endl;
                        return false;
                    }
                }
                k += dligne;
            }
            break;
        }
        return true;
    }
}

bool Echiquier::echec(Couleur couleur, bool test_echec_et_mat) {
    if (couleur == Noir) {
        Square roi_n_pos = piecesn[4]->get_pos();

        /* Teste la possibilité de mise en échec du roi noir par toutes les pièces blanches */
        for (int i(0); i < NBCOL; i++) {
            Square pieceb_i_pos = piecesb[i]->get_pos();
            Square pionb_i_pos = pionsb[i]->get_pos();

            if (!piecesb[i]->get_prise() && piecesb[i]->est_mouvement_legal(pieceb_i_pos.to_string(), roi_n_pos.to_string()) &&
                verif_saut(pieceb_i_pos, roi_n_pos, true)) {
                if (!test_echec_et_mat)
                    cout << ANSI_COLOR_RED << "Échec noir ! " << ANSI_COLOR_RESET << piecesb[i]->get_type() << " " << piecesb[i]->affiche() << " sur "
                         << ANSI_COLOR_BLACK << piecesn[4]->affiche() << ANSI_COLOR_RESET << endl;
                return true;
            } else if (!pionsb[i]->get_prise() && pionsb[i]->est_mouvement_legal(pionb_i_pos.to_string(), roi_n_pos.to_string()) &&
                       verif_saut(pionb_i_pos, roi_n_pos, true)) {
                if (pionsb[i]->get_type() == "Pion" && pionb_i_pos.get_colonne() - roi_n_pos.get_colonne() == 0) {
                    return false;
                }
                if (!test_echec_et_mat)
                    cout << ANSI_COLOR_RED << "Échec noir ! " << ANSI_COLOR_RESET << pionsb[i]->get_type() << " " << pionsb[i]->affiche() << " sur "
                         << piecesn[4]->affiche() << endl;
                return true;
            }
        }
    } else {
        Square roi_b_pos = piecesb[4]->get_pos();

        /* Teste la possibilité de mise en échec du roi blanc par toutes les pièces noires */
        for (int i(0); i < NBCOL; i++) {
            Square piecen_i_pos = piecesn[i]->get_pos();
            Square pionn_i_pos = pionsn[i]->get_pos();

            if (!piecesn[i]->get_prise() && piecesn[i]->est_mouvement_legal(piecen_i_pos.to_string(), roi_b_pos.to_string()) &&
                verif_saut(piecen_i_pos, roi_b_pos, true)) {
                if (!test_echec_et_mat)
                    cout << ANSI_COLOR_RED << "Échec blanc ! " << ANSI_COLOR_RESET << piecesn[i]->get_type() << " " << ANSI_COLOR_BLACK
                         << piecesn[i]->affiche() << ANSI_COLOR_RESET << " sur " << piecesb[4]->affiche() << endl;
                return true;
            } else if (!pionsn[i]->get_prise() && pionsn[i]->est_mouvement_legal(pionn_i_pos.to_string(), roi_b_pos.to_string()) &&
                       verif_saut(pionn_i_pos, roi_b_pos, true)) {
                if (pionsn[i]->get_type() == "Pion" && pionn_i_pos.get_colonne() - roi_b_pos.get_colonne() == 0) {
                    return false;
                }
                if (!test_echec_et_mat)
                    cout << ANSI_COLOR_RED << "Échec blanc ! " << ANSI_COLOR_RESET << pionsn[i]->get_type() << " " << ANSI_COLOR_BLACK
                         << pionsn[i]->affiche() << ANSI_COLOR_RESET << " sur " << piecesb[4]->affiche() << endl;
                return true;
            }
        }
    }
    return false;
}

bool Echiquier::mat_ou_pat_ou_egalite(Couleur couleur, bool test_pat, int compteur) {
    if (test_pat && compteur == 50) {
        cout << endl << ANSI_COLOR_RED << "50 coups sans prise ou déplacement de pion atteints. " << ANSI_COLOR_RESET << endl;
        return true;
    }

    if (couleur == Noir) {
        for (int i(0); i < NBCOL; i++) {

            Square piecen_i_pos = piecesn[i]->get_pos();
            Square pionn_i_pos = pionsn[i]->get_pos();

            /* Teste pour chaque case de l'échiquier si chaque pièce de la couleur peut s'y rendre légalement et si cela provoque ou prolonge un échec
             */
            for (size_t row(1); row <= 8; row++) {
                for (char col('a'); col <= 'h'; col++) {
                    string str(col + to_string(row));
                    Square square(str);

                    if (piecen_i_pos.to_string() == square.to_string() || pionn_i_pos.to_string() == square.to_string())
                        continue; // passe à la case suivante s'il s'agit de celle de la pièce

                    else if (!piecesn[i]->get_prise() && piecesn[i]->est_mouvement_legal(piecen_i_pos.to_string(), str) &&
                             verif_saut(piecen_i_pos, square, true) &&
                             ((get_piece(square) && (get_piece(square)->get_couleur() == Blanc)) || !get_piece(square))) {

                        piecesn[i]->set_pos(square, true); // Seule la position stockée dans la pièce est modifiée, l'échiquier est inchangé
                        if (get_piece(square)) {
                            get_piece(square)->set_prise(true);
                        }

                        if (!echec(Noir, true)) {
                            piecesn[i]->set_pos(piecen_i_pos, true);
                            if (get_piece(square)) {
                                get_piece(square)->set_prise(false);
                            }
                            return false;
                        }

                        if (get_piece(square)) {
                            get_piece(square)->set_prise(false);
                        }
                        piecesn[i]->set_pos(piecen_i_pos, true);
                    } else if (!pionsn[i]->get_prise() && pionsn[i]->est_mouvement_legal(pionn_i_pos.to_string(), str) &&
                               verif_saut(pionn_i_pos, square, true) &&
                               ((get_piece(square) &&
                                 (get_piece(square)->get_couleur() == Blanc && pionn_i_pos.get_colonne() != square.get_colonne())) ||
                                (!get_piece(square) && pionn_i_pos.get_colonne() == square.get_colonne()))) {

                        pionsn[i]->set_pos(square, true);
                        if (get_piece(square)) {
                            get_piece(square)->set_prise(true);
                        }

                        if (!echec(Noir, true)) {
                            pionsn[i]->set_pos(pionn_i_pos, true);
                            if (get_piece(square)) {
                                get_piece(square)->set_prise(false);
                            }
                            return false;
                        }

                        if (get_piece(square)) {
                            get_piece(square)->set_prise(false);
                        }
                        pionsn[i]->set_pos(pionn_i_pos, true);
                    }
                }
            }
        }
        if (!test_pat)
            cout << ANSI_COLOR_RED << "Échec et mat joueur Noir ! " << ANSI_COLOR_RESET << endl;
        else
            cout << endl << ANSI_COLOR_RED << "Pat ! Aucune pièce ne peut bouger sans mettre en échec le roi Noir." << ANSI_COLOR_RESET << endl;
    } else {
        for (int i(0); i < NBCOL; i++) {
            Square pieceb_i_pos = piecesb[i]->get_pos();
            Square pionb_i_pos = pionsb[i]->get_pos();

            /* Teste pour chaque case de l'échiquier si chaque pièce de la couleur peut s'y rendre légalement et si cela provoque ou prolonge un échec
             */
            for (size_t row(1); row <= 8; row++) {
                for (char col('a'); col <= 'h'; col++) {
                    string str(col + to_string(row));
                    Square square(str);

                    if (pieceb_i_pos.to_string() == square.to_string() || pionb_i_pos.to_string() == square.to_string())
                        continue;

                    else if (!piecesb[i]->get_prise() && piecesb[i]->est_mouvement_legal(pieceb_i_pos.to_string(), str) &&
                             verif_saut(pieceb_i_pos, square, true) &&
                             ((get_piece(square) && (get_piece(square)->get_couleur() == Noir)) || !get_piece(square))) {

                        piecesb[i]->set_pos(square, true);
                        if (get_piece(square)) {
                            get_piece(square)->set_prise(true);
                        }

                        if (!echec(Blanc, true)) {
                            piecesb[i]->set_pos(pieceb_i_pos, true);
                            if (get_piece(square)) {
                                get_piece(square)->set_prise(false);
                            }
                            return false;
                        }

                        if (get_piece(square)) {
                            get_piece(square)->set_prise(false);
                        }
                        piecesb[i]->set_pos(pieceb_i_pos, true);
                    } else if (!pionsb[i]->get_prise() && pionsb[i]->est_mouvement_legal(pionb_i_pos.to_string(), str) &&
                               verif_saut(pionb_i_pos, square, true) &&
                               ((get_piece(square) &&
                                 (get_piece(square)->get_couleur() == Noir && pionb_i_pos.get_colonne() != square.get_colonne())) ||
                                (!get_piece(square) && pionb_i_pos.get_colonne() == square.get_colonne()))) {

                        pionsb[i]->set_pos(square, true);
                        if (get_piece(square)) {
                            get_piece(square)->set_prise(true);
                        }

                        if (!echec(Blanc, true)) {
                            pionsb[i]->set_pos(pionb_i_pos, true);
                            if (get_piece(square)) {
                                get_piece(square)->set_prise(false);
                            }
                            return false;
                        }

                        if (get_piece(square)) {
                            get_piece(square)->set_prise(false);
                        }
                        pionsb[i]->set_pos(pionb_i_pos, true);
                    }
                }
            }
        }
        if (!test_pat)
            cout << ANSI_COLOR_RED << "Échec et mat joueur Blanc ! " << ANSI_COLOR_RESET << endl;
        else
            cout << endl << ANSI_COLOR_RED << "Pat !  Aucune pièce ne peut bouger sans mettre en échec le roi Blanc. " << ANSI_COLOR_RESET << endl;
    }
    return true;
}

void Echiquier::affiche() const {
    string space5 = string(7, ' ');
    bool prisen(false), priseb(false);
    cout << endl;

    /* Affichage des prises du joueur noir s'il y en a */
    for (int d(0); d < NBCOL; d++) {
        if (piecesb[d]->get_prise()) {
            if (!priseb)
                cout << endl << "   ";
            cout << ANSI_BACKGROUND_COLOR_WHITE << " " << piecesb[d]->affiche() << " " << ANSI_COLOR_RESET;
            priseb = true;
        }
        if (pionsb[d]->get_prise()) {
            if (!priseb)
                cout << endl << "   ";
            cout << ANSI_BACKGROUND_COLOR_WHITE << " " << pionsb[d]->affiche() << " " << ANSI_COLOR_RESET;
            priseb = true;
        }
    }
    if (priseb)
        cout << endl << endl;
    cout << "      a      b      c      d      e      f      g      h     " << endl << endl;
    for (int i(NBCOL - 1); i >= 0; i--) {
        /* Affichage du premier tiers de la case (pour la rendre carrée) */
        cout << "   ";
        for (int j(0); j < NBCOL; j++) {
            if (i % 2 != j % 2) {
                cout << ANSI_BACKGROUND_COLOR_GREY_WHITE << space5 << ANSI_COLOR_RESET; // 2 ascii spaces
            } else {
                cout << ANSI_BACKGROUND_COLOR_DARK_SQUARE << space5 << ANSI_COLOR_RESET; // 2 ascii spaces
            }
        }

        cout << endl << i + 1 << "  "; // numérotation ligne dans affichage
        for (int j(0); j < NBCOL; j++) {
            if (i % 2 != j % 2) {
                if (echiquier[i][j] && echiquier[i][j]->get_couleur() == Noir) {
                    cout << ANSI_BACKGROUND_COLOR_GREY_WHITE << "\u0020\u0020\u0020"; // U+0020 est un espace utf-8
                                                                                      // taille police
                    cout << ANSI_COLOR_BLACK << echiquier[i][j]->affiche() << ANSI_COLOR_RESET;
                    cout << ANSI_BACKGROUND_COLOR_GREY_WHITE << "\u0020\u0020"
                         << " " << ANSI_COLOR_RESET;
                } else if (echiquier[i][j] && echiquier[i][j]->get_couleur() == Blanc) {
                    cout << ANSI_BACKGROUND_COLOR_GREY_WHITE << "\u0020\u0020\u0020"; // U+0020 est un espace utf-8
                                                                                      // taille police
                    cout << echiquier[i][j]->affiche();
                    cout << "\u0020\u0020"
                         << " " << ANSI_COLOR_RESET;
                } else
                    cout << ANSI_BACKGROUND_COLOR_GREY_WHITE << space5 << ANSI_COLOR_RESET; // 2 ascii spaces
            } else {
                if (echiquier[i][j] && echiquier[i][j]->get_couleur() == Noir) {
                    cout << ANSI_BACKGROUND_COLOR_DARK_SQUARE << "\u0020\u0020\u0020"; // U+0020 est un espace utf-8
                                                                                       // taille police
                    cout << ANSI_COLOR_BLACK << echiquier[i][j]->affiche() << ANSI_COLOR_RESET;
                    cout << ANSI_BACKGROUND_COLOR_DARK_SQUARE << "\u0020\u0020"
                         << " " << ANSI_COLOR_RESET;
                } else if (echiquier[i][j] && echiquier[i][j]->get_couleur() == Blanc) {
                    cout << ANSI_BACKGROUND_COLOR_DARK_SQUARE << "\u0020\u0020\u0020"; // U+0020 est un espace utf-8
                                                                                       // taille police
                    cout << echiquier[i][j]->affiche();
                    cout << "\u0020\u0020"
                         << " " << ANSI_COLOR_RESET;
                } else
                    cout << ANSI_BACKGROUND_COLOR_DARK_SQUARE << space5 << ANSI_COLOR_RESET; // 2 ascii spaces
            }
        }

        /* Affichage du troisième tiers de la case */
        cout << endl << "   ";
        for (int j(0); j < NBCOL; j++) {
            if (i % 2 != j % 2) {
                cout << ANSI_BACKGROUND_COLOR_GREY_WHITE << space5 << ANSI_COLOR_RESET; // 2 ascii spaces
            } else {
                cout << ANSI_BACKGROUND_COLOR_DARK_SQUARE << space5 << ANSI_COLOR_RESET; // 2 ascii spaces
            }
        }
        cout << endl;
    }
    cout << endl;

    /* Affichage des prises du joueur blanc s'il y en a */
    cout << "   ";
    for (int d(0); d < NBCOL; d++) {
        if (piecesn[d]->get_prise()) {
            cout << ANSI_COLOR_BLACK << ANSI_BACKGROUND_COLOR_WHITE << " " << piecesn[d]->affiche() << " " << ANSI_COLOR_RESET;
            prisen = true;
        }
        if (pionsn[d]->get_prise()) {
            cout << ANSI_COLOR_BLACK << ANSI_BACKGROUND_COLOR_WHITE << " " << pionsn[d]->affiche() << " " << ANSI_COLOR_RESET;
            prisen = true;
        }
    }
    if (prisen)
        cout << endl << endl;
    else
        cout << "\r";
}

string Echiquier::pgn_piece_name(string type, Couleur couleur, bool view_pawn, bool view_color) const {
    string psymb;
    if (type == "Tour" && couleur == Blanc)
        psymb = "R"; // Rook R
    else if (type == "Cavalier" && couleur == Blanc)
        psymb = "N"; // Knight N
    else if (type == "Fou" && couleur == Blanc)
        psymb = "B"; // Bishop B
    else if (type == "Dame" && couleur == Blanc)
        psymb = "Q"; // Queen Q
    else if (type == "Roi" && couleur == Blanc)
        psymb = "K"; // King K
    else if (type == "Pion" && couleur == Blanc && view_pawn)
        psymb = "P"; // Pawn P

    if (psymb.size() > 0) { // one of the white piece has been found
        if (view_color)
            return "w" + psymb;
        else
            return psymb;
    }

    if (type == "Tour" && couleur == Noir)
        psymb = "R"; // Rook R
    else if (type == "Cavalier" && couleur == Noir)
        psymb = "N"; // Knight N
    else if (type == "Fou" && couleur == Noir)
        psymb = "B"; // Bishop B
    else if (type == "Dame" && couleur == Noir)
        psymb = "Q"; // Queen Q
    else if (type == "Roi" && couleur == Noir)
        psymb = "K"; // King K
    else if (type == "Pion" && couleur == Noir && view_pawn)
        psymb = "P"; // Pawn P

    if (psymb.size() > 0) { // one of the black piece has been found
        if (view_color)
            return "b" + psymb;
        else
            return psymb;
    } else
        return "";
}

string Echiquier::canonical_position() {
    string output;
    for (size_t row(1); row <= 8; row++) {
        for (char col('a'); col <= 'h'; col++) {
            Square square(col + to_string(row));
            if (get_piece(square))
                // get pieces with their PGN names,
                // true -> with P for pawns, true -> w/b for colors.
                output += pgn_piece_name(get_piece(square)->get_type(), get_piece(square)->get_couleur(), true, true);
            output += ",";
        }
    }
    return output;
}
