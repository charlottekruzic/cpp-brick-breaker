// SpeedChangeBrick.h
#ifndef ENLARGE_BRICK_H
#define ENLARGE_BRICK_H

#include "../Game.h"
#include "BonusBrick.h"

template <typename Shape>
class EnlargeBrick : public BonusBrick<Shape> {
 public:
  EnlargeBrick(std::shared_ptr<Game<Shape>> game,
               std::shared_ptr<SDL_Renderer>& renderer)
      : BonusBrick<Shape>(game, renderer) {}

  EnlargeBrick(std::shared_ptr<Game<Shape>> game,
               std::shared_ptr<SDL_Renderer>& renderer,
               TriangleCell::Orientation orientation)
      : BonusBrick<Shape>(game, renderer, orientation) {}

  void performAction() override {
    // Augmenter la largeur de la plateforme
    auto sharedGame = this->game_.lock();
    if (sharedGame) {
      sharedGame->enlargePlateformWidth();
    };
  }
};

#endif  // ENLARGE_BRICK_H