#include "Cell.h"

#include <memory>

#include "Colors.h"

// Constructeur par défaut, initialise la couleur par défaut à blanc
Cell::Cell() : color_(Color::White) {}

// Constructeur avec spécification de la couleur
Cell::Cell(Color color) : color_(color) {}

void Cell::renderCell(std::shared_ptr<SDL_Renderer>& renderer, int x, int y,
                      int cellWidth, int cellHeight) {}
