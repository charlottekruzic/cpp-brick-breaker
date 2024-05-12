#include "../Game.h"
#include "Shrink.h"

template <typename Shape>
Shrink<Shape>::Shrink(Game<Shape>* game, int x, int y)
    : BonusMalus<Shape>(game, Color::Red, x, y) {}

template <typename Shape>
void Shrink<Shape>::applyEffect() {
  this->game_->shrinkPlateformWidth();
}