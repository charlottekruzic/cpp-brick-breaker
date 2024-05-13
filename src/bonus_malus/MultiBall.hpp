#include "../Game.h"
#include "MultiBall.h"

template <typename Shape>
MultiBall<Shape>::MultiBall(std::weak_ptr<Game<Shape>> game, int x, int y)
    : BonusMalus<Shape>(game, Color::Magenta, x, y) {}

template <typename Shape>
void MultiBall<Shape>::applyEffect() {
  if (auto game = game_.lock()) {
    // Utilisez game normalement
    game->generateNewBalls();
  } else {
    std::cerr << "erreur weak ptr game multiball" << std::endl;
    // Le Game n'existe plus, gestion de l'erreur ou logique alternative
  }
}