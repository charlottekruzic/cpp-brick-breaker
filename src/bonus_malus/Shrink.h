#ifndef SHRINK_H
#define SHRINK_H

#include "BonusMalus.h"

template <typename Shape>
class Game;

template <typename Shape>
class Shrink : public BonusMalus<Shape> {
 public:
  Shrink(Game<Shape>* game, int x, int y);
  void applyEffect() override;
};

#include "Shrink.hpp"
#endif  // SHRINK_H