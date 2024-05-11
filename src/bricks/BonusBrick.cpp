#include "BonusBrick.h"

#include <SDL2/SDL_image.h>

#include <iostream>
#include <memory>

// pointeur statique pour la texture
std::shared_ptr<SDL_Texture> BonusBrick::bonus_texture_ = nullptr;

BonusBrick::BonusBrick(Game* game, std::shared_ptr<SDL_Renderer>& renderer)
    : MalusBonusBrick(game, renderer) {
  // Chargez la texture du mur uniquement si elle n'a pas déjà été chargée
  if (!bonus_texture_) {
    // Chargez la texture du mur depuis un fichier
    SDL_Surface* surface = IMG_Load("img/etoile.jpg");

    if (!surface) {
      // Gestion de l'erreur si le chargement de l'image échoue
      std::cerr << "Failed to load wall texture: " << IMG_GetError()
                << std::endl;
      return;
    }
    bonus_texture_ = std::shared_ptr<SDL_Texture>(
        SDL_CreateTextureFromSurface(renderer.get(), surface),
        [](SDL_Texture* texture) { SDL_DestroyTexture(texture); });
    SDL_FreeSurface(surface);
    if (!bonus_texture_) {
      // Gestion de l'erreur si la création de la texture échoue
      std::cerr << "Failed to create wall texture: " << SDL_GetError()
                << std::endl;
      return;
    }
  }
}