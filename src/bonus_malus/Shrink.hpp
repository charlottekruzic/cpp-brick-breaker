#include "../Game.h"
#include "Shrink.h"

template <typename Shape>
Shrink<Shape>::Shrink(std::shared_ptr<Game<Shape>> game, int x, int y)
    : BonusMalus<Shape>(game, Color::Red, x, y) {}

template <typename Shape>
void Shrink<Shape>::applyEffect() {
  auto sharedGame = this->game_.lock();
  if (sharedGame) {
    sharedGame->shrinkPlateformWidth();
  }
}