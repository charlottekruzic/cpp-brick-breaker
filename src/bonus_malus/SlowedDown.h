#ifndef SLOWEDDOWN_H
#define SLOWEDDOWN_H

#include "BonusMalus.h"

class Game;

class SlowedDown : public BonusMalus {
 public:
  SlowedDown(Game* game, int x, int y);
  void applyEffect() override;
};

#endif  // SLOWEDDOWN_H
