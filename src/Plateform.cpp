#include "Plateform.h"

// Constructeur par défaut
Plateform::Plateform()
    : height(20), width(100), pos_x(25), pos_y(25), speed(10) {}

Plateform::Plateform(float window_width, float window_height)
    : height(20), width(100), speed(10) {
  pos_x = (window_width - width) / 2;
  pos_y = window_height * (7.0 / 8.0) - height / 2;
}

// Fonction d'affichage
void Plateform::render(SDL_Renderer* renderer) {
  SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
  plateformRect = {pos_x, pos_y, width, height};

  SDL_RenderFillRect(renderer, &plateformRect);
}

// Fonction déplacement clavier
void Plateform::move_keyboard(SDL_Keycode keyCode, int screenWidth) {
  switch (keyCode) {
    case SDLK_LEFT:
      if (pos_x - speed >= 0) {
        pos_x -= speed;
      }
      break;
    case SDLK_RIGHT:
      if (pos_x + width + speed <= screenWidth) {
        pos_x += speed;
      }
      break;
    default:
      break;
  }
}

// Fonction déplacement souris
void Plateform::move_mouse(int mouseX, int mouseY, int screenWidth) {
  if (mouseX - width / 2 >= 0) {
    if (mouseX + width / 2 <= screenWidth) {
      pos_x = mouseX - width / 2;
    } else {
      pos_x = screenWidth - width;
    }
  } else {
    pos_x = 0;
  }
}