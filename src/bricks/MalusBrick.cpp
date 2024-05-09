#include "MalusBrick.h"

#include <SDL2/SDL_image.h>

// pointeur statique pour la texture
SDL_Texture* MalusBrick::malus_texture_ = nullptr;

MalusBrick::MalusBrick(Game* game, std::shared_ptr<SDL_Renderer>& renderer)
    : MalusBonusBrick(game, renderer) {
  // Chargez la texture du mur uniquement si elle n'a pas déjà été chargée
  if (!malus_texture_) {
    // Chargez la texture du mur depuis un fichier
    SDL_Surface* surface = IMG_Load("img/malus.jpg");

    if (!surface) {
      // Gestion de l'erreur si le chargement de l'image échoue
      std::cerr << "Failed to load wall texture: " << IMG_GetError()
                << std::endl;
      return;
    }
    malus_texture_ = SDL_CreateTextureFromSurface(renderer.get(), surface);
    SDL_FreeSurface(surface);
    if (!malus_texture_) {
      // Gestion de l'erreur si la création de la texture échoue
      std::cerr << "Failed to create wall texture: " << SDL_GetError()
                << std::endl;
      return;
    }
  }
}