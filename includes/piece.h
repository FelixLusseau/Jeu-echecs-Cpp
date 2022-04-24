#pragma once

#include <string>

#include "couleur.h"
#include "square.h"

#define NBCOL 8

using namespace std;

/**
 * @brief Classe virtuelle codant les méthodes et attributs communs à toutes les pièces.
 *
 */
class Piece {
  protected:
    string nom;
    Couleur couleur;
    Square position;
    bool a_bouge;
    bool prise;

  public:
    Piece(Couleur couleur, string nom, Square position);

    virtual ~Piece();

    /**
     * @brief Affiche la pièce à l'aide de son code UTF-8.
     *
     * @return string
     */
    string affiche() const;

    /**
     * @brief Vérifie si le mouvement est autorisé dans un échiquier vide.
     *
     * @param case_orig
     * @param case_dest
     * @return true
     * @return false
     */
    virtual bool est_mouvement_legal(string case_orig, string case_dest) const = 0;

    /**
     * @brief Renvoie la position de la pièce sous forme de Square.
     *
     * @return Square
     */
    Square get_pos() const;

    /**
     * @brief Met à jour la position de la pièce lors d'un mouvement.
     *
     * @param pos
     * @param test_mat
     */
    void set_pos(Square pos, bool test_mat);

    /**
     * @brief Donne la couleur de la pièce.
     *
     * @return Couleur
     */
    Couleur get_couleur() const;

    /**
     * @brief Donne le type de la pièce (Tour, Roi, etc...)
     *
     * @return string
     */
    virtual string get_type() const = 0;

    /**
     * @brief Permet de savoir si la pièce a été déplacée (roi et tour pour le roque).
     *
     * @return true
     * @return false
     */
    bool get_a_bouge() const;

    /**
     * @brief Renvoie si la pièce a été prise ou non.
     *
     * @return true
     * @return false
     */
    bool get_prise() const;

    /**
     * @brief Met à jour le booléen de prise dans la pièce.
     *
     * @param flag
     */
    void set_prise(bool flag);
};

/**
 * @brief Classe codant les attributs et méthodes spécifiques à la Tour.
 *
 */
class Tour : public Piece {

  public:
    Tour(Couleur couleur, string nom, Square position);

    bool est_mouvement_legal(string case_orig, string case_dest) const;

    string get_type() const;
};

/**
 * @brief Classe codant les attributs et méthodes spécifiques au Cavalier.
 *
 */
class Cavalier : public Piece {

  public:
    Cavalier(Couleur couleur, string nom, Square position);

    bool est_mouvement_legal(string case_orig, string case_dest) const;

    string get_type() const;
};

/**
 * @brief Classe codant les attributs et méthodes spécifiques au Fou.
 *
 */
class Fou : public Piece {

  public:
    Fou(Couleur couleur, string nom, Square position);

    bool est_mouvement_legal(string case_orig, string case_dest) const;

    string get_type() const;
};

/**
 * @brief Classe codant les attributs et méthodes spécifiques à la Dame.
 *
 */
class Dame : public Piece {

  public:
    Dame(Couleur couleur, string nom, Square position);

    bool est_mouvement_legal(string case_orig, string case_dest) const;

    string get_type() const;
};

/**
 * @brief Classe codant les attributs et méthodes spécifiques au Roi.
 *
 */
class Roi : public Piece {

  public:
    Roi(Couleur couleur, string nom, Square position);

    bool est_mouvement_legal(string case_orig, string case_dest) const;

    string get_type() const;
};

/**
 * @brief Classe codant les attributs et méthodes spécifiques au Pion.
 *
 */
class Pion : public Piece {

  public:
    Pion(Couleur couleur, string nom, Square position);

    bool est_mouvement_legal(string case_orig, string case_dest) const;

    string get_type() const;
};