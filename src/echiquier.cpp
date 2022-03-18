#include "echiquier.h"
#include "piece.h"
#include "square.h"

Echiquier::Echiquier() /* : bpromues(0), npromues(0) */ {
    for (int i = 0; i < NBCOL; i++) {
        for (int j = 0; j < NBCOL; j++) {
            echiquier[i][j] = nullptr;
        }
    }

    // Constructeur (Couleur,nom_affiché, case)
    piecesb[0] = new Tour(Blanc, "\u2656", Square(0, 0));
    piecesb[1] = new Cavalier(Blanc, "\u2658", Square(0, 1));
    piecesb[2] = new Fou(Blanc, "\u2657", Square(0, 2));
    piecesb[3] = new Dame(Blanc, "\u2655", Square(0, 3));
    piecesb[4] = new Roi(Blanc, "\u2654", Square(0, 4));
    piecesb[5] = new Fou(Blanc, "\u2657", Square(0, 5));
    piecesb[6] = new Cavalier(Blanc, "\u2658", Square(0, 6));
    piecesb[7] = new Tour(Blanc, "\u2656", Square(0, 7));
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
        pionsb[i] = new Pion(Blanc, "\u2659", Square(1, i));
        pionsn[i] = new Pion(Noir, "\u265F", Square(6, i));
    }
    // Pose des pieces en position initiale
    // pose des pieces blanches
    for (unsigned char i(0); i < NBCOL; i++) {
        // met à jour le tableau echiquier, à la case donnée par
        // la position courante de la pièce obtenue avec
        // piecesb[i]->get_pos(),
        // avec le pointeur vers la pièce (piecesb[i])
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
    /* for (unsigned char i(0); i < bpromues; i++) {
        delete promosb[i];
    }
    for (unsigned char i(0); i < npromues; i++) {
        delete promosn[i];
    } */
}

Piece *Echiquier::get_piece(Square pos) {
    return echiquier[pos.get_x()][pos.get_y()];
}

Piece *Echiquier::get_piece(int x, int y) { return echiquier[x][y]; }

void Echiquier::pose_piece(Piece *piece) {
    echiquier[piece->get_pos().get_x()][piece->get_pos().get_y()] = piece;
}

void Echiquier::deplace(Square orig, Square dest) {
    echiquier[dest.get_x()][dest.get_y()] =
        echiquier[orig.get_x()][orig.get_y()];
    echiquier[orig.get_x()][orig.get_y()] = nullptr;

    echiquier[dest.get_x()][dest.get_y()]->set_pos(dest);
}

void Echiquier::prise_en_passant(int x, int y) { echiquier[x][y] = nullptr; }

bool Echiquier::promotion(Couleur couleur, Square pos) {
    char piece_promue;
    cout << "Choisissez une pièce à restaurer parmi : Q, R, B, K : ";
    cin >> piece_promue;
    int pion_promu;
    if (couleur == Blanc) {
        for (pion_promu = 0; pion_promu < NBCOL; pion_promu++) {
            if (pionsb[pion_promu] == get_piece(pos)) {
                break;
            }
        }
        switch (piece_promue) {
        case 'Q':
            delete pionsb[pion_promu];
            pionsb[pion_promu] = new Dame(Blanc, "\u2655", pos);
            pose_piece(pionsb[pion_promu]);
            break;
        case 'R':
            delete pionsb[pion_promu];
            pionsb[pion_promu] = new Tour(Blanc, "\u2656", pos);
            pose_piece(pionsb[pion_promu]);
            break;
        case 'B':
            delete pionsb[pion_promu];
            pionsb[pion_promu] = new Fou(Blanc, "\u2657", pos);
            pose_piece(pionsb[pion_promu]);
            break;
        case 'K':
            delete pionsb[pion_promu];
            pionsb[pion_promu] = new Cavalier(Blanc, "\u2658", pos);
            pose_piece(pionsb[pion_promu]);
            break;
        default:
            cout << endl
                 << ANSI_COLOR_RED
                 << "Pièce sélectionnée invalide, veuillez réessayer ! "
                 << ANSI_COLOR_RESET << endl;
            return false;
        }
    } else {
        for (pion_promu = 0; pion_promu < NBCOL; pion_promu++) {
            if (pionsn[pion_promu] == get_piece(pos)) {
                break;
            }
        }
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
            cout << endl
                 << ANSI_COLOR_RED
                 << "Pièce sélectionnée invalide, veuillez réessayer ! "
                 << ANSI_COLOR_RESET << endl;
            return false;
        }
    }
    return true;
}

