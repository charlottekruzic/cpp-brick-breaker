#include "Cell.h"

#include "Colors.h"

// Constructeur par défaut, initialise la couleur par défaut à blanc
Cell::Cell() : color_(Color::White) {}

// Constructeur avec spécification de la couleur
// Cell::Cell(Color color) : color_(color) {}

Color Cell::getColor() { return color_; }

void Cell::renderCell(SDL_Renderer* renderer, int x, int y, int cellSize) {
  int padding = 1;  // Espace entre chaque case
  int size = cellSize - 2 * padding;
  // Taille effective de la case avec l'espace
  SDL_Rect rect = {x + padding, y + padding, size, size};
  // Utilise les coordonnées et la taille du carré avec l'espace
  SDL_Color color = ColorUtils::convertColor(getColor());
  SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
  SDL_RenderFillRect(renderer, &rect);
}
