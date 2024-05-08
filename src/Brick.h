#ifndef BRICK_H
#define BRICK_H

#include <map>
#include <string>

#include "Cell.h"
#include "Colors.h"

// Classe représentant une brique
class Brick : public Cell {
 public:
  bool rebondir() const override;
  bool hit() override;
  void renderCell(SDL_Renderer* renderer, int x, int y, int cellWidth) override;

  int getStrength() const;  // Méthode pour obtenir la force de la brique
  int getHitsLeft() const;  // Méthode pour obtenir le nombre de coups restants
  void ballHit();  // Méthode pour réduire le nombre de coups restants
                   // lorsqu'une balle touche la brique
  Color getColor() override;

  // protected:
  Brick(int strength);

 private:
  int strength_;  // Force de la brique
  int hitsLeft_;  // Nombre de coups restants
  Color color_;   // protected .
  static std::map<int, Color>
      strengthColorMap_;  // Dictionnaire associant une force à une couleur
};

#endif  // BRICK_H
