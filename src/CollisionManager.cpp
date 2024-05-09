#include "CollisionManager.h"

#include <cmath>

// Méthode pour vérifier la collision entre la balle et la grille
void CollisionManager::checkGridBallCollision(Grid& grid, Ball* ball) {
  int radiusBall = ball->getRadius();
  float pos_xBall = ball->getPosX();
  float pos_yBall = ball->getPosY();

  int cell_size = grid.getCellSize();
  int cell_pos_x = pos_xBall / cell_size;
  int cell_pos_y = pos_yBall / cell_size;

  bool collisionDetected = false;
  float collisionVectorX = 0;
  float collisionVectorY = 0;

  for (int row = std::max(cell_pos_y - 1, 0);
       row <= std::min(cell_pos_y + 1, grid.getRows() - 1); ++row) {
    for (int col = std::max(cell_pos_x - 1, 0);
         col <= std::min(cell_pos_x + 1, grid.getCols() - 1); ++col) {
      Cell* cell = grid.getCell(row, col);
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

          grid.hitCell(row, col);
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
                                                  Ball* balle) {
  if (balle->getPosY() > platform.getPosY()) {
    return;
  }

  float distance_x =
      abs(balle->getPosX() - (platform.getPosX() + platform.getWidth() / 2));
  float distance_y =
      abs(balle->getPosY() - (platform.getPosY() + platform.getHeight() / 2));

  if (distance_x > (balle->getRadius() + platform.getWidth() / 2)) {
    return;
  }  // pas de collision entre
  if (distance_y > (balle->getRadius() + platform.getHeight() / 2)) {
    // (platform.getHeight() / 2 + balle.getRadius())) {
    return;
  }

  float corner_distance = (distance_x - platform.getWidth() / 2) *
                              (distance_x - platform.getWidth() / 2) +
                          (distance_y - platform.getHeight() / 2) *
                              (distance_y - platform.getHeight() / 2);

  if (corner_distance <= (balle->getRadius() * balle->getRadius())) {
    // Détection de la direction d'approche de la balle par rapport à la
    // plateforme
    bool from_left = balle->getPosX() < platform.getPosX();
    bool from_top = balle->getPosY() < platform.getPosY();

    // Si la balle vient du coin supérieur gauche ou inférieur droit
    if ((from_left && from_top) || (!from_left && !from_top)) {
      // Inverse la direction horizontale de la balle
      balle->reverseVelocityX();
    }
  }

  balle->reverseVelocityY();

  /*

  float distance_x =
     abs(balle.getPosX()  - (platform.getPosX() + platform.getWidth() / 2));
 // distance horizontale entre le centre de la balle et le centre de la
 // plateforme
 float distance_y =
     abs(balle.getPosY() - (platform.getPosY() + platform.getHeight() / 2));
 // distance verticale entre le centre de la balle et le centre de la
 // plateforme

 if (distance_x > (platform.getWidth() / 2 + balle.getRadius())) {
   return;
 }  // pas de collision entre
 if (distance_y > balle.getRadius()) {
   // (platform.getHeight() / 2 + balle.getRadius())) {
   return;
 }

 // float corner_distance = (distance_x - platform.getWidth() / 2) *
 //                             (distance_x - platform.getWidth() / 2) +
 //                         (distance_y - platform.getHeight() / 2) *
 //                             (distance_y - platform.getHeight() / 2);
 //
 // // if (corner_distance <= (balle.getRadius() * balle.getRadius())) {
 // //   balle.reverseVelocityX();
 // //   balle.reverseVelocityY();
 // // } else {
 // balle.reverseVelocityY();
 // // }
 //
 // // if (distance_x <= (platform.getWidth() / 2 + balle.getRadius())) {
 //
 // //}
 // // if (distance_y <= balle.getRadius()) {
 // //(platform.getHeight() / 2 + balle.getRadius())) {
 // // balle.reverseVelocityX();
 // //}

 // Calcul de la distance au coin
 float corner_distance = (distance_x - platform.getWidth() / 2) *
                             (distance_x - platform.getWidth() / 2) +
                         (distance_y - platform.getHeight() / 2) *
                             (distance_y - platform.getHeight() / 2);

 // Gestion des rebonds spécifiques sur les coins
 if (corner_distance <= (balle.getRadius() * balle.getRadius())) {
   // Détection de la direction d'approche de la balle par rapport à la
   // plateforme
   bool from_left = balle.getPosX() < platform.getPosX();
   bool from_top = balle.getPosY() < platform.getPosY();

   // Si la balle vient du coin supérieur gauche ou inférieur droit
   if ((from_left && from_top) || (!from_left && !from_top)) {
     // Inverse la direction horizontale de la balle
     balle.reverseVelocityX();
   }
 }
 balle.reverseVelocityY();
 */
}

bool CollisionManager::checkCollisionBallBonusMalus(Ball* ball,
                                                    BonusMalus* bonusMalus) {
  // Vérifiez la collision entre la balle et le bonus/malus
  int ballLeft = ball->getPosX() - ball->getRadius();
  int ballRight = ball->getPosX() + ball->getRadius();
  int ballTop = ball->getPosY() - ball->getRadius();
  int ballBottom = ball->getPosY() + ball->getRadius();

  int bonusMalusLeft = bonusMalus->getX();
  int bonusMalusRight =
      bonusMalus->getX() +
      bonusMalus
          ->getWidth();  // Suppose que BonusMalus a une méthode getWidth()
  int bonusMalusTop = bonusMalus->getY();
  int bonusMalusBottom =
      bonusMalus->getY() +
      bonusMalus
          ->getHeight();  // Suppose que BonusMalus a une méthode getHeight()

  // Vérifiez si les rectangles délimitant la balle et le bonus/malus se
  // chevauchent
  return ballLeft < bonusMalusRight && ballRight > bonusMalusLeft &&
         ballTop < bonusMalusBottom && ballBottom > bonusMalusTop;
}
