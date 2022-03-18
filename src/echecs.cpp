#include <iostream>
#include <regex>

#include "couleur.h"
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

int main() {
    Jeu monjeu; // initialise le jeu
    string mouvement, coup_prec;
    Couleur couleur = Blanc;
    bool stop(false);
    bool roqueb(false), roquen(false);
    bool deplace_ok(true);
    bool echec(false);
    Couleur couleur_echec;
    monjeu.affiche();
    cout << "Exemple de coup : a1a8 (et attention aux couleurs inversées)"
         << endl;
    do {
        coup_prec = mouvement;
        // cout << "cout prec : " << coup_prec << endl;
        if (couleur == Noir)
            cout << "Coup Noir : ";
        else
            cout << "Coup Blanc : ";
        cin >> mouvement;
        if (mouvement != "/quit") {
            if (saisie_correcte_grandroque(mouvement)) {
                if ((couleur == Noir && roquen) ||
                    (couleur == Blanc && roqueb)) {
                    cout << endl
                         << ANSI_COLOR_RED
                         << "Impossible de réaliser le grand roque, un roque a "
                            "déjà été effectué pour votre couleur, veuillez "
                            "réessayer ! "
                         << ANSI_COLOR_RESET << endl;
                    continue;
                } else if (monjeu.grand_roque(couleur)) {
                    cout << "Grand roque effectué ! " << endl;
                    couleur ? roqueb = true : roquen = true;
                } else
                    continue;
            } else if (saisie_correcte_petitroque(mouvement)) {
                if ((couleur == Noir && roquen) ||
                    (couleur == Blanc && roqueb)) {
                    cout << endl
                         << ANSI_COLOR_RED
                         << "Impossible de réaliser le petit roque, un roque a "
                            "déjà été effectué pour votre couleur, veuillez "
                            "réessayer ! "
                         << ANSI_COLOR_RESET << endl;
                    continue;
                } else if (monjeu.petit_roque(couleur)) {
                    cout << "Petit roque effectué ! " << endl;
                    couleur ? roqueb = true : roquen = true;
                } else
                    continue;
            } else {

                if (!saisie_correcte(mouvement))
                    continue;
                // découper case origine et destination
                string orig = mouvement.substr(0, 2);
                string dest = mouvement.substr(2, 2);

                deplace_ok = monjeu.deplace(couleur, orig, dest, coup_prec);
                if (deplace_ok == false)
                    continue;
                // cout << "echec : " << echec << endl;
                if (echec) {
                    if (monjeu.test_echec(couleur_echec, false)) {
                        // monjeu.deplace(couleur, dest, orig, coup_prec);
                        cout << endl
                             << ANSI_COLOR_RED
                             << "Votre roi est toujours en échec, veuillez "
                                "réessayer ! "
                             << ANSI_COLOR_RESET << endl;
                        continue;
                    } else
                        echec = false;
                }
            }

            monjeu.affiche();

            if (monjeu.test_echec(couleur, false)) {
                echec = true;
                couleur_echec = couleur;
                if (monjeu.test_mat(couleur))
                    break;
            }
            if (couleur == Blanc)
                couleur = Noir;
            else
                couleur = Blanc;
        } else
            stop = true;
    } while (!stop);
    monjeu.fin_de_partie();
}