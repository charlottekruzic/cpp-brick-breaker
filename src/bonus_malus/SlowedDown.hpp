#include "../Game.h"
#include "SlowedDown.h"
template <typename Shape>
SlowedDown<Shape>::SlowedDown(Game<Shape>* game, int x, int y)
    : BonusMalus<Shape>(game, Color::LightGray, x, y) {}

template <typename Shape>
void SlowedDown<Shape>::applyEffect() {
  this->game_->setBallDecelerating();
}