bool Echiquier::verif_saut(Square &orig, Square &dest, bool test_echec) {
    int xorig(orig.get_x()), xdest(dest.get_x()), yorig(orig.get_y()),
        ydest(dest.get_y()), dx, dy;
    if (get_piece(xorig, yorig)->get_type() == "Cavalier" ||
        get_piece(xorig, yorig)->get_type() == "Roi")
        return true;
    if (xorig - xdest == 0) {
        (yorig < ydest) ? dy = 1 : dy = -1;
        for (int k(yorig + dy); k != ydest; k += dy) {
            if (get_piece(xorig, k)) {
                if (!test_echec)
                    cout << endl
                         << ANSI_COLOR_RED
                         << "Vous sautez une pièce, veuillez "
                            "réessayer ! "
                         << ANSI_COLOR_RESET << endl;
                return false;
            }
        }
        return true;
    } else if (yorig - ydest == 0) {
        (xorig < xdest) ? dx = 1 : dx = -1;
        for (int k(xorig + dx); k != xdest; k += dx) {
            if (get_piece(k, yorig)) {
                if (!test_echec)
                    cout << endl
                         << ANSI_COLOR_RED
                         << "Vous sautez une pièce, veuillez "
                            "réessayer ! "
                         << ANSI_COLOR_RESET << endl;
                return false;
            }
        }
        return true;

    } else {
        (xorig < xdest) ? dx = 1 : dx = -1;
        (yorig < ydest) ? dy = 1 : dy = -1;
        for (int k(xorig + dx); k != xdest; k += dx) {
            for (int l(yorig + dy); l != ydest; l += dy) {
                if (get_piece(k, l)) {
                    if (!test_echec)
                        cout << endl
                             << ANSI_COLOR_RED
                             << "Vous sautez une pièce, veuillez "
                                "réessayer ! "
                             << ANSI_COLOR_RESET << endl;
                    return false;
                }
                k += dx;
            }
            break;
        }
        return true;
    }
}

