#include "CollisionManager.h"

#include <cmath>

void CollisionManager::checkCollisions(
    Plateform& platform, std::shared_ptr<Ball>& ball,
    std::shared_ptr<Grid>& grid,
    std::unordered_set<std::shared_ptr<BonusMalus>>& bonus_maluses__) {
  checkPlatformBallCollision(platform, ball);
  // checkWindowBallCollision(bounds, ball);
  checkGridBallCollision(grid, ball);
  // Vérifier la collision entre la balle et les bonus/malus
  std::unordered_set<std::shared_ptr<BonusMalus>> bonus_maluses_to_remove;

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
}

bool isNear(float px, float py, float x1, float y1, float x2, float y2,
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

// Méthode pour vérifier la collision entre la balle et la grille
void CollisionManager::checkGridBallCollision(std::shared_ptr<Grid>& grid,
                                              std::shared_ptr<Ball>& ball) {
  for (int i = 0; i < grid->getRows(); i++) {
    for (int j = 0; j < grid->getCols(); j++) {
      Cell* cell = grid->getCell(i, j);
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
