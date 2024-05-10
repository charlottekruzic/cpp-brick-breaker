#ifndef MULTIBALL_H
#define MULTIBALL_H

#include "BonusMalus.h"

class Game;

class MultiBall : public BonusMalus {
 public:
  MultiBall(Game* game, int x, int y);
  void applyEffect() override;
};

#endif  // MULTIBALL_H
