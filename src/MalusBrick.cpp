#include "MalusBrick.h"

#include <SDL2/SDL_image.h>

// pointeur statique pour la texture
SDL_Texture* MalusBrick::malus_texture_ = nullptr;

MalusBrick::MalusBrick(int strength, SDL_Renderer* renderer) : Brick(strength) {
  // Chargez la texture du mur uniquement si elle n'a pas déjà été chargée
  if (!malus_texture_) {
    // Chargez la texture du mur depuis un fichier
    SDL_Surface* wallSurface = IMG_Load("img/malus.jpg");

    if (!wallSurface) {
      // Gestion de l'erreur si le chargement de l'image échoue
      std::cerr << "Failed to load wall texture: " << IMG_GetError()
                << std::endl;
      return;
    }
    malus_texture_ = SDL_CreateTextureFromSurface(renderer, wallSurface);
    SDL_FreeSurface(wallSurface);
    if (!malus_texture_) {
      // Gestion de l'erreur si la création de la texture échoue
      std::cerr << "Failed to create wall texture: " << SDL_GetError()
                << std::endl;
      return;
    }
  }
}

void MalusBrick::renderCell(SDL_Renderer* renderer, int x, int y,
                            int cellSize) {
  int padding = 1;  // Espace entre chaque case
  int size = cellSize - 2 * padding;

  // Utilisez la texture du mur pour afficher le mur
  SDL_Rect rect = {x + padding, y + padding, size, size};
  SDL_RenderCopy(renderer, malus_texture_, NULL, &rect);
}
