#include "Empty.h"

// pointeur statique pour la texture
// SDL_Texture* Empty::empty_texture_ = nullptr;

Empty::Empty() : Cell(Color::Black) {}

bool Empty::rebondir() const {
  return false;  // Les objets ne rebondissent pas sur une case vide
}

bool Empty::hit() { return true; }

void Empty::renderCell(std::shared_ptr<SDL_Renderer>& renderer, int x, int y,
                       int cellWidth, int cellHeight) { /*rien*/ }

Color Empty::getColor() const { return color_; }