bool Echiquier::echec(Couleur couleur, bool test_echec_et_mat) {
    if (couleur == Blanc) {
        /* cout << "roi en cours : " << piecesn[4]->affiche() << endl; */
        Square roi_n_pos = piecesn[4]->get_pos();
        for (int i(0); i < NBCOL; i++) {
            Square pieceb_i_pos = piecesb[i]->get_pos();
            Square pionb_i_pos = pionsb[i]->get_pos();
            /* cout << piecesb[i]->affiche()
                 << piecesb[i]->est_mouvement_legal(pieceb_i_pos.to_string(),
                                                    roi_n_pos.to_string())
                 << " pièce n : " << pieceb_i_pos.to_string()
                 << " roi n : " << roi_n_pos.to_string()
                 << piecesn[4]->affiche() << endl; */
            /* cout << pionsb[i]->affiche()
                 << pionsb[i]->est_mouvement_legal(pionb_i_pos.to_string(),
                                                   roi_n_pos.to_string())
                 << " pion b " << i << " : " << pionb_i_pos.to_string()
                 << " roi n : " << roi_n_pos.to_string()
                 << piecesn[4]->affiche() << endl; */
            if (!piecesb[i]->get_prise() &&
                piecesb[i]->est_mouvement_legal(pieceb_i_pos.to_string(),
                                                roi_n_pos.to_string()) &&
                verif_saut(pieceb_i_pos, roi_n_pos, true)) {
                if (!test_echec_et_mat)
                    cout << ANSI_COLOR_RED << "Echec noir ! "
                         << ANSI_COLOR_RESET << piecesb[i]->get_type() << " "
                         << piecesb[i]->affiche() << " sur "
                         << piecesn[4]->affiche() << endl;
                return true;
            } else if (!pionsb[i]->get_prise() &&
                       pionsb[i]->est_mouvement_legal(pionb_i_pos.to_string(),
                                                      roi_n_pos.to_string()) &&
                       verif_saut(pionb_i_pos, roi_n_pos, true)) {
                if (pionsb[i]->affiche() == "\u2659" &&
                    pionb_i_pos.get_y() - roi_n_pos.get_y() == 0) {
                    return false;
                }
                if (!test_echec_et_mat)
                    cout << ANSI_COLOR_RED << "Echec noir ! "
                         << ANSI_COLOR_RESET << pionsb[i]->get_type() << " "
                         << pionsb[i]->affiche() << " sur "
                         << piecesn[4]->affiche() << endl;
                return true;
            }
        }
    } else {
        /* cout << "roi en cours : " << piecesb[4]->affiche() << endl; */
        Square roi_b_pos = piecesb[4]->get_pos();
        for (int i(0); i < NBCOL; i++) {
            Square piecen_i_pos = piecesn[i]->get_pos();
            Square pionn_i_pos = pionsn[i]->get_pos();
            /* cout << piecesn[i]->affiche()
                 << piecesn[i]->est_mouvement_legal(piecen_i_pos.to_string(),
                                                    roi_b_pos.to_string())
                 << " pièce n : " << piecen_i_pos.to_string()
                 << " roi b : " << roi_b_pos.to_string()
                 << piecesb[4]->affiche() << endl; */
            /* cout << pionsn[i]->affiche()
                 << pionsn[i]->est_mouvement_legal(pionn_i_pos.to_string(),
                                                   roi_b_pos.to_string())
                 << " pion n " << i << " : " << pionn_i_pos.to_string()
                 << " roi b : " << roi_b_pos.to_string()
                 << piecesb[4]->affiche() << endl; */
            if (!piecesn[i]->get_prise() &&
                piecesn[i]->est_mouvement_legal(piecen_i_pos.to_string(),
                                                roi_b_pos.to_string()) &&
                verif_saut(piecen_i_pos, roi_b_pos, true)) {
                if (!test_echec_et_mat)
                    cout << ANSI_COLOR_RED << "Echec blanc ! "
                         << ANSI_COLOR_RESET << piecesn[i]->get_type() << " "
                         << piecesn[i]->affiche() << " sur "
                         << piecesb[4]->affiche() << endl;
                return true;
            } else if (!pionsn[i]->get_prise() &&
                       pionsn[i]->est_mouvement_legal(pionn_i_pos.to_string(),
                                                      roi_b_pos.to_string()) &&
                       verif_saut(pionn_i_pos, roi_b_pos, true)) {
                if (pionsn[i]->affiche() == "\u265F" &&
                    pionn_i_pos.get_y() - roi_b_pos.get_y() == 0) {
                    return false;
                }
                if (!test_echec_et_mat)
                    cout << ANSI_COLOR_RED << "Echec blanc ! "
                         << ANSI_COLOR_RESET << pionsn[i]->get_type() << " "
                         << pionsn[i]->affiche() << " sur "
                         << piecesb[4]->affiche() << endl;
                return true;
            }
        }
    }
    return false;
}

