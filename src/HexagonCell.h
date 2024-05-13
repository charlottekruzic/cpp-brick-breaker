#ifndef HEXAGON_CELL_H
#define HEXAGON_CELL_H

#include <SDL2/SDL.h>

#include <cmath>
#include <iostream>
#include <memory>

class HexagonCell {
 public:
  HexagonCell();

  void draw(std::shared_ptr<SDL_Renderer>& renderer, int x, int y,
            int cellWidth, int cellHeight, SDL_Color color);

  SDL_Point getPoint(int i);

 private:
  SDL_Point points_[7];

  void fillHexagon(std::shared_ptr<SDL_Renderer>& renderer, SDL_Point* points);
};

#endif  // HEXAGON_CELL_H