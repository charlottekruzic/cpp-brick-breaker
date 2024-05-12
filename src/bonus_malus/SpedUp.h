#ifndef SPEDUP_H
#define SPEDUP_H

#include "BonusMalus.h"

class Game;

class SpedUp : public BonusMalus {
 public:
  SpedUp(Game* game, int x, int y);
  void applyEffect() override;
};

#endif  // SPEDUP_H