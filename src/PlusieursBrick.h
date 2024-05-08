#ifndef PLSIEURSBRICK_H
#define PLSIEURSBRICK_H

#include "Brick.h"

// Classe représentant une brique basique
class BasicBrick : public Brick {
 public:
  BasicBrick(int strength);  // Constructeur prenant la couleur choisie
};

// class BrickV2 : public Brick {
//  public:
//   BrickV2(Color color);  // Constructeur prenant la couleur choisie
// };
//
// class BrickV3 : public Brick {
//  public:
//   BrickV3(Color color);  // Constructeur prenant la couleur choisie
// };
#endif  // PLSIEURSBRICK_H
