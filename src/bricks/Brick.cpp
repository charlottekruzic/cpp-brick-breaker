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

Color Brick::getColor() {
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
