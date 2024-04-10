#include "Ball.h"

Ball::Ball()
    : radius_(10),
      speed_(10),
      pos_x_(25),
      pos_y_(25),
      velocity_x_(1),
      velocity_y_(-1) {}

Ball::Ball(int radius, int speed, float platformPosX, float platformPosY,
           int platformLength, float velocity_x, float velocity_y)
    : radius_(radius),
      speed_(speed),
      velocity_x_(velocity_x),
      velocity_y_(velocity_y) {
  pos_x_ = platformPosX + platformLength / 2;
  pos_y_ = platformPosY - radius_ * 2;
}

void Ball::render(SDL_Renderer* renderer) {
  SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
  SDL_Rect ballRect = {pos_x_, pos_y_, 2 * radius_, 2 * radius_};
  SDL_RenderFillRect(renderer, &ballRect);
}

void Ball::updatePosition(float dt, int screenWidth, int screenHeight) {
  pos_x_ += speed_ * dt * velocity_x_;

  if ((pos_x_ < 0)) {
    velocity_x_ = -velocity_x_;
    pos_x_ = 0;
  }

  if (pos_x_ + radius_ * 2 > screenWidth) {
    velocity_x_ = -velocity_x_;
    pos_x_ = screenWidth - radius_ * 2;
  }

  pos_y_ += speed_ * dt * velocity_y_;

  if (pos_y_ <= 0) {
    velocity_y_ = -velocity_y_;
    pos_y_ = 0;
  }

  // TODO : Supprimer et retourner une erreur = fin de jeu perdu
  if (pos_y_ + radius_ * 2 > screenHeight) {
    velocity_y_ = -velocity_y_;
    pos_y_ = screenHeight - radius_ * 2;
  }
}

void Ball::checkCollide(const Plateform p) {
  if ((pos_y_ + radius_ * 2) >= p.getPosY() &&
      pos_y_ <= (p.getPosY() + p.getHeight()) &&
      (pos_x_ + radius_ * 2) >= p.getPosX() &&
      pos_x_ <= p.getPosX() + p.getWidth()) {
    velocity_y_ *= -1;
  }
}
