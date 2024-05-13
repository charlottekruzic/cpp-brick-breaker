#include "../Game.h"
#include "Enlarge.h"

template <typename Shape>
Enlarge<Shape>::Enlarge(std::shared_ptr<Game<Shape>> game, int x, int y)
    : BonusMalus<Shape>(game, Color::Green, x, y) {}

template <typename Shape>
void Enlarge<Shape>::applyEffect() {
  auto sharedGame = this->game_.lock();
  if (sharedGame) {
    sharedGame->enlargePlateformWidth();
  }
}