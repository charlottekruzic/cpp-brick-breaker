#ifndef MALUS_BONUS_H
#define MALUS_BONUS_H

#include "Brick.h"

template <typename Derived>
class MalusBonusBrick : public Brick {
 public:
  MalusBonusBrick(Game* game, std::shared_ptr<SDL_Renderer>& renderer);

  // Méthode virtuelle pure pour effectuer une action spécifique
  void renderCell(std::shared_ptr<SDL_Renderer>& renderer, int x, int y,
                  int cellWidth, int cellHeight) override;
  virtual void performAction() = 0;
  bool hit() override;

  static std::shared_ptr<SDL_Texture>& getTexture() {
    return Derived::getTexture();
  }
};

#include "MalusBonusBrick.hpp"

#endif  // MALUS_BONUS_H
