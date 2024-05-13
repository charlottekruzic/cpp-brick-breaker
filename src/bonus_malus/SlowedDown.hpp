#include "../Game.h"
#include "SlowedDown.h"
template <typename Shape>
SlowedDown<Shape>::SlowedDown(std::weak_ptr<Game<Shape>> game, int x, int y)
    : BonusMalus<Shape>(game, Color::Blue, x, y) {}

template <typename Shape>
void SlowedDown<Shape>::applyEffect() {
  if (auto game = game_.lock()) {
    // Utilisez game normalement
    game->setBallDecelerating();
  } else {
    std::cerr << "erreur weak ptr game slowed down" << std::endl;
    // Le Game n'existe plus, gestion de l'erreur ou logique alternative
  }
}