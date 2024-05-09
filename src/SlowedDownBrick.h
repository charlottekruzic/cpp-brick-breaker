// SpeedChangeBrick.h
#ifndef SLOWED_DOWN_BRICK_H
#define SLOWED_DOWN_BRICK_H

#include "BonusBrick.h"

class SlowedDownBrick : public BonusBrick {
 public:
 public:
  SlowedDownBrick(int strength, Game* game, SDL_Renderer* renderer)
      : BonusBrick(strength, game, renderer) {}

  void performAction() override;
};

#endif  // SLOWED_DOWN_BRICK_H
