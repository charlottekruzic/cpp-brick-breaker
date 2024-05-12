// SpeedChangeBrick.h
#ifndef ENLARGE_BRICK_H
#define ENLARGE_BRICK_H

#include "../Game.h"
#include "BonusBrick.h"

template <typename Shape>
class EnlargeBrick : public BonusBrick<Shape> {
 public:
  EnlargeBrick(Game* game, std::shared_ptr<SDL_Renderer>& renderer)
      : BonusBrick<Shape>(game, renderer) {}

  EnlargeBrick(Game* game, std::shared_ptr<SDL_Renderer>& renderer,
               TriangleCell::Orientation orientation)
      : BonusBrick<Shape>(game, renderer, orientation) {}

  void performAction() override {
    // Augmenter la largeur de la plateforme
    this->game_->enlargePlateformWidth();
  }
};

#endif  // ENLARGE_BRICK_H