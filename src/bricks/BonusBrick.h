#ifndef BONUS_BRICK_H
#define BONUS_BRICK_H

#include "SpecialBrick.h"

template <typename Shape>
class BonusBrick : public SpecialBrick<BonusBrick<Shape>, Shape> {
 public:
  BonusBrick(Game* game, std::shared_ptr<SDL_Renderer>& renderer);
  BonusBrick(Game* game, std::shared_ptr<SDL_Renderer>& renderer,
             TriangleCell::Orientation orientation);

  // Méthode pour obtenir la texture du malus
  static std::shared_ptr<SDL_Texture>& getTexture() {
    // Implémentation pour obtenir la texture spécifique à MalusBrick
    return bonus_texture_;
  }

  void renderCell(std::shared_ptr<SDL_Renderer>& renderer, int x, int y,
                  int cellWidth, int cellHeight);

  inline Color getColor() const override { return Color::DarkGreen; };

 private:
  static std::shared_ptr<SDL_Texture> bonus_texture_;  // Attribut pour la
                                                       // texture du malus
};

#include "BonusBrick.hpp"

#endif  // BONUS_BRICK_H