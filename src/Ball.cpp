#include "Ball.h"

#include "bricks/Brick.h"

Ball::Ball()
    : radius_(10),
      speed_(10),
      pos_x_(25),
      pos_y_(25),
      velocity_x_(1),
      velocity_y_(-1) {}

Ball::Ball(const int radius, const int speed, const float platformPosX,
           const float platformPosY, const int platformLength,
           const float velocity_x, const float velocity_y)
    : radius_(radius),
      speed_(speed),
      velocity_x_(velocity_x),
      velocity_y_(velocity_y) {
  pos_x_ = platformPosX + platformLength / 2 - radius_ * 2;
  pos_y_ = platformPosY - radius_ * 2;
}

void Ball::render(const std::shared_ptr<SDL_Renderer>& renderer) {
  SDL_SetRenderDrawColor(renderer.get(), 255, 255, 255, 255);
  for (int y = -radius_; y <= radius_; y++)
    for (int x = -radius_; x <= radius_; x++)
      if (x * x + y * y <= radius_ * radius_)
        SDL_RenderDrawPoint(renderer.get(), pos_x_ + x, pos_y_ + y);
}

bool Ball::updatePosition(const float dt, const int screenWidth,
                          const int screenHeight) {
  prev_pos_x_ = pos_x_;
  prev_pos_y_ = pos_y_;

  float new_pos_x = pos_x_ + speed_ * dt * velocity_x_;

  if ((new_pos_x - radius_ < 0)) {
    velocity_x_ = -velocity_x_;
    pos_x_ = radius_;
  } else if (new_pos_x + radius_ > screenWidth) {
    velocity_x_ = -velocity_x_;
    pos_x_ = screenWidth - radius_;
  } else {
    pos_x_ = new_pos_x;
  }

  float new_pos_y = pos_y_ + speed_ * dt * velocity_y_;

  if (new_pos_y - radius_ < 0) {
    velocity_y_ = -velocity_y_;
    pos_y_ = radius_;
  }

  // Balle sous la plateforme = GAME OVER
  else if (new_pos_y + radius_ > screenHeight) {
    return true;
  } else {
    pos_y_ = new_pos_y;
  }

  // Rebond bord du bas
  /*if (pos_y_ + radius_ > screenHeight) {
    velocity_y_ = -velocity_y_;
    pos_y_ = screenHeight - radius_;
  }*/

  return false;
}
