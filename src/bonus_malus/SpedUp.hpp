#include "../Game.h"
#include "SpedUp.h"
template <typename Shape>
SpedUp<Shape>::SpedUp(std::shared_ptr<Game<Shape>> game, int x, int y)
    : BonusMalus<Shape>(game, Color::Yellow, x, y) {}
template <typename Shape>
void SpedUp<Shape>::applyEffect() {
  auto sharedGame = this->game_.lock();
  if (sharedGame) {
    sharedGame->setBallAccelerating();
  }
}