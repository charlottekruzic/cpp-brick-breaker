#include "MultiBall.h"

#include "../Game.h"

MultiBall::MultiBall(Game* game, int x, int y)
    : BonusMalus(game, Color::Magenta, x, y) {}

void MultiBall::applyEffect() { game_->generateNewBalls(); }
