#include "Wall.h"

#include <SDL2/SDL_image.h>

#include <iostream>

// pointeur statique pour la texture
std::shared_ptr<SDL_Texture> Wall::wall_texture_ = nullptr;

Wall::Wall(std::shared_ptr<SDL_Renderer>& renderer) : Cell(Color::Cyan) {
  // Chargez la texture du mur uniquement si elle n'a pas déjà été chargée
  if (!wall_texture_) {
    // Chargez la texture du mur depuis un fichier
    SDL_Surface* surface = IMG_Load("img/wall.png");

    if (!surface) {
      // Gestion de l'erreur si le chargement de l'image échoue
      std::cerr << "Failed to load wall texture: " << IMG_GetError()
                << std::endl;
      return;
    }
    wall_texture_ = std::shared_ptr<SDL_Texture>(
        SDL_CreateTextureFromSurface(renderer.get(), surface),
        [](SDL_Texture* texture) { SDL_DestroyTexture(texture); });
    SDL_FreeSurface(surface);
    if (!wall_texture_) {
      // Gestion de l'erreur si la création de la texture échoue
      std::cerr << "Failed to create wall texture: " << SDL_GetError()
                << std::endl;
      return;
    }
  }
}

void Wall::renderCell(std::shared_ptr<SDL_Renderer>& renderer, int x, int y,
                      int cellWidth, int cellHeight) {
  int padding = 1;  // Espace entre chaque case
  int size = cellWidth - 2 * padding;

  // Utilisez la texture du mur pour afficher le mur
  SDL_Rect rect = {x + padding, y + padding, size, size};
  SDL_RenderCopy(renderer.get(), wall_texture_.get(), NULL, &rect);
}