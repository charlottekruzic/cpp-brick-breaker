// SpeedChangeBrick.h
#ifndef SPEED_CHANGE_BRICK_H
#define SPEED_CHANGE_BRICK_H

#include "MalusBrick.h"

class SpeedChangeBrick : public MalusBrick {
 public:
 public:
  SpeedChangeBrick(int strength, SDL_Renderer* renderer)
      : MalusBrick(strength, renderer) {}

  void performAction(Ball& ball, Plateform& platform) override;
};

#endif  // SPEED_CHANGE_BRICK_H
