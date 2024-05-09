#ifndef MALUS_BONUS_H
#define MALUS_BONUS_H

#include "Brick.h"

template <typename Derived>
class MalusBonusBrick : public Brick {
 public:
  MalusBonusBrick(int strength, Game* game, SDL_Renderer* renderer);

  // Méthode virtuelle pure pour effectuer une action spécifique
  void renderCell(SDL_Renderer* renderer, int x, int y, int cellWidth) override;
  virtual void performAction() = 0;
  bool hit() override;

  static SDL_Texture* getTexture() { return Derived::getTexture(); }
};

#include "MalusBonusBrick.hpp"

#endif  // MALUS_BONUS_H
