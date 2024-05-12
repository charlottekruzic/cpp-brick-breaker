#ifndef COLLISIONMANAGER_H
#define COLLISIONMANAGER_H

#include <memory>

#include "Ball.h"
#include "Grid.h"
#include "Plateform.h"
#include "SquareCell.h"
#include "TriangleCell.h"
// #include "bonus_malus/BonusMalus.h"

class Ball;
class Plateform;
template <typename Shape>
class Grid;
class BonusMalus;

template <typename Shape>
class CollisionManager {
 public:
  // Méthode principale pour vérifier les collisions
  static void checkCollisions(
      Plateform& platform, std::unordered_set<std::shared_ptr<Ball>>& balls,
      std::shared_ptr<Grid<Shape>>& grid/*,
      std::unordered_set<std::shared_ptr<BonusMalus>>& bonus_maluses__*/);

 private:
  // Méthode pour vérifier la collision entre la plateforme et la balle
  static void checkPlatformBallCollision(Plateform& platform,
                                         std::shared_ptr<Ball>& ball);
  // Méthode pour vérifier la collision entre la balle et la grille
  static void checkGridBallCollision(std::shared_ptr<Grid<Shape>>& grid,
                                     std::shared_ptr<Ball>& ball);

  // static bool checkCollisionPlateformBonusMalus(
  // Plateform& plateform, std::shared_ptr<BonusMalus>& bonusMalus);
};

// Spécialisation partielle pour SquareCell
template <>
class CollisionManager<SquareCell> {
 public:
  static void checkCollisions(Plateform& platform,
                              std::unordered_set<std::shared_ptr<Ball>>& balls,
                              std::shared_ptr<Grid<SquareCell>>& grid) {
    for (auto ball : balls) {
      checkPlatformBallCollision(platform, ball);
      // checkWindowBallCollision(bounds, ball);
      checkGridBallCollision(grid, ball);
    }

    // Vérifier la collision entre la balle et les bonus/malus
    std::unordered_set<std::shared_ptr<BonusMalus>> bonus_maluses_to_remove;

    /*for (auto bonusMalus : bonus_malus) {
      if (checkCollisionPlateformBonusMalus(platform, bonusMalus)) {
        // Collision détectée, gérer l'effet du bonus/malus
        bonusMalus->applyEffect();
        // Si applyEffect a été appelée, supprimer le bonus/malus de l'ensemble
        bonus_maluses_to_remove.insert(bonusMalus);
      }
    }
    for (auto bonusMalus : bonus_maluses_to_remove) {
      bonus_malus.erase(bonusMalus);
    }*/
  }

