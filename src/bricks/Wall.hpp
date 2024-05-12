#include <SDL2/SDL_image.h>

#include <iostream>

#include "Wall.h"

// pointeur statique pour la texture
template <typename Shape>
std::shared_ptr<SDL_Texture> Wall<Shape>::wall_texture_ = nullptr;

template <typename Shape>
Wall<Shape>::Wall(std::shared_ptr<SDL_Renderer>& renderer)
    : Cell<Shape>(Color::Cyan) {
  // Chargez la texture du mur uniquement si elle n'a pas déjà été chargée
  if (!wall_texture_) {
    // Chargez la texture du mur depuis un fichier
    SDL_Surface* surface = IMG_Load("img/wall.png");

    if (!surface) {
      // Gestion de l'erreur si le chargement de l'image échoue
      std::cerr << "Échec du chargement de la texture du mur : " << std::endl;
      exit(1);
    }
    wall_texture_ = std::shared_ptr<SDL_Texture>(
        SDL_CreateTextureFromSurface(renderer.get(), surface),
        [](SDL_Texture* texture) { SDL_DestroyTexture(texture); });
    SDL_FreeSurface(surface);
    if (!wall_texture_) {
      // Gestion de l'erreur si la création de la texture échoue
      std::cerr << "Échec de la création de la texture du mur : "
                << SDL_GetError() << std::endl;
      exit(1);
    }
  }
}

template <typename Shape>
Wall<Shape>::Wall(std::shared_ptr<SDL_Renderer>& renderer,
                  TriangleCell::Orientation orientation)
    : Cell<Shape>(Color::Cyan, orientation) {
  // Chargez la texture du mur uniquement si elle n'a pas déjà été chargée
  if (!wall_texture_) {
    // Chargez la texture du mur depuis un fichier
    SDL_Surface* surface = IMG_Load("img/wall.png");

    if (!surface) {
      // Gestion de l'erreur si le chargement de l'image échoue
      std::cerr << "Échec du chargement de la texture du mur : " << std::endl;
      exit(1);
    }
    wall_texture_ = std::shared_ptr<SDL_Texture>(
        SDL_CreateTextureFromSurface(renderer.get(), surface),
        [](SDL_Texture* texture) { SDL_DestroyTexture(texture); });
    SDL_FreeSurface(surface);
    if (!wall_texture_) {
      // Gestion de l'erreur si la création de la texture échoue
      std::cerr << "Échec de la création de la texture du mur : "
                << SDL_GetError() << std::endl;
      exit(1);
    }
  }
}

template <typename Shape>
void Wall<Shape>::renderCell(std::shared_ptr<SDL_Renderer>& renderer, int x,
                             int y, int cellWidth, int cellHeight) {
  this->shape_.draw(renderer, x, y, cellWidth, cellHeight,
                    ColorUtils::convertColor(getColor()));
}