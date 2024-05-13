#include "TriangleCell.h"

#include <algorithm>
#include <memory>

TriangleCell::TriangleCell() {}

TriangleCell::TriangleCell(Orientation orientation)
    : orientation_(orientation) {}

void TriangleCell::draw(std::shared_ptr<SDL_Renderer>& renderer, int x, int y,
                        int cellWidth, int cellHeight, SDL_Color color) {
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

SDL_Point TriangleCell::getPoint(int i) {
  if (i >= 0 && i < points_.size()) {
    return points_[i];
  } else {
    return SDL_Point();
  }
}

void TriangleCell::fillTriangle(std::shared_ptr<SDL_Renderer>& renderer,
                                std::vector<SDL_Point>& points) {
  // Tri des points
  if (points[0].y > points[1].y) std::swap(points[0], points[1]);
  if (points[1].y > points[2].y) std::swap(points[1], points[2]);
  if (points[0].y > points[1].y) std::swap(points[0], points[1]);

  int totalHeight = points[2].y - points[0].y;

  // Remplissage du triangle
  for (int i = 0; i < totalHeight; i++) {
    bool second_half =
        i > points[1].y - points[0].y || points[1].y == points[0].y;
    int segmentHeight =
        second_half ? points[2].y - points[1].y : points[1].y - points[0].y;
    float alpha = (float)i / totalHeight;
    float beta = (float)(i - (second_half ? points[1].y - points[0].y : 0)) /
                 segmentHeight;

    int ax = points[0].x + (points[2].x - points[0].x) * alpha;
    int bx = second_half ? points[1].x + (points[2].x - points[1].x) * beta
                         : points[0].x + (points[1].x - points[0].x) * beta;

    if (ax > bx) std::swap(ax, bx);

    SDL_RenderDrawLine(renderer.get(), ax, points[0].y + i, bx,
                       points[0].y + i);
  }
}