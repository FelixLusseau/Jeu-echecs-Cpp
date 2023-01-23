#pragma once
#include <string>

/* Couleurs pour les pièces dans le jeu */
enum Couleur { Noir, Blanc };

/* Couleurs d'affichage du texte et des pièces */
const std::string ANSI_COLOR_BLACK = "\x1b[30m";
const std::string ANSI_COLOR_RED = "\x1b[31m";
const std::string ANSI_COLOR_GREEN = "\x1b[32m";

/* Couleurs d'arrière-plan pour l'échiquier et les pièces prises */
#ifndef OSX
const std::string ANSI_BACKGROUND_COLOR_DARK_SQUARE = "\x1b[48;2;88;45;0m";
const std::string ANSI_BACKGROUND_COLOR_GREY_WHITE = "\x1b[48;2;129;137;137m";
#else
const std::string ANSI_BACKGROUND_COLOR_DARK_SQUARE = "\x1b[48;5;236m";
const std::string ANSI_BACKGROUND_COLOR_GREY_WHITE = "\x1b[48;5;243m";
#endif
const std::string ANSI_BACKGROUND_COLOR_WHITE = "\x1b[48;5;245m";
/* Réinitialisation de toute coloration */
const std::string ANSI_COLOR_RESET = "\x1b[0m";