 private:
  // Méthode pour vérifier la collision entre la plateforme et la balle
  static void checkPlatformBallCollision(Plateform& platform,
                                         std::shared_ptr<Ball>& ball) {
    if (ball->getPosY() > platform.getPosY()) {
      return;
    }

    float distance_x =
        abs(ball->getPosX() - (platform.getPosX() + platform.getWidth() / 2));
    float distance_y =
        abs(ball->getPosY() - (platform.getPosY() + platform.getHeight() / 2));

    if (distance_x > (ball->getRadius() + platform.getWidth() / 2)) {
      return;
    }  // pas de collision entre
    if (distance_y > (ball->getRadius() + platform.getHeight() / 2)) {
      // (platform.getHeight() / 2 + balle.getRadius())) {
      return;
    }

    float corner_distance = (distance_x - platform.getWidth() / 2) *
                                (distance_x - platform.getWidth() / 2) +
                            (distance_y - platform.getHeight() / 2) *
                                (distance_y - platform.getHeight() / 2);

    if (corner_distance <= (ball->getRadius() * ball->getRadius())) {
      // Détection de la direction d'approche de la balle par rapport à la
      // plateforme
      bool from_left = ball->getPosX() < platform.getPosX();
      bool from_top = ball->getPosY() < platform.getPosY();

      // Si la balle vient du coin supérieur gauche ou inférieur droit
      if ((from_left && from_top) || (!from_left && !from_top)) {
        // Inverse la direction horizontale de la balle
        ball->reverseVelocityX();
      }
    }

    ball->reverseVelocityY();

    // Direction balle en fonction de l'endroit de l'impact sur la plateforme
    float impact_point =
        (ball->getPosX() - platform.getPosX()) / (platform.getWidth() / 2) - 1;

    // Calcule vitesse et vélocite pour ne pas accelerer la balle
    float new_velocity_x = -impact_point * ball->getVelocityY();
    float old_speed = std::hypot(ball->getVelocityX(), ball->getVelocityY());
    float new_speed = std::hypot(new_velocity_x, ball->getVelocityY());

    if (new_speed != 0) {
      ball->setVelocityX(new_velocity_x * old_speed / new_speed);
      ball->setVelocityY(ball->getVelocityY() * old_speed / new_speed);
    }
  }
  // Méthode pour vérifier la collision entre la balle et la grille
  static void checkGridBallCollision(std::shared_ptr<Grid<SquareCell>>& grid,
                                     std::shared_ptr<Ball>& ball) {
    int radiusBall = ball->getRadius();
    float pos_xBall = ball->getPosX();
    float pos_yBall = ball->getPosY();

    int cell_size = grid->getCellSize();
    int cell_pos_x = pos_xBall / cell_size;
    int cell_pos_y = pos_yBall / cell_size;

    bool collisionDetected = false;
    float collisionVectorX = 0;
    float collisionVectorY = 0;

    for (int row = std::max(cell_pos_y - 1, 0);
         row <= std::min(cell_pos_y + 1, grid->getRows() - 1); ++row) {
      for (int col = std::max(cell_pos_x - 1, 0);
           col <= std::min(cell_pos_x + 1, grid->getCols() - 1); ++col) {
        Cell<SquareCell>* cell = grid->getCell(row, col);
        if (cell && cell->rebondir()) {
          bool intersect_x = pos_xBall + radiusBall >= (col * cell_size) &&
                             pos_xBall - radiusBall <= ((col + 1) * cell_size);
          bool intersect_y = pos_yBall + radiusBall >= (row * cell_size) &&
                             pos_yBall - radiusBall <= ((row + 1) * cell_size);

          if (intersect_x && intersect_y) {
            collisionDetected = true;

            float depth_x =
                std::min(abs(pos_xBall + radiusBall - (col * cell_size)),
                         abs(pos_xBall - radiusBall - ((col + 1) * cell_size)));
            float depth_y =
                std::min(abs(pos_yBall + radiusBall - (row * cell_size)),
                         abs(pos_yBall - radiusBall - ((row + 1) * cell_size)));

            if (depth_x < depth_y) {
              collisionVectorX +=
                  (pos_xBall < col * cell_size) ? -depth_x : depth_x;
            } else {
              collisionVectorY +=
                  (pos_yBall < row * cell_size) ? -depth_y : depth_y;
            }

            grid->hitCell(row, col);
          }
        }
      }
    }

    if (collisionDetected) {
      if (abs(collisionVectorX) > abs(collisionVectorY)) {
        ball->reverseVelocityX();
      } else {
        ball->reverseVelocityY();
      }
    }
  }
};

// Spécialisation partielle pour TriangleCell
template <>
class CollisionManager<TriangleCell> {
 public:
  static void checkCollisions(Plateform& platform,
                              std::unordered_set<std::shared_ptr<Ball>>& balls,
                              std::shared_ptr<Grid<TriangleCell>>& grid) {
    for (auto ball : balls) {
      checkPlatformBallCollision(platform, ball);
      // checkWindowBallCollision(bounds, ball);
      checkGridBallCollision(grid, ball);
    }

    // Vérifier la collision entre la balle et les bonus/malus
    std::unordered_set<std::shared_ptr<BonusMalus>> bonus_maluses_to_remove;
    /*
    for (auto bonusMalus : bonus_maluses__) {
      if (checkCollisionPlateformBonusMalus(platform, bonusMalus)) {
        // Collision détectée, gérer l'effet du bonus/malus
        bonusMalus->applyEffect();
        // Si applyEffect a été appelée, supprimer le bonus/malus de l'ensemble
        bonus_maluses_to_remove.insert(bonusMalus);
      }
    }
    for (auto bonusMalus : bonus_maluses_to_remove) {
      bonus_maluses__.erase(bonusMalus);
    }
    */
  }

