#include "BonusMalus.h"

BonusMalus::BonusMalus(Game* game, Color color, int x, int y)
    : game_(game), color_(color), x_(x), y_(y) {}

void BonusMalus::render(SDL_Renderer* renderer) {
  SDL_Color color = ColorUtils::convertColor(getColor());
  SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
  SDL_Rect rect = {x_, y_, width_, height_};
  SDL_RenderFillRect(renderer, &rect);
}