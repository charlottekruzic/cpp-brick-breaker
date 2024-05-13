#include "../Game.h"
#include "SlowedDown.h"
template <typename Shape>
SlowedDown<Shape>::SlowedDown(std::shared_ptr<Game<Shape>> game, int x, int y)
    : BonusMalus<Shape>(game, Color::Blue, x, y) {}

template <typename Shape>
void SlowedDown<Shape>::applyEffect() {
  auto sharedGame = this->game_.lock();
  if (sharedGame) {
    sharedGame->setBallDecelerating();
  }
}