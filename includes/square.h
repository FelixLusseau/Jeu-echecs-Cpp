#pragma once

#include <iostream>
#include <string>

using namespace std;

class Square {
  private:
    int ligne;
    int colonne;

  public:
    Square(string entree);
    Square(int ligne, int colonne);

    /**
     * @brief Renvoie la position sous forme de string. Ex : a3.
     *
     * @return string
     */
    string to_string();

    /**
     * @brief Retourne la ligne de la pièce.
     *
     * @return int
     */
    int get_ligne();

    /**
     * @brief Retourne la colonne de la pièce.
     *
     * @return int
     */
    int get_colonne();
};