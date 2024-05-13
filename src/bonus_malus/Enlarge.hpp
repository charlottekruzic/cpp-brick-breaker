#include "../Game.h"
#include "Enlarge.h"

template <typename Shape>
Enlarge<Shape>::Enlarge(std::weak_ptr<Game<Shape>> game, int x, int y)
    : BonusMalus<Shape>(game, Color::Green, x, y) {}

template <typename Shape>
void Enlarge<Shape>::applyEffect() {
  if (auto game = game_.lock()) {
    // Utilisez game normalement
    game->enlargePlateformWidth();
  } else {
    std::cerr << "erreur weak ptr game enlarge" << std::endl;
    // Le Game n'existe plus, gestion de l'erreur ou logique alternative
  }
}