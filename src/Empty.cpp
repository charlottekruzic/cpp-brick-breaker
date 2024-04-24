#include "Empty.h"

Empty::Empty() : Cell() {}

bool Empty::rebondir() const {
  return false;  // Les objets ne rebondissent pas sur une case vide
}

bool Empty::hit() { return true; }

void Empty::renderCell(SDL_Renderer* renderer, int x, int y, int cellSize) {}
