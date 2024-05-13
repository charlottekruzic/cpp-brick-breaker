#include "HexagonCell.h"

#include <algorithm>
#include <memory>

HexagonCell::HexagonCell() {}

void HexagonCell::draw(std::shared_ptr<SDL_Renderer>& renderer, int x, int y,
                       int cellWidth, int cellHeight, SDL_Color color) {
  double angle = M_PI / 3;

  for (int i = 0; i < 6; ++i) {
    points_[i].x = x + cellHeight * cos(i * angle);
    points_[i].y = y + cellHeight * sin(i * angle);
  }
  points_[6] = points_[0];

  // Couleur intérieure
  SDL_SetRenderDrawColor(renderer.get(), color.r, color.g, color.b, color.a);
  SDL_RenderDrawLines(renderer.get(), points_, 7);

  fillHexagon(renderer, points_);

  // Contours noirs
  SDL_SetRenderDrawColor(renderer.get(), 0, 0, 0, 255);
  SDL_RenderDrawLines(renderer.get(), points_, 7);
}

SDL_Point HexagonCell::getPoint(int i) {
  if (i >= 0 && i < 6) {
    return points_[i];
  } else {
    return points_[0];
  }
}

void HexagonCell::fillHexagon(std::shared_ptr<SDL_Renderer>& renderer,
                              SDL_Point* points) {
  int minY = points[0].y;
  int maxY = points[0].y;
  for (int i = 1; i < 6; ++i) {
    if (points[i].y < minY) minY = points[i].y;
    if (points[i].y > maxY) maxY = points[i].y;
  }

  for (int y = minY; y <= maxY; ++y) {
    int count = 0;
    int intersections[12] = {0};
    for (int i = 0; i < 6; ++i) {
      SDL_Point& p1 = points[i];
      SDL_Point& p2 = points[i + 1];
      if (p1.y == p2.y) continue;
      if ((y >= p1.y && y < p2.y) || (y >= p2.y && y < p1.y)) {
        intersections[count++] =
            p1.x + (p2.x - p1.x) * (y - p1.y) / (p2.y - p1.y);
      }
    }
    std::sort(intersections, intersections + count);
    for (int i = 0; i < count; i += 2) {
      if (i + 1 < count) {
        SDL_RenderDrawLine(renderer.get(), intersections[i], y,
                           intersections[i + 1], y);
      }
    }
  }
}
