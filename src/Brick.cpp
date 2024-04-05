#include "Brick.h"

Brick::Brick(Color color, int strength, std::string type)
    : Cell(color), strength_(strength), hitsLeft_(strength), type_(type) {}

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

std::string Brick::getType() const { return type_; }

void Brick::renderCell(SDL_Renderer* renderer, int x, int y, int cellSize) {
  int padding = 1;  // Espace entre chaque case
  int size = cellSize - 2 * padding;
  // Taille effective de la case avec l'espace
  SDL_Rect rect = {x + padding, y + padding, size, size};
  // Utilise les coordonnées et la taille du carré avec l'espace
  SDL_Color color = ColorUtils::convertColor(getColor());
  SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
  SDL_RenderFillRect(renderer, &rect);
}
