#ifndef WALL_H
#define WALL_H

#include <SDL2/SDL.h>

#include "../Cell.h"

template <typename Shape>
class Wall : public Cell<Shape> {
 public:
  Wall(std::shared_ptr<SDL_Renderer>& renderer);
  Wall(std::shared_ptr<SDL_Renderer>& renderer,
       TriangleCell::Orientation orientation);

  inline bool rebondir() const override { return true; }
  inline bool hit() override { return false; }
  inline Color getColor() const override { return this->color_; }

  void renderCell(std::shared_ptr<SDL_Renderer>& renderer, int x, int y,
                  float cellWidth, float cellHeight) override;

 private:
  static std::shared_ptr<SDL_Texture> wall_texture_;  // Attribut pour la
                                                      // texture du malus

  // Méthode pour obtenir la texture du malus
  inline static std::shared_ptr<SDL_Texture>& getTexture() {
    return wall_texture_;
  }
};

#include "Wall.hpp"

#endif  // WALL_H