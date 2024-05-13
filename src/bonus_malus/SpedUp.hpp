#include "../Game.h"
#include "SpedUp.h"

// Constructeur de la classe SpedUp
template <typename Shape>
SpedUp<Shape>::SpedUp(Game<Shape>* game, const int x, const int y)
    : BonusMalus<Shape>(game, Color::Yellow, x, y) {}

// Appliquer l'effet du malus
template <typename Shape>
void SpedUp<Shape>::applyEffect() {
  this->game_->setBallAccelerating();
}