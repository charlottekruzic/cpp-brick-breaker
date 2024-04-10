#ifndef PLATEFORM_H
#define PLATEFORM_H

#include <SDL2/SDL.h>

class Plateform {
 private:
  int height_;
  int width_;
  int pos_x_;
  int pos_y_;

  int speed_;

  SDL_Rect plateformRect;

  // Set
  void setHeight(int height);
  void setWidth(int width);
  void setPosX(int pos_x);
  void setPosY(int pos_y);
  void setSpeed(float speed);

 public:
  // Constructeurs
  Plateform();
  Plateform(float width_window, float height_window);

  // Get
  int getHeight() const;
  int getWidth() const;
  int getPosX() const;
  int getPosY() const;
  float getSpeed() const;

  // Fonctions
  void render(SDL_Renderer* renderer);
  void move_keyboard(SDL_Keycode keyCode, int screenWidth);
  void move_mouse(int mouseX, int mouseY, int screenWidth);
};

#endif  // PLATEFORM_H