 private:
  // Méthode pour vérifier la collision entre la plateforme et la balle
  static void checkPlatformBallCollision(Plateform& platform,
                                         std::shared_ptr<Ball>& ball) {
    if (ball->getPosY() > platform.getPosY()) {
      return;
    }

    float distance_x =
        abs(ball->getPosX() - (platform.getPosX() + platform.getWidth() / 2));
    float distance_y =
        abs(ball->getPosY() - (platform.getPosY() + platform.getHeight() / 2));

    if (distance_x > (ball->getRadius() + platform.getWidth() / 2)) {
      return;
    }  // pas de collision entre
    if (distance_y > (ball->getRadius() + platform.getHeight() / 2)) {
      // (platform.getHeight() / 2 + balle.getRadius())) {
      return;
    }

    float corner_distance = (distance_x - platform.getWidth() / 2) *
                                (distance_x - platform.getWidth() / 2) +
                            (distance_y - platform.getHeight() / 2) *
                                (distance_y - platform.getHeight() / 2);

    if (corner_distance <= (ball->getRadius() * ball->getRadius())) {
      // Détection de la direction d'approche de la balle par rapport à la
      // plateforme
      bool from_left = ball->getPosX() < platform.getPosX();
      bool from_top = ball->getPosY() < platform.getPosY();

      // Si la balle vient du coin supérieur gauche ou inférieur droit
      if ((from_left && from_top) || (!from_left && !from_top)) {
        // Inverse la direction horizontale de la balle
        ball->reverseVelocityX();
      }
    }

    ball->reverseVelocityY();

    // Direction balle en fonction de l'endroit de l'impact sur la plateforme
    float impact_point =
        (ball->getPosX() - platform.getPosX()) / (platform.getWidth() / 2) - 1;

    // Calcule vitesse et vélocite pour ne pas accelerer la balle
    float new_velocity_x = -impact_point * ball->getVelocityY();
    float old_speed = std::hypot(ball->getVelocityX(), ball->getVelocityY());
    float new_speed = std::hypot(new_velocity_x, ball->getVelocityY());

    if (new_speed != 0) {
      ball->setVelocityX(new_velocity_x * old_speed / new_speed);
      ball->setVelocityY(ball->getVelocityY() * old_speed / new_speed);
    }
  }
  // Méthode pour vérifier la collision entre la balle et la grille
  static void checkGridBallCollision(std::shared_ptr<Grid<TriangleCell>>& grid,
                                     std::shared_ptr<Ball>& ball) {
    for (int i = 0; i < grid->getRows(); i++) {
      for (int j = 0; j < grid->getCols(); j++) {
        Cell<TriangleCell>* cell = grid->getCell(i, j);
        if (cell && cell->rebondir()) {
          // TriangleCell* triangleCell = dynamic_cast<TriangleCell*>(cell);
          SDL_Point points[4] = {cell->getPoint(0), cell->getPoint(1),
                                 cell->getPoint(2), cell->getPoint(3)};

          bool hit = false;
          for (int k = 0; k < 4; k++) {
            int next = (k + 1) % 4;
            if (isNear(ball->getPosX(), ball->getPosY(), points[k].x,
                       points[k].y, points[next].x, points[next].y,
                       ball->getRadius())) {
              hit = true;

              // Direction collision
              float dx = ball->getVelocityX();
              float dy = ball->getVelocityY();

              if ((k == 0 || k == 2) &&
                  fabs(dy) > fabs(dx)) {  // collision horizontale
                ball->reverseVelocityY();
              } else if ((k == 1 || k == 3) &&
                         fabs(dx) > fabs(dy)) {  // collision verticale
                ball->reverseVelocityX();
              } else {
                ball->reverseVelocityX();
                ball->reverseVelocityY();
              }
              // Détruit cellule
              grid->hitCell(i, j);
              break;
            }
          }
        }
      }
    }
  }

  static bool isNear(float px, float py, float x1, float y1, float x2, float y2,
                     float radius) {
    float line_height = sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2));
    float distance;
    if (line_height < 0) {
      distance = sqrt(pow(px - x1, 2) + pow(py - y1, 2));
    } else {
      float u = ((px - x1) * (x2 - x1) + (py - y1) * (y2 - y1)) /
                (line_height * line_height);
      if (u < 0.0f || u > 1.0f) {
        distance = std::min(sqrt(pow(px - x1, 2) + pow(py - y1, 2)),
                            sqrt(pow(px - x2, 2) + pow(py - y2, 2)));
      } else {
        float ix = x1 + u * (x2 - x1);
        float iy = y1 + u * (y2 - y1);
        distance = sqrt(pow(px - ix, 2) + pow(py - iy, 2));
      }
    }
    return distance <= radius;
  }
};

// #include "CollisionManager.hpp"

#endif
