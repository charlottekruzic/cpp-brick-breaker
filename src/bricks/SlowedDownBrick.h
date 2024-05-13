// SpeedChangeBrick.h
#ifndef SLOWEDDOWN_BRICK_H
#define SLOWEDDOWN_BRICK_H

#include "../Game.h"
#include "BonusBrick.h"

template <typename Shape>
class SlowedDownBrick : public BonusBrick<Shape> {
 public:
  SlowedDownBrick(std::shared_ptr<Game<Shape>> game,
                  std::shared_ptr<SDL_Renderer>& renderer)
      : BonusBrick<Shape>(game, renderer) {}

  SlowedDownBrick(std::shared_ptr<Game<Shape>> game,
                  std::shared_ptr<SDL_Renderer>& renderer,
                  TriangleCell::Orientation orientation)
      : BonusBrick<Shape>(game, renderer, orientation) {}

  void performAction() override {
    // Augmenter la largeur de la plateforme

    auto sharedGame = this->game_.lock();
    if (sharedGame) {
      sharedGame->setBallDecelerating();
    }
  }
};

#endif  // SLOWEDDOWN_BRICK_H