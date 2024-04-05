#include "Brick.h"

Brick::Brick(int strength, Color color)
    : Cell(color), strength_(strength), hitsLeft_(strength) {}

bool Brick::rebondir() const {
  return true;  // Les objets rebondissent sur une brique
}

bool Brick::traverse() const {
  return false;  // Les objets ne peuvent pas traverser une brique
}

int Brick::getStrength() const {
  return strength_;  // Renvoie la force de la brique
}

int Brick::getHitsLeft() const {
  return hitsLeft_;  // Renvoie le nombre de coups restants
}

void Brick::ballHit() { hitsLeft_--; }
