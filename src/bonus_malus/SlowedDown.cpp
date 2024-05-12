#include "SlowedDown.h"

#include "../Game.h"

SlowedDown::SlowedDown(Game* game, int x, int y)
    : BonusMalus(game, Color::LightGray, x, y) {}

void SlowedDown::applyEffect() { game_->setBallDecelerating(); }