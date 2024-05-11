#include "MalusBrick.h"

#include <SDL2/SDL_image.h>

#include <iostream>

// pointeur statique pour la texture
std::shared_ptr<SDL_Texture> MalusBrick::malus_texture_ = nullptr;

MalusBrick::MalusBrick(Game* game, std::shared_ptr<SDL_Renderer>& renderer)
    : SpecialBrick(game, renderer) {
  // Chargez la texture du mur uniquement si elle n'a pas déjà été chargée
  if (!malus_texture_) {
    // Chargez la texture du mur depuis un fichier
    SDL_Surface* surface = IMG_Load("img/goomba.png");

    if (!surface) {
      // Gestion de l'erreur si le chargement de l'image échoue
      std::cerr << "Échec du chargement de la texture du malus : "
                << IMG_GetError() << std::endl;
      exit(1);
    }
    malus_texture_ = std::shared_ptr<SDL_Texture>(
        SDL_CreateTextureFromSurface(renderer.get(), surface),
        [](SDL_Texture* texture) { SDL_DestroyTexture(texture); });
    SDL_FreeSurface(surface);
    if (!malus_texture_) {
      // Gestion de l'erreur si la création de la texture échoue
      std::cerr << "Échec de la création de la texture du malus : "
                << SDL_GetError() << std::endl;
      exit(1);
    }
  }
}