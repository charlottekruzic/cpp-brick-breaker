#ifndef ENLARGE_H
#define ENLARGE_H

#include "BonusMalus.h"

class Game;

class Enlarge : public BonusMalus {
 public:
  Enlarge(Game* game, int x, int y);
  void applyEffect() override;
};

#endif  // ENLARGE_H
