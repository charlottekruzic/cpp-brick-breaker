#include "BasicBrick.h"

void BasicBrick::fillTriangle(SDL_Renderer* renderer, SDL_Point* points) {
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

    SDL_RenderDrawLine(renderer, ax, points[0].y + i, bx, points[0].y + i);
  }
}

void BasicBrick::renderCell(std::shared_ptr<SDL_Renderer>& renderer, int x,
                            int y, int cellWidth, int cellHeight) {
  if (orientation_ == Orientation::UP) {
    points[0] = {x + cellWidth / 2, y};          // Pointe haut
    points[1] = {x, y + cellWidth};              // Bas gauche
    points[2] = {x + cellWidth, y + cellWidth};  // Bas droit

  } else {                                           // Orientation::DOWN
    points[0] = {x, y};                              // Haut gauche
    points[1] = {x + cellWidth, y};                  // Haut droit
    points[2] = {x + cellWidth / 2, y + cellWidth};  // Pointe bas
  }
  points[3] = points[0];

  // Remplissage
  SDL_Color color = ColorUtils::convertColor(getColor());
  SDL_SetRenderDrawColor(renderer.get(), color.r, color.g, color.b, color.a);
  SDL_RenderDrawLines(renderer.get(), points, 4);
  BasicBrick::fillTriangle(renderer.get(), points);

  // Ajoute contours
  SDL_SetRenderDrawColor(renderer.get(), 0, 0, 0, 255);
  SDL_RenderDrawLines(renderer.get(), points, 4);
}

BasicBrick::Orientation BasicBrick::getOrientation() const {
  return orientation_;
}