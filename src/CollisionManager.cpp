#include "CollisionManager.h"

#include <cmath>

void CollisionManager::checkCollisions(
    Plateform& platform, std::unordered_set<std::shared_ptr<Ball>>& balls,
    std::shared_ptr<Grid>& grid,
    std::unordered_set<std::shared_ptr<BonusMalus>>& bonus_malus) {
  for (auto ball : balls) {
    checkPlatformBallCollision(platform, ball);
    // checkWindowBallCollision(bounds, ball);
    checkGridBallCollision(grid, ball);
  }

  // Vérifier la collision entre la balle et les bonus/malus
  std::unordered_set<std::shared_ptr<BonusMalus>> bonus_maluses_to_remove;

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

// Méthode pour vérifier la collision entre la balle et la grille
void CollisionManager::checkGridBallCollision(std::shared_ptr<Grid>& grid,
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
      Cell* cell = grid->getCell(row, col);
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

void CollisionManager::checkPlatformBallCollision(Plateform& platform,
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

bool CollisionManager::checkCollisionPlateformBonusMalus(
    Plateform& plateform, std::shared_ptr<BonusMalus>& bonusMalus) {
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
