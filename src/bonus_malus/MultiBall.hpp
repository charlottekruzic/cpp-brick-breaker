#include "../Game.h"
#include "MultiBall.h"

template <typename Shape>
MultiBall<Shape>::MultiBall(std::shared_ptr<Game<Shape>> game, int x, int y)
    : BonusMalus<Shape>(game, Color::Magenta, x, y) {}

template <typename Shape>
void MultiBall<Shape>::applyEffect() {
  auto sharedGame = this->game_.lock();
  if (sharedGame) {
    sharedGame->generateNewBalls();
  }
}