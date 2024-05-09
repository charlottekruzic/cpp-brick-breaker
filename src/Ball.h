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
  inline int getSpeed() const { return speed_; }
  inline void setSpeed(int speed) { speed_ = speed; }
  inline float getPosX() const { return pos_x_; }
  inline float getPosY() const { return pos_y_; }
  inline float getPrevPosX() const { return prev_pos_x_; }
  inline float getPrevPosY() const { return prev_pos_y_; }
  inline int getRadius() const { return radius_; }
  inline float getVelocityX() const { return velocity_x_; }
  inline float getVelocityY() const { return velocity_y_; }

  inline void setPosX(const float pos_x) { pos_x_ = pos_x; }
  inline void setPosY(const float pos_y) { pos_y_ = pos_y; }
  inline void setVelocityX(const float velocity_x) { velocity_x_ = velocity_x; }
  inline void setVelocityY(const float velocity_y) { velocity_y_ = velocity_y; }

  // Méthodes pour inverser les vitesses de la balle
  inline void reverseVelocityX() { velocity_x_ = -velocity_x_; }
  inline void reverseVelocityY() { velocity_y_ = -velocity_y_; }
};

#endif  // BALL_H