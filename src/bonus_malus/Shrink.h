#ifndef SHRINK_H
#define SHRINK_H

#include "BonusMalus.h"

template <typename Shape>
class Game;

template <typename Shape>
class Shrink : public BonusMalus<Shape> {
 public:
  Shrink(std::weak_ptr<Game<Shape>> game, int x, int y);
  void applyEffect() override;

 protected:
  std::weak_ptr<Game<Shape>> game_;
};

#include "Shrink.hpp"
#endif  // SHRINK_H