bool Echiquier::mat(Couleur couleur) {
    if (couleur == Blanc) {
        for (int i(0); i < NBCOL; i++) {

            Square piecen_i_pos = piecesn[i]->get_pos();
            Square pionn_i_pos = pionsn[i]->get_pos();

            for (size_t row(1); row <= 8; row++) {
                for (char col('a'); col <= 'h'; col++) {
                    string str(col + to_string(row));
                    Square square(str);
                    /* cout << str << piecesn[i]->affiche()
                         << !piecesn[i]->get_prise()
                         << piecesn[i]->est_mouvement_legal(
                                piecen_i_pos.to_string(), str)
                         << verif_saut(piecen_i_pos, square, true)
                         << !echec(couleur, false) << endl; */
                    /* cout << str << piecesn[i]->affiche()
                         << !piecesn[i]->get_prise()
                         << piecesn[i]->est_mouvement_legal(
                                piecen_i_pos.to_string(), str)
                         << verif_saut(piecen_i_pos, square, true)
                         << "pièce dest ? " << get_piece(square)
                         << " couleur : "
                         << (get_piece(square)
                                 ? get_piece(square)->get_couleur()
                                 : 2)
                         << couleur << endl; */
                    cout << str << pionsn[i]->affiche()
                         << !pionsn[i]->get_prise()
                         << pionsn[i]->est_mouvement_legal(
                                pionn_i_pos.to_string(), str)
                         << verif_saut(pionn_i_pos, square, true)
                         << " pièce dest ? " << get_piece(square)
                         << " couleur : "
                         << (get_piece(square)
                                 ? get_piece(square)->get_couleur()
                                 : 2)
                         << couleur << endl;
                    if (!piecesn[i]->get_prise() &&
                        piecesn[i]->est_mouvement_legal(
                            piecen_i_pos.to_string(), str) &&
                        verif_saut(piecen_i_pos, square, true) &&
                        ((get_piece(square) &&
                          (get_piece(square)->get_couleur() == couleur)) ||
                         !get_piece(square))) {
                        piecesn[i]->set_pos(square);
                        if (get_piece(square)) {
                            get_piece(square)->set_prise(true);
                        }
                        // cout << piecesn[i]->affiche() << str << endl;
                        if (!echec(couleur, true)) {
                            piecesn[i]->set_pos(piecen_i_pos);
                            if (get_piece(square)) {
                                get_piece(square)->set_prise(false);
                            }
                            return false;
                        }
                        if (get_piece(square)) {
                            get_piece(square)->set_prise(false);
                        }
                        piecesn[i]->set_pos(piecen_i_pos);

                    } else if (!pionsn[i]->get_prise() &&
                               pionsn[i]->est_mouvement_legal(
                                   piecen_i_pos.to_string(), str) &&
                               verif_saut(pionn_i_pos, square, true) &&
                               ((get_piece(square) &&
                                 (get_piece(square)->get_couleur() ==
                                  couleur)) ||
                                !get_piece(square))) {
                        pionsn[i]->set_pos(square);
                        if (get_piece(square)) {
                            get_piece(square)->set_prise(true);
                        }
                        // cout << pionsn[i]->affiche() << str << endl;
                        if (!echec(couleur, true)) {
                            pionsn[i]->set_pos(pionn_i_pos);
                            if (get_piece(square)) {
                                get_piece(square)->set_prise(false);
                            }
                            return false;
                        }
                        if (get_piece(square)) {
                            get_piece(square)->set_prise(false);
                        }
                        pionsn[i]->set_pos(pionn_i_pos);
                    }
                }
            }
        }
        cout << ANSI_COLOR_RED << "Echec et mat joueur Noir ! "
             << ANSI_COLOR_RESET << endl;
    } else {
        for (int i(0); i < NBCOL; i++) {
            Square pieceb_i_pos = piecesb[i]->get_pos();
            Square pionb_i_pos = pionsb[i]->get_pos();

            for (size_t row(1); row <= 8; row++) {
                for (char col('a'); col <= 'h'; col++) {
                    string str(col + to_string(row));
                    Square square(str);
                    cout << str << piecesb[i]->affiche()
                         << !piecesb[i]->get_prise()
                         << piecesb[i]->est_mouvement_legal(
                                pieceb_i_pos.to_string(), str)
                         << verif_saut(pieceb_i_pos, square, true)
                         << "pièce dest ? " << get_piece(square)
                         << " couleur : "
                         << (get_piece(square)
                                 ? get_piece(square)->get_couleur()
                                 : 2)
                         << couleur << endl;
                    if (!piecesb[i]->get_prise() &&
                        piecesb[i]->est_mouvement_legal(
                            pieceb_i_pos.to_string(), str) &&
                        verif_saut(pieceb_i_pos, square, true) &&
                        ((get_piece(square) &&
                          (get_piece(square)->get_couleur() == couleur)) ||
                         !get_piece(square))) {
                        piecesb[i]->set_pos(square);
                        if (get_piece(square)) {
                            get_piece(square)->set_prise(true);
                        }
                        // cout << "ss " << !echec(couleur, false) << endl;
                        //  cout << piecesb[i]->affiche() << str << endl;
                        if (!echec(couleur, true)) {
                            piecesb[i]->set_pos(pieceb_i_pos);
                            if (get_piece(square)) {
                                get_piece(square)->set_prise(false);
                            }
                            return false;
                        }
                        if (get_piece(square)) {
                            get_piece(square)->set_prise(false);
                        }
                        piecesb[i]->set_pos(pieceb_i_pos);
                    } else if (!pionsb[i]->get_prise() &&
                               pionsb[i]->est_mouvement_legal(
                                   pieceb_i_pos.to_string(), str) &&
                               verif_saut(pionb_i_pos, square, true) &&
                               ((get_piece(square) &&
                                 (get_piece(square)->get_couleur() ==
                                  couleur)) ||
                                !get_piece(square))) {
                        pionsb[i]->set_pos(square);
                        if (get_piece(square)) {
                            get_piece(square)->set_prise(true);
                        }
                        // cout << pionsb[i]->affiche() << str << endl;
                        if (!echec(couleur, true)) {
                            pionsb[i]->set_pos(pionb_i_pos);
                            if (get_piece(square)) {
                                get_piece(square)->set_prise(false);
                            }
                            return false;
                        }
                        if (get_piece(square)) {
                            get_piece(square)->set_prise(false);
                        }
                        pionsb[i]->set_pos(pionb_i_pos);
                    }
                }
            }
        }
        cout << ANSI_COLOR_RED << "Echec et mat joueur Blanc ! "
             << ANSI_COLOR_RESET << endl;
    }
    return true;
}

