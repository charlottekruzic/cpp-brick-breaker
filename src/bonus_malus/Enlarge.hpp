#include "../Game.h"
#include "Enlarge.h"

template <typename Shape>
Enlarge<Shape>::Enlarge(Game<Shape>* game, int x, int y)
    : BonusMalus<Shape>(game, Color::DarkGreen, x, y) {}

template <typename Shape>
void Enlarge<Shape>::applyEffect() {
  this->game_->enlargePlateformWidth();
}