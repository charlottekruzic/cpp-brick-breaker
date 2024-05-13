#ifndef COLLISIONMANAGER_HPP
#define COLLISIONMANAGER_HPP

#include "CollisionManager.h"
#include "HexagonCell.h"
#include "SquareCell.h"
#include "TriangleCell.h"

template <typename Shape>
void CollisionManager<Shape>::checkCollisions(
    const Plateform& platform,
    const std::unordered_set<std::shared_ptr<Ball>>& balls,
    const std::shared_ptr<Grid<Shape>>& grid,
    std::unordered_set<std::shared_ptr<BonusMalus<Shape>>>& bonus_malus) {
  for (auto ball : balls) {
    checkPlatformBallCollision(platform, ball);
    checkGridBallCollision(grid, ball);
  }

  // Vérifier la collision entre la balle et les bonus/malus
  std::unordered_set<std::shared_ptr<BonusMalus<Shape>>>
      bonus_maluses_to_remove;

  for (auto bonusMalus : bonus_malus) {
    if (checkCollisionPlateformBonusMalus(platform, bonusMalus)) {
      // Collision détectée, gérer l'effet du bonus/malus
      bonusMalus->applyEffect();
      // Si applyEffect a été appelée, supprimer le bonus/malus de l'ensemble
      bonus_maluses_to_remove.insert(bonusMalus);
    }
  }
  for (auto bonusMalus : bonus_maluses_to_remove) {
    bonus_malus.erase(bonusMalus);
  }
}

// Méthode pour vérifier la collision entre la plateforme et la balle
template <typename Shape>
void CollisionManager<Shape>::checkPlatformBallCollision(
    const Plateform& platform, const std::shared_ptr<Ball>& ball) {
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

template <typename Shape>
bool CollisionManager<Shape>::checkCollisionPlateformBonusMalus(
    const Plateform& plateform,
    const std::shared_ptr<BonusMalus<Shape>>& bonusMalus) {
  // Récupérer les coordonnées de la plateforme
  int plateformLeft = plateform.getPosX();
  int plateformRight = plateform.getPosX() + plateform.getWidth();
  int plateformTop = plateform.getPosY();
  int plateformBottom = plateform.getPosY() + plateform.getHeight();

  // Récupérer les coordonnées du bonus/malus
  int bonusMalusLeft = bonusMalus->getX();
  int bonusMalusRight = bonusMalus->getX() + bonusMalus->getWidth();
  int bonusMalusTop = bonusMalus->getY();
  int bonusMalusBottom = bonusMalus->getY() + bonusMalus->getHeight();

  // Vérifier si les rectangles délimitant la plateforme et le bonus/malus
  // se chevauchent
  bool collision =
      (plateformLeft < bonusMalusRight) && (plateformRight > bonusMalusLeft) &&
      (plateformTop < bonusMalusBottom) && (plateformBottom > bonusMalusTop);

  return collision;
}

// Méthode pour vérifier la collision entre la balle et les cellules de la
// grille carrée
template <>
inline void CollisionManager<SquareCell>::checkGridBallCollision(
    const std::shared_ptr<Grid<SquareCell>>& grid,
    const std::shared_ptr<Ball>& ball) {
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

// Méthode pour vérifier la collision entre la balle et les cellules de la
// grille triangulaire
template <>
inline void CollisionManager<TriangleCell>::checkGridBallCollision(
    const std::shared_ptr<Grid<TriangleCell>>& grid,
    const std::shared_ptr<Ball>& ball) {
  for (int i = 0; i < grid->getRows(); i++) {
    for (int j = 0; j < grid->getCols(); j++) {
      Cell<TriangleCell>* cell = grid->getCell(i, j);
      if (cell && cell->rebondir()) {
        SDL_Point points[4] = {cell->getPoint(0), cell->getPoint(1),
                               cell->getPoint(2), cell->getPoint(3)};

        bool hit = false;
        for (int k = 0; k < 4; k++) {
          int next = (k + 1) % 4;
          if (isNear(ball->getPosX(), ball->getPosY(), points[k].x, points[k].y,
                     points[next].x, points[next].y, ball->getRadius())) {
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

// Méthode pour vérifier la collision entre la balle et les cellules de la
// grille hexagonale
template <>
inline void CollisionManager<HexagonCell>::checkGridBallCollision(
    const std::shared_ptr<Grid<HexagonCell>>& grid,
    const std::shared_ptr<Ball>& ball) {
  for (int i = 0; i < grid->getRows(); i++) {
    for (int j = 0; j < grid->getCols(); j++) {
      Cell<HexagonCell>* cell = grid->getCell(i, j);
      if (cell && cell->rebondir()) {
        // Récupération des points de l'hexagone
        SDL_Point points[7];
        for (int p = 0; p < 7; p++) {
          points[p] = cell->getPoint(p);
        }

        bool hit = false;
        // Calcule des collisions sur les 6 côtés
        for (int k = 0; k < 6; k++) {
          int next = (k + 1) % 6;
          if (isNear(ball->getPosX(), ball->getPosY(), points[k].x, points[k].y,
                     points[next].x, points[next].y, ball->getRadius())) {
            // Calcul de la normale
            float n_x = points[next].y - points[k].y;
            float n_y = points[k].x - points[next].x;
            float normLength = sqrt(n_x * n_x + n_y * n_y);
            n_x /= normLength;
            n_y /= normLength;

            // Calcul de la nouvelle vélocité (éviter que la balle accélère)
            float product =
                ball->getVelocityX() * n_x + ball->getVelocityY() * n_y;
            ball->setVelocityX(ball->getVelocityX() - 2 * product * n_x);
            ball->setVelocityY(ball->getVelocityY() - 2 * product * n_y);

            grid->hitCell(i, j);
            break;
          }
        }
      }
    }
  }
}

template <typename Shape>
bool CollisionManager<Shape>::isNear(const float px, const float py,
                                     const float x1, const float y1,
                                     const float x2, const float y2,
                                     const float radius) {
  float line_height = sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2));
  float distance;
  if (line_height < 0.001f) {
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

#endif