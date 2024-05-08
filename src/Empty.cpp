#include "Empty.h"

// pointeur statique pour la texture
// SDL_Texture* Empty::empty_texture_ = nullptr;

Empty::Empty() : Cell(Color::Black) {
  /*
  // Chargez la texture uniquement si elle n'a pas déjà été chargée
  if (!empty_texture_) {
    // Chargez la texture depuis un fichier
    SDL_Surface* emptySurface = IMG_Load("img/test.jpg");

    if (!emptySurface) {
      // Gestion de l'erreur si le chargement de l'image échoue
      std::cerr << "Failed to load empty texture: " << IMG_GetError()
                << std::endl;
      return;
    }
    empty_texture_ = SDL_CreateTextureFromSurface(renderer, emptySurface);
    SDL_FreeSurface(emptySurface);
    if (!empty_texture_) {
      // Gestion de l'erreur si la création de la texture échoue
      std::cerr << "Failed to create empty texture: " << SDL_GetError()
                << std::endl;
      return;
    }
  }
  */
}

bool Empty::rebondir() const {
  return false;  // Les objets ne rebondissent pas sur une case vide
}

bool Empty::hit() { return true; }

/*
void Empty::renderCell(SDL_Renderer* renderer, int x, int y, int cellSize) {
  int padding = 1;  // Espace entre chaque case
  int size = cellSize - 2 * padding;

  // Utilisez la texture du mur pour afficher le mur
  SDL_Rect rect = {x + padding, y + padding, size, size};
  SDL_RenderCopy(renderer, empty_texture_, NULL, &rect);
}
*/
