#include <iostream>

#include "../Game.h"
#include "SpedUp.h"
template <typename Shape>
SpedUp<Shape>::SpedUp(std::weak_ptr<Game<Shape>> game, int x, int y)
    : BonusMalus<Shape>(game, Color::Yellow, x, y) {}
template <typename Shape>
void SpedUp<Shape>::applyEffect() {
  if (auto game = game_.lock()) {
    // Utilisez game normalement
    game->setBallAccelerating();
  } else {
    std::cerr << "erreur weak ptr game sped up" << std::endl;
    // Le Game n'existe plus, gestion de l'erreur ou logique alternative
  }
}