#include "../Game.h"
#include "Shrink.h"

// Constructeur de la classe Shrink
template <typename Shape>
Shrink<Shape>::Shrink(Game<Shape>* game, const int x, const int y)
    : BonusMalus<Shape>(game, Color::Red, x, y) {}

// Appliquer l'effet du malus
template <typename Shape>
void Shrink<Shape>::applyEffect() {
  this->game_->shrinkPlateformWidth();
}