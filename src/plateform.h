#ifndef PLATEFORM_H
#define PLATEFORM_H

#include <SDL2/SDL.h>

class Plateform {
 private:
  int height;
  int width;
  int pos_x;
  int pos_y;

  SDL_Rect plateformRect;

 public:
  Plateform();
  Plateform(float width_window, float height_window);

  void render(SDL_Renderer* renderer);
  void move_keyboard(SDL_Keycode keyCode);
};

#endif  // PLATEFORM_H