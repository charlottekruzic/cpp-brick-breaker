// SpeedChangeBrick.h
#ifndef ENLARGE_BRICK_H
#define ENLARGE_BRICK_H

#include "BonusBrick.h"

class EnlargeBrick : public BonusBrick {
 public:
  EnlargeBrick(Game* game, SDL_Renderer* renderer)
      : BonusBrick(game, renderer) {}

  void performAction() override {
    // Augmenter la largeur de la plateforme
    game_->enlargePlateformWidth();
  }
};

#endif  // ENLARGE_BRICK_H
