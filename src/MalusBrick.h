#ifndef MALICIOUS_BRICK_H
#define MALICIOUS_BRICK_H

#include "Ball.h"
#include "Brick.h"
#include "Plateform.h"

class MalusBrick : public Brick {
 public:
  MalusBrick(int strength, Game* game, SDL_Renderer* renderer);
  virtual void performAction() = 0;  //
  // Méthode virtuelle pure pour effectuer une action spécifique
  void renderCell(SDL_Renderer* renderer, int x, int y, int cellWidth) override;
  bool hit() override;

 private:
  static SDL_Texture* malus_texture_;

 protected:
  // int hitsLeft_;
};

#endif  // MALICIOUS_BRICK_H
