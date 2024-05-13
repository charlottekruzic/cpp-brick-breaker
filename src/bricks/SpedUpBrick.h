// SpeedChangeBrick.h
#ifndef SPEDUP_BRICK_H
#define SPEDUP_BRICK_H

#include "../Game.h"
#include "BonusBrick.h"

template <typename Shape>
class SpedUpBrick : public MalusBrick<Shape> {
 public:
  SpedUpBrick(std::shared_ptr<Game<Shape>> game,
              std::shared_ptr<SDL_Renderer>& renderer)
      : MalusBrick<Shape>(game, renderer) {}

  SpedUpBrick(std::shared_ptr<Game<Shape>> game,
              std::shared_ptr<SDL_Renderer>& renderer,
              TriangleCell::Orientation orientation)
      : MalusBrick<Shape>(game, renderer, orientation) {}

  void performAction() override {
    // Augmenter la largeur de la plateforme
    auto sharedGame = this->game_.lock();  // Convertit weak_ptr en shared_ptr
    if (sharedGame) {
      sharedGame->setBallAccelerating();
    }
  }
};

#endif  // SPEDUP_BRICK_H