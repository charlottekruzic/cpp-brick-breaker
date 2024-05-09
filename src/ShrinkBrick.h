// SpeedChangeBrick.h
#ifndef SHRINK_BRICK_H
#define SHRINK_BRICK_H

#include "MalusBrick.h"

class ShrinkBrick : public MalusBrick {
 public:
  ShrinkBrick(Game* game, SDL_Renderer* renderer)
      : MalusBrick(game, renderer) {}

  void performAction() override {
    // Augmenter la largeur de la plateforme
    game_->shrinkPlateformWidth();
  }
};

#endif  // SHRINK_BRICK_H
