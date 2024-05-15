#include <SDL2/SDL_image.h>

#include <iostream>
#include <memory>

#include "BonusBrick.h"

// Initialisation du pointeur statique de la texture du bonus
template <typename Shape>
std::shared_ptr<SDL_Texture> BonusBrick<Shape>::bonus_texture_ = nullptr;

// Constructeur de la classe BonusBrick
template <typename Shape>
BonusBrick<Shape>::BonusBrick(Game<Shape>* game,
                              std::shared_ptr<SDL_Renderer>& renderer)
    : SpecialBrick<BonusBrick, Shape>(game, renderer) {
  // Chargez la texture du mur uniquement si elle n'a pas déjà été chargée
  if (!bonus_texture_) {
    // Chargez la texture du mur depuis un fichier
    std::unique_ptr<SDL_Surface, void (*)(SDL_Surface*)> surface(
        IMG_Load("../img/etoile.png"), SDL_FreeSurface);

    if (!surface) {
      // Gestion de l'erreur si le chargement de l'image échoue
      std::cerr << "Échec du chargement de la texture du bonus : "
                << IMG_GetError() << std::endl;
      exit(1);
    }
    bonus_texture_ = std::shared_ptr<SDL_Texture>(
        SDL_CreateTextureFromSurface(renderer.get(), surface.get()),
        [](SDL_Texture* texture) { SDL_DestroyTexture(texture); });

    if (!bonus_texture_) {
      // Gestion de l'erreur si la création de la texture échoue
      std::cerr << "Échec de la création de la texture du bonus : "
                << SDL_GetError() << std::endl;
      exit(1);
    }
  }
}

// Constructeur de la classe BonusBrick avec orientation pour les briques
// triangulaires
template <typename Shape>
BonusBrick<Shape>::BonusBrick(Game<Shape>* game,
                              std::shared_ptr<SDL_Renderer>& renderer,
                              const TriangleCell::Orientation orientation)
    : SpecialBrick<BonusBrick, Shape>(game, renderer, orientation) {
  // Chargez la texture du mur uniquement si elle n'a pas déjà été chargée
  if (!bonus_texture_) {
    // Chargez la texture du mur depuis un fichier
    std::unique_ptr<SDL_Surface, void (*)(SDL_Surface*)> surface(
        IMG_Load("../img/etoile.png"), SDL_FreeSurface);
    if (!surface) {
      // Gestion de l'erreur si le chargement de l'image échoue
      std::cerr << "Échec du chargement de la texture du bonus : "
                << IMG_GetError() << std::endl;
      exit(1);
    }
    bonus_texture_ = std::shared_ptr<SDL_Texture>(
        SDL_CreateTextureFromSurface(renderer.get(), surface.get()),
        [](SDL_Texture* texture) { SDL_DestroyTexture(texture); });
    if (!bonus_texture_) {
      // Gestion de l'erreur si la création de la texture échoue
      std::cerr << "Échec de la création de la texture du bonus : "
                << SDL_GetError() << std::endl;
      exit(1);
    }
  }
}

/**
 * @brief Afficher la brique carrée
 * @param renderer Renderer SDL
 * @param x Position x de la brique
 * @param y Position y de la brique
 * @param cellWidth Largeur d'une cellule
 * @param cellHeight Hauteur d'une cellule
 */
template <>
void BonusBrick<SquareCell>::renderCell(
    const std::shared_ptr<SDL_Renderer>& renderer, const int x, const int y,
    const float cellWidth, const float cellHeight) {
  int padding = 1;  // Espace entre chaque case
  int size = cellWidth - 2 * padding;

  // Utilisez la texture du mur pour afficher le mur
  SDL_Rect rect = {x + padding, y + padding, size, size};
  SDL_RenderCopy(renderer.get(), getTexture().get(), NULL, &rect);
}

/**
 * @brief Afficher la brique triangulaire
 * @param renderer Renderer SDL
 * @param x Position x de la brique
 * @param y Position y de la brique
 * @param cellWidth Largeur d'une cellule
 * @param cellHeight Hauteur d'une cellule
 */
template <>
void BonusBrick<TriangleCell>::renderCell(
    const std::shared_ptr<SDL_Renderer>& renderer, const int x, const int y,
    const float cellWidth, const float cellHeight) {
  this->shape_.draw(renderer, x, y, cellWidth, cellHeight,
                    ColorUtils::convertColor(getColor()));
}

/**
 * @brief Afficher la brique hexagonale
 * @param renderer Renderer SDL
 * @param x Position x de la brique
 * @param y Position y de la brique
 * @param cellWidth Largeur d'une cellule
 * @param cellHeight Hauteur d'une cellule
 */
template <>
void BonusBrick<HexagonCell>::renderCell(
    const std::shared_ptr<SDL_Renderer>& renderer, const int x, const int y,
    const float cellWidth, const float cellHeight) {
  this->shape_.draw(renderer, x, y, cellWidth, cellHeight,
                    ColorUtils::convertColor(getColor()));
}