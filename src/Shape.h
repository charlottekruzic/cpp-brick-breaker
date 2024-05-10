#ifndef SQUARE_CELL_H
#define SQUARE_CELL_H
#include "Cell.h"

//  Carré
class SquareCell : public Cell {
 public:
  SquareCell(Color color) : Cell(color) {}

  bool rebondir() const override { return true; }

  bool hit() override { return true; }

  void renderCell(std::shared_ptr<SDL_Renderer>& renderer, int x, int y,
                  int cellWidth, int cellHeight) override {
    int padding = 1;  // Espace entre chaque case
    int size = cellWidth - 2 * padding;
    // Taille effective de la case avec l'espace
    SDL_Rect rect = {x + padding, y + padding, size, size};
    // Utilise les coordonnées et la taille du carré avec l'espace
    SDL_Color color = ColorUtils::convertColor(getColor());
    SDL_SetRenderDrawColor(renderer.get(), color.r, color.g, color.b, color.a);
    SDL_RenderFillRect(renderer.get(), &rect);
  }

  Color getColor() const override { return color_; }
};

#endif  // SQUARE_CELL_H

#ifndef TRIANGLE_CELL_H
#define TRIANGLE_CELL_H

#include "Cell.h"
// Triangle
class TriangleCell : public Cell {
 public:
  TriangleCell(Color color) : Cell(color) {}

  bool rebondir() const override { return true; }

  bool hit() override { return true; }

  void renderCell(std::shared_ptr<SDL_Renderer>& renderer, int x, int y,
                  int cellWidth, int cellHeight) override {
    // A voir après
  }
};

#endif  // TRIANGLE_CELL_H