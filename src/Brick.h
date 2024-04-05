#ifndef BRICK_H
#define BRICK_H

#include <string>

#include "Cell.h"

// Classe représentant une brique
class Brick : public Cell {
 public:
  Brick(int strength, Color color);
  bool rebondir() const override;
  bool traverse() const override;
  int getStrength() const;  // Méthode pour obtenir la force de la brique
  int getHitsLeft() const;  // Méthode pour obtenir le nombre de coups restants
  const std::string& getColor() const;
  // Méthode pour obtenir la couleur de la brique
  void ballHit();  // Méthode pour réduire le nombre de coups restants
                   // lorsqu'une balle touche la brique

 private:
  int strength_;  // Force de la brique
  int hitsLeft_;  // Nombre de coups restants
};

#endif  // BRICK_H
