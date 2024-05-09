#ifndef SHRINK_H
#define SHRINK_H

#include "BonusMalus.h"

class Game;

class Shrink : public BonusMalus {
 public:
  Shrink(Game* game, int x, int y) : BonusMalus(game, x, y) {}

  // void applyEffect() override;

  Color color = Color::Cyan;
};

#endif  // SHRINK_H
