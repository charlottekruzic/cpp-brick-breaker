#ifndef PLATEFORM_H
#define PLATEFORM_H

#include <SDL2/SDL.h>

class Plateform {
 private:
  int height;
  int width;
  int pos_x;
  int pos_y;

  int speed;

  SDL_Rect plateformRect;

 public:
  Plateform();
  Plateform(float width_window, float height_window);

  void render(SDL_Renderer* renderer);
  void move_keyboard(SDL_Keycode keyCode, int screenWidth);
  void move_mouse(int mouseX, int mouseY, int screenWidth);
};

#endif  // PLATEFORM_H