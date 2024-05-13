#ifndef ENLARGE_H
#define ENLARGE_H

#include "BonusMalus.h"

template <typename Shape>
class Game;

template <typename Shape>
class Enlarge : public BonusMalus<Shape> {
 public:
  Enlarge(std::shared_ptr<Game<Shape>> game, int x, int y);
  void applyEffect() override;
};

#include "Enlarge.hpp"
#endif  // ENLARGE_H