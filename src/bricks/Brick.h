#ifndef BRICK_H
#define BRICK_H

#include <map>
#include <string>

#include "../Cell.h"
#include "../Colors.h"

template <typename Shape>
class Game;

// Classe représentant une brique
template <typename Shape>
class Brick : public Cell<Shape> {
 public:
  bool rebondir() const override;
  bool hit();
  void renderCell(std::shared_ptr<SDL_Renderer>& renderer, int x, int y,
                  int cellWidth, int cellHeight);

  inline int getStrength() const { return strength_; }
  inline int getHitsLeft() const { return hitsLeft_; }

  // Méthode pour obtenir le nombre de coups restants
  Color getColor() const override;

  // protected:
  Brick(int strength, Game<Shape>* game);

  Brick(int strength, Game<Shape>* game, TriangleCell::Orientation orientation);

 protected:
  Game<Shape>* game_;  // Attribut pour stocker un pointeur vers l'objet Game
  int hitsLeft_;       // Nombre de coups restants

 private:
  int strength_;  // Force de la brique
  Color color_;   // protected .
  std::map<int, Color> strengthColorMap_ = {
      {1, Color::BrickLight},
      {2, Color::BrickLightMedium},
      {3, Color::BrickMedium},
      {4, Color::BrickDarkMedium},
      {5, Color::BrickDark}};  // Dictionnaire associant une force à une couleur
};

#include "Brick.hpp"

#endif  // BRICK_H
