#include "BonusMalus.h"

BonusMalus::BonusMalus(Game* game, int x, int y) : game_(game), x_(x), y_(y) {}

void BonusMalus::render(SDL_Renderer* renderer) {
  SDL_Color color = ColorUtils::convertColor(getColor());
  SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
  SDL_Rect rect = {x_, y_, width_, height_};
  SDL_RenderFillRect(renderer, &rect);
}
void BonusMalus::applyEffect() {
  std::cout << "apply effect bonus malus " << std::endl;
  game_->enlargePlateformWidth();
}