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
  static void checkCollisions(
      Plateform& platform, Ball* ball, Grid& grid,
      std::unordered_set<BonusMalus*>& bonus_maluses__) {
    checkPlatformBallCollision(platform, ball);
    // checkWindowBallCollision(bounds, ball);
    checkGridBallCollision(grid, ball);
    // Vérifier la collision entre la balle et les bonus/malus
    std::unordered_set<BonusMalus*> bonus_maluses_to_remove;
    for (auto bonusMalus : bonus_maluses__) {
      if (checkCollisionBallBonusMalus(ball, bonusMalus)) {
        // Collision détectée, gérer l'effet du bonus/malus
        bonusMalus->applyEffect();
        // Si applyEffect a été appelée, supprimer le bonus/malus de l'ensemble
        bonus_maluses_to_remove.insert(bonusMalus);
      }
    }
    for (auto bonusMalus : bonus_maluses_to_remove) {
      bonus_maluses__.erase(bonusMalus);
      delete bonusMalus;
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
