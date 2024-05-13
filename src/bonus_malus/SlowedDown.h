#ifndef SLOWEDDOWN_H
#define SLOWEDDOWN_H

#include "BonusMalus.h"

template <typename Shape>
class Game;

template <typename Shape>
class SlowedDown : public BonusMalus<Shape> {
 public:
  SlowedDown(std::weak_ptr<Game<Shape>> game, int x, int y);
  void applyEffect() override;

 protected:
  std::weak_ptr<Game<Shape>> game_;
};

#include "SlowedDown.hpp"
#endif  // SLOWEDDOWN_H