#ifndef BALL_H
#define BALL_H

#include <SDL2/SDL.h>

#include "Grid.h"
#include "Plateform.h"

class Ball {
 private:
  int radius_;
  int speed_;
  float pos_x_;
  float pos_y_;
  float velocity_x_;
  float velocity_y_;
  float prev_pos_x_;
  float prev_pos_y_;

  SDL_Rect plateformRect;

 public:
  Ball();
  Ball(int radius, int speed, float platformPosX, float platformPosY,
       int platformLength, float velocity_x, float velocity_y);

  void render(SDL_Renderer* renderer);
  bool updatePosition(float dt, int screenWidth, int screenHeight);
  // void checkCollide(const Plateform& p, const Grid& grid);

  // Méthodes set et get
  int getSpeed() const { return speed_; }
  float getPosX() const { return pos_x_; }
  float getPosY() const { return pos_y_; }
  float getPrevPosX() const { return prev_pos_x_; }
  float getPrevPosY() const { return prev_pos_y_; }
  int getRadius() const { return radius_; }
  float getVelocityX() const { return velocity_x_; }
  float getVelocityY() const { return velocity_y_; }

  void setPosX(const float pos_x) { pos_x_ = pos_x; }
  void setPosY(const float pos_y) { pos_y_ = pos_y; }
  void setVelocityX(const float velocity_x) { velocity_x_ = velocity_x; }
  void setVelocityY(const float velocity_y) { velocity_y_ = velocity_y; }

  // Méthodes pour inverser les vitesses de la balle
  void reverseVelocityX() { velocity_x_ = -velocity_x_; }
  void reverseVelocityY() { velocity_y_ = -velocity_y_; }
};

#endif  // BALL_H