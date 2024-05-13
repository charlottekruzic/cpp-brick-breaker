#ifndef MULTIBALL_H
#define MULTIBALL_H

#include "BonusMalus.h"

template <typename Shape>
class Game;

template <typename Shape>
class MultiBall : public BonusMalus<Shape> {
 public:
  MultiBall(std::weak_ptr<Game<Shape>> game, int x, int y);
  void applyEffect() override;

 protected:
  std::weak_ptr<Game<Shape>> game_;
};

#include "MultiBall.hpp"
#endif  // MULTIBALL_H