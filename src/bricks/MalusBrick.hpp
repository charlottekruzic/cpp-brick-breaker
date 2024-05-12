#include <SDL2/SDL_image.h>

#include <iostream>
#include <memory>

#include "MalusBrick.h"

// pointeur statique pour la texture

template <typename Shape>
std::shared_ptr<SDL_Texture> MalusBrick<Shape>::malus_texture_ = nullptr;

template <typename Shape>
MalusBrick<Shape>::MalusBrick(Game<Shape>* game,
                              std::shared_ptr<SDL_Renderer>& renderer)
    : SpecialBrick<MalusBrick, Shape>(game, renderer) {
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

template <typename Shape>
MalusBrick<Shape>::MalusBrick(Game<Shape>* game,
                              std::shared_ptr<SDL_Renderer>& renderer,
                              TriangleCell::Orientation orientation)
    : SpecialBrick<MalusBrick, Shape>(game, renderer, orientation) {
  // Chargez la texture du mur uniquement si elle n'a pas déjà été chargée
  if (!malus_texture_) {
    // Chargez la texture du mur depuis un fichier
    SDL_Surface* surface = IMG_Load("img/etoile.png");

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

template <>
void MalusBrick<SquareCell>::renderCell(std::shared_ptr<SDL_Renderer>& renderer,
                                        int x, int y, int cellWidth,
                                        int cellHeight) {
  int padding = 1;  // Espace entre chaque case
  int size = cellWidth - 2 * padding;

  // Utilisez la texture du mur pour afficher le mur
  SDL_Rect rect = {x + padding, y + padding, size, size};
  SDL_RenderCopy(renderer.get(), getTexture().get(), NULL, &rect);
}

template <>
void MalusBrick<TriangleCell>::renderCell(
    std::shared_ptr<SDL_Renderer>& renderer, int x, int y, int cellWidth,
    int cellHeight) {
  this->shape_.draw(renderer, x, y, cellWidth, cellHeight,
                    ColorUtils::convertColor(getColor()));
}