#include "Cell.h"

#include <memory>

#include "Colors.h"

// Constructeur par défaut, initialise la couleur par défaut à blanc
Cell::Cell() : color_(Color::White) {}

// Constructeur avec spécification de la couleur
Cell::Cell(Color color) : color_(color) {}

void Cell::renderCell(std::shared_ptr<SDL_Renderer>& renderer, int x, int y,
                      int cellWidth, int cellHeight) {
  /*SDL_Point points[4];

  if (orientation_ == Orientation::UP) {
    // Triangle pointant vers le haut
    points[0] = {x + cellSize / 2, y};             // Pointe du triangle en haut
    points[1] = {x - cellSize / 2, y + cellSize};  // Bas gauche
    points[2] = {x + cellSize * 3 / 2, y + cellSize};  // Bas droit
  } else {                                             // Orientation::DOWN
    // Triangle pointant vers le bas
    points[0] = {x - cellSize / 2, y};             // Haut gauche
    points[1] = {x + cellSize * 3 / 2, y};         // Haut droit
    points[2] = {x + cellSize / 2, y + cellSize};  // Pointe du triangle en bas
  }
  points[3] = points[0];  // Fermer le triangle

  SDL_Color color = ColorUtils::convertColor(getColor());
  SDL_SetRenderDrawColor(renderer.get(), color.r, color.g, color.b, color.a);
  SDL_RenderDrawLines(renderer.get(), points, 4);*/
}