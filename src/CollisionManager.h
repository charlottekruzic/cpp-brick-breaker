#ifndef COLLISIONMANAGER_H
#define COLLISIONMANAGER_H

#include <memory>

#include "Ball.h"
#include "BonusMalus.h"
#include "Grid.h"
#include "Plateform.h"

class Ball;
class Plateform;
class Grid;
class BonusMalus;

class CollisionManager {
 public:
  // Méthode principale pour vérifier les collisions
  static void checkCollisions(
      Plateform& platform, std::shared_ptr<Ball>& ball,
      std::shared_ptr<Grid>& grid,
      std::unordered_set<std::shared_ptr<BonusMalus> >& bonus_maluses__);

 private:
  // Méthode pour vérifier la collision entre la plateforme et la balle
  static void checkPlatformBallCollision(Plateform& platform,
                                         std::shared_ptr<Ball>& ball);
  // Méthode pour vérifier la collision entre la balle et la grille
  static void checkGridBallCollision(std::shared_ptr<Grid>& grid,
                                     std::shared_ptr<Ball>& ball);

  static bool checkCollisionPlateformBonusMalus(
      Plateform& plateform, std::shared_ptr<BonusMalus>& bonusMalus);
};

#endif
