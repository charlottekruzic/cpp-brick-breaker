// SpeedChangeBrick.h
#ifndef SPEED_CHANGE_BRICK_H
#define SPEED_CHANGE_BRICK_H

#include "MalusBrick.h"

class SpedUpBrick : public MalusBrick {
 public:
 public:
  SpedUpBrick(Game* game, std::shared_ptr<SDL_Renderer>& renderer)
      : MalusBrick(game, renderer) {}

  void performAction() override {
    // Démarrer l'accélération de la balle
    game_->setBallAccelerating();
  }
};

#endif  // SPEED_CHANGE_BRICK_H
