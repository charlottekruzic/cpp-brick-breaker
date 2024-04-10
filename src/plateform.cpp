#include "plateform.h"

// Constructeur par défaut
Plateform::Plateform() : height(20), width(100), pos_x(25), pos_y(25) {}

Plateform::Plateform(float window_width, float window_height)
    : height(20), width(100) {
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
void Plateform::move_keyboard(SDL_Keycode keyCode) {
  // TODO : Ajout vérification de non sortie de l'écran
  switch (keyCode) {
    case SDLK_LEFT:
      pos_x -= 10;
      break;
    case SDLK_RIGHT:
      pos_x += 10;
      break;
    default:
      break;
  }
}