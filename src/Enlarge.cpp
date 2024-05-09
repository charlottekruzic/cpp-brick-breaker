#include "Enlarge.h"

#include "Game.h"

Enlarge::Enlarge(Game* game, int x, int y)
    : BonusMalus(game, Color::DarkGreen, x, y) {}

void Enlarge::applyEffect() { game_->enlargePlateformWidth(); }
