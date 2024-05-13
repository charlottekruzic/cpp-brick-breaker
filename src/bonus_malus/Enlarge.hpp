#include "../Game.h"
#include "Enlarge.h"

// Constructeur de la classe Enlarge
template <typename Shape>
Enlarge<Shape>::Enlarge(Game<Shape>* game, const int x, const int y)
    : BonusMalus<Shape>(game, Color::Green, x, y) {}

// Appliquer l'effet du bonus
template <typename Shape>
void Enlarge<Shape>::applyEffect() {
  this->game_->enlargePlateformWidth();
}