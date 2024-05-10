#ifndef COLLISIONMANAGER_H
#define COLLISIONMANAGER_H

#include <memory>

#include "Ball.h"
#include "Grid.h"
#include "Plateform.h"
#include "Shape.h"
#include "bonus_malus/BonusMalus.h"

class Ball;
class Plateform;
template <typename SquareCell>
class Grid;
class BonusMalus;

class CollisionManager {
 public:
  // Méthode principale pour vérifier les collisions
  static void checkCollisions(
      Plateform& platform, std::unordered_set<std::shared_ptr<Ball>>& balls,
      std::shared_ptr<Grid<SquareCell>>& grid,
      std::unordered_set<std::shared_ptr<BonusMalus>>& bonus_maluses__);

 private:
  // Méthode pour vérifier la collision entre la plateforme et la balle
  static void checkPlatformBallCollision(Plateform& platform,
                                         std::shared_ptr<Ball>& ball);
  // Méthode pour vérifier la collision entre la balle et la grille
  static void checkGridBallCollision(std::shared_ptr<Grid<SquareCell>>& grid,
                                     std::shared_ptr<Ball>& ball);

  static bool checkCollisionPlateformBonusMalus(
      Plateform& plateform, std::shared_ptr<BonusMalus>& bonusMalus);
};

#endif
