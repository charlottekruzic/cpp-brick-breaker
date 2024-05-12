#include "../Game.h"
#include "SpedUp.h"
template <typename Shape>
SpedUp<Shape>::SpedUp(Game<Shape>* game, int x, int y)
    : BonusMalus<Shape>(game, Color::DarkBlue, x, y) {}
template <typename Shape>
void SpedUp<Shape>::applyEffect() {
  this->game_->setBallAccelerating();
}