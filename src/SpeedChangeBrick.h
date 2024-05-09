// SpeedChangeBrick.h
#ifndef SPEED_CHANGE_BRICK_H
#define SPEED_CHANGE_BRICK_H

#include "MalusBrick.h"

class SpeedChangeBrick : public MalusBrick {
 public:
 public:
  SpeedChangeBrick(int strength, Game* game, SDL_Renderer* renderer)
      : MalusBrick(strength, game, renderer) {}

  void performAction() override;
};

#endif  // SPEED_CHANGE_BRICK_H
