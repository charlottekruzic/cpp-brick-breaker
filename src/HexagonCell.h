#ifndef HEXAGON_CELL_H
#define HEXAGON_CELL_H

#include <SDL2/SDL.h>

#include <cmath>
#include <iostream>
#include <memory>
#include <vector>

class HexagonCell {
 public:
  HexagonCell();

  void draw(std::shared_ptr<SDL_Renderer>& renderer, int x, int y,
            int cellWidth, int cellHeight, SDL_Color color);

  SDL_Point getPoint(int i);

 private:
  std::vector<SDL_Point> points_;

  void fillHexagon(std::shared_ptr<SDL_Renderer>& renderer,
                   std::vector<SDL_Point>& points);
};

#endif  // HEXAGON_CELL_H