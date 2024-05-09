#ifndef COLLISIONMANAGER_H
#define COLLISIONMANAGER_H

#include "Ball.h"
#include "Grid.h"
#include "Plateform.h"

class Ball;
class Plateform;
class Grid;

class CollisionManager {
 public:
  // Méthode principale pour vérifier les collisions
  static void checkCollisions(Plateform& platform, Ball* ball, Grid& grid,
                              std::vector<BonusMalus*>& bonus_maluses__) {
    checkPlatformBallCollision(platform, ball);
    // checkWindowBallCollision(bounds, ball);
    checkGridBallCollision(grid, ball);
    // Vérifier la collision entre la balle et les bonus/malus
    // Vérifier la collision entre la balle et les bonus/malus
    for (auto bonusMalus : bonus_maluses__) {
      if (checkCollisionBallBonusMalus(ball, bonusMalus)) {
        // Collision détectée, gérer l'effet du bonus/malus
        bonusMalus->applyEffect();
        // // Si applyEffect a été appelée, supprimer le bonus/malus de la liste
        // bonus_maluses__.erase(std::remove(bonus_maluses__.begin(),
        //                                   bonus_maluses__.end(), bonusMalus),
        //                       bonus_maluses__.end());
        // // Libérer la mémoire associée au bonus/malus
        // delete bonusMalus;
      }
    }
  }

 private:
  // Méthode pour vérifier la collision entre la plateforme et la balle
  static void checkPlatformBallCollision(Plateform& platform, Ball* ball);
  // Méthode pour vérifier la collision entre la balle et la grille
  static void checkGridBallCollision(Grid& grid, Ball* ball);

  static bool checkCollisionBallBonusMalus(Ball* ball, BonusMalus* bonusMalus);
};

#endif
