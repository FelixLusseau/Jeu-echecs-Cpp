#pragma once

#include <iostream>
#include <string>

using namespace std;

class Square {
  private:
    int x;
    int y;

  public:
    Square(string entree);
    Square(int x, int y);

    string to_string();
    int get_x();
    int get_y();
};