void Echiquier::affiche() const {
    string space5 = string(5, ' ');
    cout << endl;
    cout << "     a     b     c     d     e     f     g     h    " << endl;
    cout << "  +-----+-----+-----+-----+-----+-----+-----+-----+" << endl;
    for (int i(NBCOL - 1); i >= 0; i--) {
        cout << i + 1 << " "; // numérotation ligne dans affichage
        for (int j(0); j < NBCOL; j++) {
            cout << "|";
            if (echiquier[i][j]) {
                cout << "\u0020\u0020"; // U+0020 est un esapce utf-8 taille
                                        // police
                cout << echiquier[i][j]->affiche();
                cout << "\u0020"
                     << " ";
            } else
                cout << space5; // 2 ascii spaces
        }
        cout << "|\n  +-----+-----+-----+-----+-----+-----+-----+-----+";
        cout << endl;
    }
}

string Echiquier::pgn_piece_name(string name, bool view_pawn,
                                 bool view_color) const {

    string psymb;
    if (name == "\u2656")
        psymb = "R"; // Rook W
    else if (name == "\u2658")
        psymb = "N"; // Knight W
    else if (name == "\u2657")
        psymb = "B"; // Bishop W
    else if (name == "\u2655")
        psymb = "Q"; // Queen W
    else if (name == "\u2654")
        psymb = "K"; // King W
    else if (name.rfind("\u2659", 0) == 0 && view_pawn)
        psymb = "P";        // Pawn W
    if (psymb.size() > 0) { // one of the white piece has been found
        if (view_color)
            return "w" + psymb;
        else
            return psymb;
    }
    if (name == "\u265C")
        psymb = "R"; // Rook B
    else if (name == "\u265E")
        psymb = "N"; // Knight B
    else if (name == "\u265D")
        psymb = "B"; // Bishop B
    else if (name == "\u265B")
        psymb = "Q"; // Queen B
    else if (name == "\u265A")
        psymb = "K"; // King B
    else if (name.rfind("\u265F", 0) == 0 && view_pawn)
        psymb = "P";        // Pawn B
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
                // get pieces with theit PGN names,
                // true -> with P for pawns, true -> w/b for colors.
                output +=
                    pgn_piece_name(get_piece(square)->to_string(), true, true);
            output += ",";
        }
    }
    return output;
}