#ifndef COLLISIONMANAGER_H
#define COLLISIONMANAGER_H

#include <memory>
#include <unordered_set>

class Ball;
class Plateform;
template <typename Shape>
class Grid;
template <typename Shape>
class BonusMalus;

/**
 * @brief Classe utilitaire pour gérer les collisions
 * @tparam Shape Type de cellule de la grille
 */
template <typename Shape>
class CollisionManager {
 public:
  /**
   * @brief Méthode pour vérifier les collisions entre les différentes entités
   * du jeu
   * @param platform Plateforme du jeu
   * @param balls Ensemble des balles du jeu
   * @param grid Grille du jeu
   * @param bonus_malus Ensemble des bonus/malus du jeu
   * @return void
   */
  static void checkCollisions(
      const Plateform& platform,
      const std::unordered_set<std::shared_ptr<Ball>>& balls,
      const std::shared_ptr<Grid<Shape>>& grid,
      std::unordered_set<std::shared_ptr<BonusMalus<Shape>>>& bonus_malus);

 private:
  /**
   * @brief Méthode pour vérifier la collision entre la plateforme et la balle
   * @param platform Plateforme du jeu
   * @param ball Balle du jeu
   * @return void
   */
  static void checkPlatformBallCollision(const Plateform& platform,
                                         const std::shared_ptr<Ball>& ball);

  /**
   * @brief Méthode pour vérifier la collision entre la balle et la grille
   * @param grid Grille du jeu
   * @param ball Balle du jeu
   * @return void
   */
  static void checkGridBallCollision(const std::shared_ptr<Grid<Shape>>& grid,
                                     const std::shared_ptr<Ball>& ball);

  /**
   * @brief Méthode pour vérifier la collision entre la plateforme et un
   * bonus/malus
   * @param plateform Plateforme du jeu
   * @param bonusMalus Bonus/Malus du jeu
   * @return true si il y a collision, false sinon
   */
  static bool checkCollisionPlateformBonusMalus(
      const Plateform& plateform,
      const std::shared_ptr<BonusMalus<Shape>>& bonusMalus);

  /**
   * @brief Méthode pour vérifier si la balle est proche d'un segment
   * @param px Position x de la balle
   * @param py Position y de la balle
   * @param x1 Position x du premier point du segment
   * @param y1 Position y du premier point du segment
   * @param x2 Position x du deuxième point du segment
   * @param y2 Position y du deuxième point du segment
   * @param radius Rayon de la balle
   * @return true si la balle est proche du segment, false sinon
   * @note La méthode est utilisée pour détecter les collisions entre la balle
   * et les cellules de la grille de type TriangleCell et HexagonCell.
   */
  static bool isNear(const float px, const float py, const float x1,
                     const float y1, const float x2, const float y2,
                     const float radius);
};

#include "CollisionManager.hpp"

#endif
