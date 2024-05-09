#include "Shrink.h"

#include "Game.h"

Shrink::Shrink(Game* game, int x, int y)
    : BonusMalus(game, Color::DarkRed, x, y) {}

void Shrink::applyEffect() { game_->shrinkPlateformWidth(); }
