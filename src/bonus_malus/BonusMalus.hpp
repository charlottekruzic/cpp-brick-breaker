#include <memory>

#include "BonusMalus.h"
template <typename Shape>
BonusMalus<Shape>::BonusMalus(std::weak_ptr<Game<Shape>> game, Color color,
                              int x, int y)
    : game_(std::move(game)), color_(color), x_(x), y_(y) {}

template <typename Shape>
void BonusMalus<Shape>::render(std::shared_ptr<SDL_Renderer>& renderer) {
  SDL_Color color = ColorUtils::convertColor(getColor());
  SDL_SetRenderDrawColor(renderer.get(), color.r, color.g, color.b, color.a);
  SDL_Rect rect = {x_, y_, width_, height_};
  SDL_RenderFillRect(renderer.get(), &rect);
}