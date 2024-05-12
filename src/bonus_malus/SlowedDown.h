#ifndef SLOWEDDOWN_H
#define SLOWEDDOWN_H

#include "BonusMalus.h"

template <typename Shape>
class Game;

template <typename Shape>
class SlowedDown : public BonusMalus<Shape> {
 public:
  SlowedDown(Game<Shape>* game, int x, int y);
  void applyEffect() override;
};

#include "SlowedDown.hpp"
#endif  // SLOWEDDOWN_H