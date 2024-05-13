#include "../Game.h"
#include "MultiBall.h"

// Constructeur de la classe MultiBall
template <typename Shape>
MultiBall<Shape>::MultiBall(Game<Shape>* game, int x, int y)
    : BonusMalus<Shape>(game, Color::Magenta, x, y) {}

// Appliquer l'effet du bonus
template <typename Shape>
void MultiBall<Shape>::applyEffect() {
  this->game_->generateNewBalls();
}