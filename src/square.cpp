#include "square.h"

Square::Square(string entree) : x(entree[1] - '1'), y(entree[0] - 'a') {
    // cout << "constructeur string : x : " << x << ", y : " << y << endl;
}
Square::Square(int x, int y) : x(x), y(y) {}

string Square::to_string() {
    char y_lettre = y + 'a';
    string s;
    s += y_lettre;
    s += std::to_string(x + 1);
    return s;
}
int Square::get_x() { return x; }
int Square::get_y() { return y; }