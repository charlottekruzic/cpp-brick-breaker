#include "../Game.h"
#include "Shrink.h"

template <typename Shape>
Shrink<Shape>::Shrink(std::weak_ptr<Game<Shape>> game, int x, int y)
    : BonusMalus<Shape>(game, Color::Red, x, y) {}

template <typename Shape>
void Shrink<Shape>::applyEffect() {
  if (auto game = game_.lock()) {
    // Utilisez game normalement
    game->shrinkPlateformWidth();
  } else {
    std::cerr << "erreur weak ptr game shrink" << std::endl;
    // Le Game n'existe plus, gestion de l'erreur ou logique alternative
  }
}