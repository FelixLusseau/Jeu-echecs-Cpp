#pragma once

#include <iostream>
#include <string>

using namespace std;

/**
 * @brief Classe codant une case stockée dans la pièce contenant la position, la
 * convertissant depuis un string vers des coordonnées et inversement.
 *
 */
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
    string to_string() const;

    /**
     * @brief Donne la ligne de la pièce.
     *
     * @return int
     */
    int get_ligne() const;

    /**
     * @brief Donne la colonne de la pièce.
     *
     * @return int
     */
    int get_colonne() const;
};
