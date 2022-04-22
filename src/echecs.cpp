#include <iostream>
#include <queue>
#include <regex>

#include "couleur.h"
#include "echecs.h"
#include "jeu.h"

using namespace std;

//--------------------------------------------------------------

bool saisie_correcte(string const &cmd) {
    regex mouvmtpattern("[a-h][1-8][a-h][1-8]");
    return regex_match(cmd, mouvmtpattern);
}

bool saisie_correcte_petitroque(string const &cmd) {
    regex mouvmtpattern("(O|o|0)-(O|o|0)");
    return regex_match(cmd, mouvmtpattern);
}

bool saisie_correcte_grandroque(string const &cmd) {
    regex mouvmtpattern("(O|o|0)-(O|o|0)-(O|o|0)");
    return regex_match(cmd, mouvmtpattern);
}

bool grand_roque(Jeu *monjeu, Couleur couleur, bool *roqueb, bool *roquen) {
    if ((couleur == Noir && *roquen) || (couleur == Blanc && *roqueb)) {
        cout << endl << ANSI_COLOR_RED << "Impossible de réaliser le grand roque, un roque a déjà été effectué pour votre couleur, veuillez réessayer ! " << ANSI_COLOR_RESET << endl;
        return false;
    } else if (monjeu->grand_roque(couleur)) {
        cout << ANSI_COLOR_GREEN << "Grand roque effectué ! " << ANSI_COLOR_RESET << endl;
        couleur ? *roqueb = true : *roquen = true;
        return true;
    } else
        return false;
}

bool petit_roque(Jeu *monjeu, Couleur couleur, bool *roqueb, bool *roquen) {
    if ((couleur == Noir && *roquen) || (couleur == Blanc && *roqueb)) {
        cout << endl << ANSI_COLOR_RED << "Impossible de réaliser le petit roque, un roque a déjà été effectué pour votre couleur, veuillez réessayer ! " << ANSI_COLOR_RESET << endl;
        return false;
    } else if (monjeu->petit_roque(couleur)) {
        cout << ANSI_COLOR_GREEN << "Petit roque effectué ! " << ANSI_COLOR_RESET << endl;
        couleur ? *roqueb = true : *roquen = true;
        return true;
    } else
        return false;
}

bool gestion_fifo(queue<string> &fifo, Jeu *monjeu) {
    fifo.push(monjeu->canonical_position());

    /* Conserve uniquement les 9 derniers échiquiers */
    if (fifo.size() > 9)
        fifo.pop();

    /* Lorsque suffisamment de coups ont été joués, regarde si le premier et le dernier échiquier sont identiques,
    puis si oui regarde l'échiquier intermédiaire en dépilant sur une copie de la file. */
    if (fifo.size() == 9) {
        if (fifo.front() == fifo.back()) {
            queue<string> copie_fifo = fifo;

            for (int i = 1; i <= 4; i++)
                copie_fifo.pop();

            if (copie_fifo.front() == copie_fifo.back()) {
                cout << endl << ANSI_COLOR_RED << "Pat ! Règle des 3 positions identiques ! " << ANSI_COLOR_RESET << endl;
                return true;
            }
        }
    }
    return false;
}

int main() {
    Jeu monjeu; // initialise le jeu
    string mouvement, coup_prec;
    queue<string> echiquer_canonique;
    Couleur couleur = Blanc;
    bool stop(false), pat(false), prise_ou_pion(false);
    bool roqueb(false), roquen(false);
    bool deplace_ok(true);
    int compteur(0);

    monjeu.affiche();
    cout << "Exemple de coup : a2a4" << endl;

    /* Boucle du jeu */
    do {
        /* Vérification du pat ou du mat en cas d'échec au début du tour */
        if (monjeu.test_echec(couleur, false)) {
            if (monjeu.test_mat(couleur))
                break;
        } else if (monjeu.test_pat(couleur, compteur)) {
            pat = true;
            break;
        }

        cout << "Coup " << (couleur ? "Blanc" : "Noir") << " : ";
        if (!getline(cin, mouvement)) {
            stop = true;
            break;
        }

        if (mouvement != "/quit") {
            if (saisie_correcte_grandroque(mouvement)) {
                if (!grand_roque(&monjeu, couleur, &roqueb, &roquen))
                    continue;
            } else if (saisie_correcte_petitroque(mouvement)) {
                if (!petit_roque(&monjeu, couleur, &roqueb, &roquen))
                    continue;
            } else {

                if (!saisie_correcte(mouvement))
                    continue;
                /* découper case origine et destination */
                string orig = mouvement.substr(0, 2);
                string dest = mouvement.substr(2, 2);

                deplace_ok = monjeu.jeu(couleur, orig, dest, coup_prec, &prise_ou_pion);
                if (deplace_ok == false) {
                    continue;
                }

                /* Vérification de l'absence de 3 échiquiers identiques de suite */
                if (gestion_fifo(echiquer_canonique, &monjeu)) {
                    pat = true;
                    break;
                }
            }

            /* Vérification de la règle des 50 coups */
            if (!prise_ou_pion)
                compteur++;
            else {
                prise_ou_pion = false;
                compteur = 0;
            }

            coup_prec = mouvement;

            monjeu.affiche();

            /* Changement de couleur */
            if (couleur == Blanc)
                couleur = Noir;
            else
                couleur = Blanc;

        } else
            stop = true;
    } while (!stop);

    /* Affichage de fin de partie */
    monjeu.fin_de_partie(couleur, stop, pat);
}