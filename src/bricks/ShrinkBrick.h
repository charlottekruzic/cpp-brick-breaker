// SpeedChangeBrick.h
#ifndef SHRINK_BRICK_H
#define SHRINK_BRICK_H

#include "../Game.h"
#include "MalusBrick.h"

template <typename Shape>
class ShrinkBrick : public MalusBrick<Shape> {
 public:
  ShrinkBrick(std::shared_ptr<Game<Shape>> game,
              std::shared_ptr<SDL_Renderer>& renderer)
      : MalusBrick<Shape>(game, renderer) {}

  ShrinkBrick(std::shared_ptr<Game<Shape>> game,
              std::shared_ptr<SDL_Renderer>& renderer,
              TriangleCell::Orientation orientation)
      : MalusBrick<Shape>(game, renderer, orientation) {}

  void performAction() override {
    // Augmenter la largeur de la plateforme

    auto sharedGame = this->game_.lock();
    if (sharedGame) {
      sharedGame->shrinkPlateformWidth();
    }
  }
};

#endif  // SHRINK_BRICK_H