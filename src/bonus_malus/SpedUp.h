#ifndef SPEDUP_H
#define SPEDUP_H

#include "BonusMalus.h"

template <typename Shape>
class Game;

template <typename Shape>
class SpedUp : public BonusMalus<Shape> {
 public:
  SpedUp(Game<Shape>* game, int x, int y);
  void applyEffect() override;
};

#include "SpedUp.hpp"
#endif  // SPEDUP_H