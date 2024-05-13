#ifndef SPEDUP_H
#define SPEDUP_H

#include "BonusMalus.h"

template <typename Shape>
class Game;

template <typename Shape>
class SpedUp : public BonusMalus<Shape> {
 public:
  SpedUp(std::weak_ptr<Game<Shape>> game, int x, int y);
  void applyEffect() override;

 protected:
  std::weak_ptr<Game<Shape>> game_;
};

#include "SpedUp.hpp"
#endif  // SPEDUP_H