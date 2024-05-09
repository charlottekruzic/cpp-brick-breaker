#include "BonusMalus.h"

#include <memory>

BonusMalus::BonusMalus(Game* game, Color color, int x, int y)
    : game_(game), color_(color), x_(x), y_(y) {}

void BonusMalus::render(std::shared_ptr<SDL_Renderer>& renderer) {
  SDL_Color color = ColorUtils::convertColor(getColor());
  SDL_SetRenderDrawColor(renderer.get(), color.r, color.g, color.b, color.a);
  SDL_Rect rect = {x_, y_, width_, height_};
  SDL_RenderFillRect(renderer.get(), &rect);
}