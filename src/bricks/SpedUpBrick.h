// SpeedChangeBrick.h
#ifndef SPEDUP_BRICK_H
#define SPEDUP_BRICK_H

#include "../Game.h"
#include "BonusBrick.h"

template <typename Shape>
class SpedUpBrick : public MalusBrick<Shape> {
 public:
  SpedUpBrick(Game* game, std::shared_ptr<SDL_Renderer>& renderer)
      : MalusBrick<Shape>(game, renderer) {}

  SpedUpBrick(Game* game, std::shared_ptr<SDL_Renderer>& renderer,
              TriangleCell::Orientation orientation)
      : MalusBrick<Shape>(game, renderer, orientation) {}

  void performAction() override {
    // Augmenter la largeur de la plateforme
    this->game_->setBallAccelerating();
  }
};

#endif  // SPEDUP_BRICK_H