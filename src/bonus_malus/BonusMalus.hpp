#include <memory>

#include "BonusMalus.h"

// Constructeur de la classe BonusMalus
template <typename Shape>
BonusMalus<Shape>::BonusMalus(Game<Shape>* game, const Color color, const int x,
                              const int y)
    : game_(game), color_(color), x_(x), y_(y) {}

// Afficher le bonus/malus
template <typename Shape>
void BonusMalus<Shape>::render(const std::shared_ptr<SDL_Renderer>& renderer) {
  SDL_Color color = ColorUtils::convertColor(getColor());
  SDL_SetRenderDrawColor(renderer.get(), color.r, color.g, color.b, color.a);
  SDL_Rect rect = {x_, y_, width_, height_};
  SDL_RenderFillRect(renderer.get(), &rect);
}