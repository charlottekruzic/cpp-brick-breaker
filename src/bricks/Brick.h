#ifndef BRICK_H
#define BRICK_H

#include <map>
#include <string>

#include "../Cell.h"

// #include "Game.h"

class Game;

// Classe représentant une brique
class Brick : public Cell {
 public:
  bool rebondir() const override;
  bool hit() override;

  int getStrength() const;  // Méthode pour obtenir la force de la brique
  int getHitsLeft() const;  // Méthode pour obtenir le nombre de coups restants
  Color getColor() override;

  // protected:
  Brick(int strength, Game* game);

 protected:
  Game* game_;    // Attribut pour stocker un pointeur vers l'objet Game
  int hitsLeft_;  // Nombre de coups restants

 private:
  int strength_;  // Force de la brique
  Color color_;   // protected .
  static std::map<int, Color>
      strengthColorMap_;  // Dictionnaire associant une force à une couleur
};

#endif  // BRICK_H
