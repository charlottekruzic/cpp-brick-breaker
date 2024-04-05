#include "Wall.h"

Wall::Wall() : Cell(Color::Yellow) {}

bool Wall::rebondir() const {
  return true;  // Les objets rebondissent sur les murs
}

bool Wall::traverse() const {
  return false;  // Les murs ne sont pas traversables
}
