#pragma once
#include <string>

enum Couleur { Noir, Blanc };
const std::string ANSI_COLOR_RED = "\x1b[31m";
const std::string ANSI_COLOR_GREEN = "\x1b[32m";
const std::string ANSI_COLOR_YELLOW = "\x1b[33m";
const std::string ANSI_COLOR_RESET = "\x1b[0m";
