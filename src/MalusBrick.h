#ifndef MALICIOUS_BRICK_H
#define MALICIOUS_BRICK_H

#include "Ball.h"
#include "Brick.h"
#include "Plateform.h"

class MalusBrick : public Brick {
 public:
  MalusBrick(int strength, SDL_Renderer* renderer);
  virtual void performAction(Ball& ball, Plateform& platform) = 0;  //
  // Méthode virtuelle pure pour effectuer une action spécifique
  void renderCell(SDL_Renderer* renderer, int x, int y, int cellWidth) override;

 private:
  static SDL_Texture* malus_texture_;
};

#endif  // MALICIOUS_BRICK_H
