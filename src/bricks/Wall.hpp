#include <SDL2/SDL_image.h>

#include <iostream>

#include "Wall.h"

// Initialisation du pointeur statique sur la texture du mur
template <typename Shape>
std::shared_ptr<SDL_Texture> Wall<Shape>::wall_texture_ = nullptr;

// Constructeurs de la classe Wall
template <typename Shape>
Wall<Shape>::Wall(std::shared_ptr<SDL_Renderer>& renderer)
    : color_(Color::BrickColor) {
  // Chargez la texture du mur uniquement si elle n'a pas déjà été chargée
  if (!wall_texture_) {
    // Chargez la texture du mur depuis un fichier
    SDL_Surface* surface = IMG_Load("../img/wall.png");

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
                  const TriangleCell::Orientation orientation)
    : color_(Color::BrickColor),
      orientation_(orientation),
      shape_(orientation) {
  // Chargez la texture du mur uniquement si elle n'a pas déjà été chargée
  if (!wall_texture_) {
    // Chargez la texture du mur depuis un fichier
    SDL_Surface* surface = IMG_Load("../img/wall.png");

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

// Afficher le mur
template <typename Shape>
void Wall<Shape>::renderCell(std::shared_ptr<SDL_Renderer>& renderer,
                             const int x, const int y, const float cellWidth,
                             const float cellHeight) {
  this->shape_.draw(renderer, x, y, cellWidth, cellHeight,
                    ColorUtils::convertColor(getColor()));
}

// Spécialisation de la méthode renderCell pour les cases carrées
template <>
inline void Wall<SquareCell>::renderCell(
    std::shared_ptr<SDL_Renderer>& renderer, int x, int y, float cellWidth,
    float cellHeight) {
  int padding = 1;  // Espace entre chaque case
  int size = cellWidth - 2 * padding;

  // Utilisez la texture du mur pour afficher le mur
  SDL_Rect rect = {x + padding, y + padding, size, size};
  SDL_RenderCopy(renderer.get(), wall_texture_.get(), NULL, &rect);
}