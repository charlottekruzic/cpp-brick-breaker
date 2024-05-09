#ifndef SHRINK_H
#define SHRINK_H

#include "BonusMalus.h"

class Game;

class Shrink : public BonusMalus {
 public:
  Shrink(Game* game, int x, int y);
  void applyEffect() override;
};

#endif  // SHRINK_H
