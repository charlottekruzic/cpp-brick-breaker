// SpeedChangeBrick.h
#ifndef SLOWED_DOWN_BRICK_H
#define SLOWED_DOWN_BRICK_H

#include "BonusBrick.h"

class SlowedDownBrick : public BonusBrick {
 public:
 public:
  SlowedDownBrick(Game* game, std::shared_ptr<SDL_Renderer>& renderer)
      : BonusBrick(game, renderer) {}

  void performAction() override {
    // Démarrer l'accélération de la balle
    game_->setBallDecelerating();
  }
};

#endif  // SLOWED_DOWN_BRICK_H
