#ifndef COLLISIONMANAGER_H
#define COLLISIONMANAGER_H

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
  static void checkCollisions(Plateform& platform, Ball* ball, Grid& grid,
                              std::unordered_set<BonusMalus*>& bonus_maluses__);

 private:
  // Méthode pour vérifier la collision entre la plateforme et la balle
  static void checkPlatformBallCollision(Plateform& platform, Ball* ball);
  // Méthode pour vérifier la collision entre la balle et la grille
  static void checkGridBallCollision(Grid& grid, Ball* ball);

  static bool checkCollisionPlateformBonusMalus(Plateform& plateform,
                                                BonusMalus* bonusMalus);
};

#endif
