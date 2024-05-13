#ifndef TRIANGLE_CELL_H
#define TRIANGLE_CELL_H

#include <SDL2/SDL.h>

#include <iostream>
#include <memory>
#include <vector>

class TriangleCell {
 public:
  enum class Orientation { UP, DOWN };
  TriangleCell();
  TriangleCell(Orientation orientation);

  void draw(std::shared_ptr<SDL_Renderer>& renderer, int x, int y,
            int cellWidth, int cellHeight, SDL_Color color);

  SDL_Point getPoint(int i);

 private:
  Orientation orientation_;
  std::vector<SDL_Point> points_;

  void fillTriangle(std::shared_ptr<SDL_Renderer>& renderer,
                    std::vector<SDL_Point>& points);
};

#endif  // TRIANGLE_CELL_H
