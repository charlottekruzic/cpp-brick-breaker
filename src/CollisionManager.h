#ifndef COLLISIONMANAGER_H
#define COLLISIONMANAGER_H

#include <memory>
#include <unordered_set>

// #include "Ball.h"
// #include "Grid.h"
// #include "Plateform.h"
// #include "SquareCell.h"
// #include "TriangleCell.h"
// #include "bonus_malus/BonusMalus.h"

class Ball;
class Plateform;
template <typename Shape>
class Grid;
template <typename Shape>
class BonusMalus;

template <typename Shape>
class CollisionManager {
 public:
  // Méthode principale pour vérifier les collisions
  static void checkCollisions(
      Plateform& platform, std::unordered_set<std::shared_ptr<Ball>>& balls,
      std::shared_ptr<Grid<Shape>>& grid,
      std::unordered_set<std::shared_ptr<BonusMalus<Shape>>>& bonus_maluses__);

 private:
  // Méthode pour vérifier la collision entre la plateforme et la balle
  static void checkPlatformBallCollision(Plateform& platform,
                                         std::shared_ptr<Ball>& ball);
  // Méthode pour vérifier la collision entre la balle et la grille
  static void checkGridBallCollision(std::shared_ptr<Grid<Shape>>& grid,
                                     std::shared_ptr<Ball>& ball);

  static bool checkCollisionPlateformBonusMalus(
      Plateform& plateform, std::shared_ptr<BonusMalus<Shape>>& bonusMalus);

  static bool isNear(float px, float py, float x1, float y1, float x2, float y2,
                     float radius);
};

#include "CollisionManager.hpp"

#endif
