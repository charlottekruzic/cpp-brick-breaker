#ifndef BASICsBRICK_H
#define BASICsBRICK_H

#include "Brick.h"

// Classe représentant une brique basique
class BasicBrick : public Brick {
 public:
  BasicBrick(int strength, Game* game)
      : Brick(strength, game) {}  // Constructeur prenant la couleur choisie
};

#endif  // BASICsBRICK_H
