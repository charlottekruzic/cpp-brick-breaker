#ifndef WALL_H
#define WALL_H

#include <SDL2/SDL_image.h>

#include "../Cell.h"

class Wall : public Cell {
 public:
  Wall(std::shared_ptr<SDL_Renderer>& renderer);

  inline bool rebondir() const override { return true; }
  inline bool hit() override { return false; }
  void renderCell(std::shared_ptr<SDL_Renderer>& renderer, int x, int y,
                  int cellWidth, int cellHeight) override;

  inline Color getColor() const override { return color_; }

 private:
  static std::shared_ptr<SDL_Texture> wall_texture_;  // Attribut pour la
                                                      // texture du malus

  // Méthode pour obtenir la texture du malus
  static std::shared_ptr<SDL_Texture>& getTexture() {
    // Implémentation pour obtenir la texture spécifique à MalusBrick
    return wall_texture_;
  }
};

#endif  // WALL_H
