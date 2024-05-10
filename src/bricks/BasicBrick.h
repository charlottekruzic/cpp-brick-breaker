#ifndef BASICsBRICK_H
#define BASICsBRICK_H

#include "../Colors.h"
#include "Brick.h"

// Classe représentant une brique basique
class BasicBrick : public Brick {
 public:
  enum class Orientation { UP, DOWN };

  BasicBrick(int strength, Game* game, Orientation orientation)
      : Brick(strength, game),
        orientation_(orientation) {}  // Constructeur prenant la couleur choisie

  void renderCell(std::shared_ptr<SDL_Renderer>& renderer, int x, int y,
                  int cellWidth, int cellHeight) override;

  void fillTriangle(SDL_Renderer* renderer, SDL_Point* points);

  Orientation getOrientation() const;

 private:
  Orientation orientation_;
};

#endif  // BASICsBRICK_H
