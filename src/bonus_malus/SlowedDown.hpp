#include "../Game.h"
#include "SlowedDown.h"
template <typename Shape>

// Constructeur de la classe SlowedDown
SlowedDown<Shape>::SlowedDown(Game<Shape>* game, const int x, const int y)
    : BonusMalus<Shape>(game, Color::Blue, x, y) {}

// Appliquer l'effet du bonus
template <typename Shape>
void SlowedDown<Shape>::applyEffect() {
  this->game_->setBallDecelerating();
}