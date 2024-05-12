#include "SpedUp.h"

#include "../Game.h"

SpedUp::SpedUp(Game* game, int x, int y)
    : BonusMalus(game, Color::DarkBlue, x, y) {}

void SpedUp::applyEffect() { game_->setBallAccelerating(); }