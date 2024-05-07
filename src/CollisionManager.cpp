#include "CollisionManager.h"

// Méthode pour vérifier la collision entre la balle et la grille
void CollisionManager::checkGridBallCollision(Grid& grid, Ball& ball) {
  int cell_size = grid.getCellSize();
  int cell_pos_x = ball.getPosX() / cell_size;
  int cell_pos_y = ball.getPosY() / cell_size;

  bool collisionDetected = false;
  float collisionVectorX = 0;
  float collisionVectorY = 0;

  for (int row = std::max(cell_pos_y - 1, 0);
       row <= std::min(cell_pos_y + 1, grid.getRows() - 1); ++row) {
    for (int col = std::max(cell_pos_x - 1, 0);
         col <= std::min(cell_pos_x + 1, grid.getCols() - 1); ++col) {
      Cell* cell = grid.getCell(row, col);
      if (cell && cell->rebondir()) {
        bool intersect_x =
            ball.getPosX() + ball.getRadius() >= (col * cell_size) &&
            ball.getPosX() - ball.getRadius() <= ((col + 1) * cell_size);
        bool intersect_y =
            ball.getPosY() + ball.getRadius() >= (row * cell_size) &&
            ball.getPosY() - ball.getRadius() <= ((row + 1) * cell_size);

        if (intersect_x && intersect_y) {
          std::cerr << "Collision : (" << row << ", " << col << ")\n";
          collisionDetected = true;

          float depth_x = std::min(
              abs(ball.getPosX() + ball.getRadius() - (col * cell_size)),
              abs(ball.getPosX() - ball.getRadius() - ((col + 1) * cell_size)));
          float depth_y = std::min(
              abs(ball.getPosY() + ball.getRadius() - (row * cell_size)),
              abs(ball.getPosY() - ball.getRadius() - ((row + 1) * cell_size)));

          if (depth_x < depth_y) {
            collisionVectorX +=
                (ball.getPosX() < col * cell_size) ? -depth_x : depth_x;
          } else {
            collisionVectorY +=
                (ball.getPosY() < row * cell_size) ? -depth_y : depth_y;
          }

          grid.hitCell(row, col);
        }
      }
    }
  }

  if (collisionDetected) {
    if (abs(collisionVectorX) > abs(collisionVectorY)) {
      ball.reverseVelocityX();
    } else {
      ball.reverseVelocityY();
    }
  }
}

void CollisionManager::checkPlatformBallCollision(Plateform& platform,
                                                  Ball& balle) {
  float distance_x =
      abs(balle.getPosX() - (platform.getPosX() + platform.getWidth() / 2));
  float distance_y =
      abs(balle.getPosY() - (platform.getPosY() + platform.getHeight() / 2));

  // Collision entre la balle et les bords de la fenetre
  if (distance_x > (platform.getWidth() / 2 + balle.getRadius())) {
    return;
  }
  if (distance_y > (platform.getHeight() / 2 + balle.getRadius())) {
    return;
  }

  if (distance_x <= (platform.getWidth() / 2)) {
    balle.reverseVelocityY();
  }
  if (distance_y <= (platform.getHeight() / 2)) {
    balle.reverseVelocityX();
  }

  float corner_distance = (distance_x - platform.getWidth() / 2) *
                              (distance_x - platform.getWidth() / 2) +
                          (distance_y - platform.getHeight() / 2) *
                              (distance_y - platform.getHeight() / 2);

  if (corner_distance <= (balle.getRadius() * balle.getRadius())) {
    balle.reverseVelocityX();
    balle.reverseVelocityY();
  }
}
