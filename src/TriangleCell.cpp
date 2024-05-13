#include "TriangleCell.h"

#include <algorithm>
#include <memory>

TriangleCell::TriangleCell() {
  points_.resize(4);
  for (int i = 0; i < 4; ++i) {
    points_[i] = SDL_Point();
  }
}

TriangleCell::TriangleCell(Orientation orientation)
    : orientation_(orientation) {
  points_.resize(4);
  for (int i = 0; i < 4; ++i) {
    points_[i] = SDL_Point();
  }
}

void TriangleCell::draw(const std::shared_ptr<SDL_Renderer>& renderer,
                        const int x, const int y, const int cellWidth,
                        const int cellHeight, const SDL_Color color) {
  points_.clear();

  if (orientation_ == Orientation::UP) {
    points_.push_back({x + cellWidth / 2, y});          // Pointe haut
    points_.push_back({x, y + cellWidth});              // Bas gauche
    points_.push_back({x + cellWidth, y + cellWidth});  // Bas droit

  } else {                                                  // Orientation::DOWN
    points_.push_back({x, y});                              // Haut gauche
    points_.push_back({x + cellWidth, y});                  // Haut droit
    points_.push_back({x + cellWidth / 2, y + cellWidth});  // Pointe bas
  }

  points_.push_back(points_[0]);

  // Remplissage
  SDL_SetRenderDrawColor(renderer.get(), color.r, color.g, color.b, color.a);
  SDL_RenderDrawLines(renderer.get(), points_.data(), points_.size());
  fillTriangle(renderer, points_);

  // Ajoute contours
  SDL_SetRenderDrawColor(renderer.get(), 0, 0, 0, 255);
  SDL_RenderDrawLines(renderer.get(), points_.data(), points_.size());
}

SDL_Point TriangleCell::getPoint(const int i) const {
  if (i >= 0 && i < points_.size()) {
    return points_[i];
  } else {
    return points_[0];
  }
}

void TriangleCell::fillTriangle(const std::shared_ptr<SDL_Renderer>& renderer,
                                const std::vector<SDL_Point>& points) const {
  std::vector<SDL_Point> sortedPoints = points;

  // Tri des points
  if (sortedPoints[0].y > sortedPoints[1].y)
    std::swap(sortedPoints[0], sortedPoints[1]);
  if (sortedPoints[1].y > sortedPoints[2].y)
    std::swap(sortedPoints[1], sortedPoints[2]);
  if (sortedPoints[0].y > sortedPoints[1].y)
    std::swap(sortedPoints[0], sortedPoints[1]);

  int totalHeight = sortedPoints[2].y - sortedPoints[0].y;

  // Remplissage du triangle
  for (int i = 0; i < totalHeight; i++) {
    bool second_half = i > sortedPoints[1].y - sortedPoints[0].y ||
                       sortedPoints[1].y == sortedPoints[0].y;
    int segmentHeight = second_half ? sortedPoints[2].y - sortedPoints[1].y
                                    : sortedPoints[1].y - sortedPoints[0].y;
    float alpha = (float)i / totalHeight;
    float beta =
        (float)(i - (second_half ? sortedPoints[1].y - sortedPoints[0].y : 0)) /
        segmentHeight;

    int ax =
        sortedPoints[0].x + (sortedPoints[2].x - sortedPoints[0].x) * alpha;
    int bx = second_half ? sortedPoints[1].x +
                               (sortedPoints[2].x - sortedPoints[1].x) * beta
                         : sortedPoints[0].x +
                               (sortedPoints[1].x - sortedPoints[0].x) * beta;

    if (ax > bx) std::swap(ax, bx);

    SDL_RenderDrawLine(renderer.get(), ax, sortedPoints[0].y + i, bx,
                       sortedPoints[0].y + i);
  }
}
