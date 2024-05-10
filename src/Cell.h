#ifndef CELL_H
#define CELL_H

#include <iostream>
#include <memory>
#include <vector>

#include "Colors.h"

// Classe de base représentant une case du plateau
class Cell {
 public:
  // virtual ~Cell() {}  // Définir un destructeur virtuel pour permettre la
  // destruction correcte des objets dérivés

  enum class Orientation { UP, DOWN };

  virtual bool rebondir() const = 0;
  virtual bool hit() = 0;
  virtual void renderCell(std::shared_ptr<SDL_Renderer>& renderer, int x, int y,
                          int cellWidth, int cellHeight);

  inline virtual Color getColor() {
    return color_;
  };  // Méthode pour obtenir la couleur de la case
  Orientation getOrientation() const;

  SDL_Point getPoint(int i) {
    if (i >= 0 && i <= 4) {
      return points[i];
    } else {
      return points[0];
    }
  }

 protected:
  Orientation orientation_;
  Cell();
  Cell(Color color);
  SDL_Point points[4];
  // constructeur accessible uniquement par les classes enfants

 private:
  // char symbol;

  Color color_;  // Couleur de la case
};

#endif  // CELL_H
