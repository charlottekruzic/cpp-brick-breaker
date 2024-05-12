#include "../Game.h"
#include "MultiBall.h"

template <typename Shape>
MultiBall<Shape>::MultiBall(Game<Shape>* game, int x, int y)
    : BonusMalus<Shape>(game, Color::Magenta, x, y) {}

template <typename Shape>
void MultiBall<Shape>::applyEffect() {
  this->game_->generateNewBalls();
}