#include "Brick.h"

#include <memory>

std::map<int, Color> Brick::strengthColorMap_ = {{1, Color::Green},
                                                 {2, Color::Yellow},
                                                 {3, Color::Orange},
                                                 {4, Color::Red},
                                                 {5, Color::Purple}};

Brick::Brick(int strength, Game* game)
    : strength_(strength), hitsLeft_(strength), game_(game) {}

bool Brick::rebondir() const {
  return (hitsLeft_ > 0);  // Les objets rebondissent sur une brique
}

int Brick::getStrength() const {
  return strength_;  // Renvoie la force de la brique
}

int Brick::getHitsLeft() const {
  return hitsLeft_;  // Renvoie le nombre de coups restants
}

Color Brick::getColor() const {
  auto it = strengthColorMap_.find(hitsLeft_);
  if (it != strengthColorMap_.end()) {
    return it->second;  // Retourne la couleur associée à la force de la brique
  } else {
    // Gérer le cas où la force n'est pas trouvée dans le dictionnaire
    return Color::DEFAULT_COLOR;
  }
}

// retourne vrai si détruit
bool Brick::hit() {
  if (hitsLeft_ > 0) {
    hitsLeft_--;
  }
  if (hitsLeft_ == 0) {
    return true;
  }
  // std::cout << "-1 vie mais en vie" << std::endl;
  return false;
}

// idem à Cell
void Brick::renderCell(std::shared_ptr<SDL_Renderer>& renderer, int x, int y,
                       int cellWidth, int cellHeight) {
  int padding = 1;  // Espace entre chaque case
  int size = cellWidth - 2 * padding;
  // Taille effective de la case avec l'espace
  SDL_Rect rect = {x + padding, y + padding, size, size};
  // Utilise les coordonnées et la taille du carré avec l'espace
  SDL_Color color = ColorUtils::convertColor(getColor());
  SDL_SetRenderDrawColor(renderer.get(), color.r, color.g, color.b, color.a);
  SDL_RenderFillRect(renderer.get(), &rect);
}