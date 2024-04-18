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
  pos_x_ = platformPosX + platformLength / 2 - radius_;
  pos_y_ = platformPosY - radius_ * 2;
}

void Ball::render(SDL_Renderer* renderer) {
  SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
  for (int y = -radius_; y <= radius_; y++)
    for (int x = -radius_; x <= radius_; x++)
      if (x * x + y * y <= radius_ * radius_)
        SDL_RenderDrawPoint(renderer, pos_x_ + x, pos_y_ + y);
}

bool Ball::updatePosition(float dt, int screenWidth, int screenHeight) {
  pos_x_ += speed_ * dt * velocity_x_;

  if ((pos_x_ - radius_ < 0)) {
    velocity_x_ = -velocity_x_;
    pos_x_ = radius_;
  }

  if (pos_x_ + radius_ > screenWidth) {
    velocity_x_ = -velocity_x_;
    pos_x_ = screenWidth - radius_;
  }

  pos_y_ += speed_ * dt * velocity_y_;

  if (pos_y_ - radius_ < 0) {
    velocity_y_ = -velocity_y_;
    pos_y_ = radius_;
  }

  // Rebond bord du bas
  /*if (pos_y_ + radius_ > screenHeight) {
    velocity_y_ = -velocity_y_;
    pos_y_ = screenHeight - radius_;
  }*/

  // Balle sous la plateforme = GAME OVER
  if (pos_y_ + radius_ > screenHeight) {
    return true;
  }

  return false;
}

void Ball::checkCollide(const Plateform p) {
  float distance_x = abs(pos_x_ - (p.getPosX() + p.getWidth() / 2));
  float distance_y = abs(pos_y_ - (p.getPosY() + p.getHeight() / 2));

  if (distance_x > (p.getWidth() / 2 + radius_)) {
    return;
  }
  if (distance_y > (p.getHeight() / 2 + radius_)) {
    return;
  }

  if (distance_x <= (p.getWidth() / 2)) {
    velocity_y_ *= -1;
  }
  if (distance_y <= (p.getHeight() / 2)) {
    velocity_x_ *= -1;
  }

  float corner_distance =
      (distance_x - p.getWidth() / 2) * (distance_x - p.getWidth() / 2) +
      (distance_y - p.getHeight() / 2) * (distance_y - p.getHeight() / 2);

  if (corner_distance <= (radius_ * radius_)) {
    velocity_x_ *= -1;
    velocity_y_ *= -1;
  }
}
