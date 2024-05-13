#ifndef MALUS_BONUS_H
#define MALUS_BONUS_H

#include "Brick.h"

/**
 * @brief Classe représentant une brique spéciale
 * @tparam Derived Classe dérivée de SpecialBrick
 * @tparam Shape Type de cellule de la grille
 */
template <class Derived, typename Shape>
class SpecialBrick : public Brick<Shape> {
 public:
  /**
   * @brief Constructeur de la classe SpecialBrick
   * @param game Game auquel appartient la brique
   * @param renderer Renderer utilisé pour afficher la brique
   */
  SpecialBrick(Game<Shape>* game, std::shared_ptr<SDL_Renderer>& renderer);

  /**
   * @brief Constructeur de la classe SpecialBrick avec orientation pour les
   * cases triangulaires
   * @param game Game auquel appartient la brique
   * @param renderer Renderer utilisé pour afficher la brique
   * @param orientation Orientation de la brique
   */
  SpecialBrick(Game<Shape>* game, std::shared_ptr<SDL_Renderer>& renderer,
               const TriangleCell::Orientation orientation);

  /**
   * @brief Afficher la brique
   * @param renderer Renderer utilisé pour afficher la brique
   * @param x Position en x de la brique
   * @param y Position en y de la brique
   * @param cellWidth Largeur de la brique
   * @param cellHeight Hauteur de la brique
   */
  void renderCell(std::shared_ptr<SDL_Renderer>& renderer, const int x,
                  const int y, const float cellWidth,
                  const float cellHeight) override;

  /**
   * @brief Appliquer l'effet de la brique
   * @note Méthode virtuelle pure
   */
  virtual void performAction() = 0;

  /**
   * @brief Action quand la brique est touchée
   * @return bool Vrai si la brique est cassée, faux sinon
   * @note Diminue le nombre de coups restants si la brique n'est pas cassée
   * et applique l'effet de la brique si le nombre de coups restants est nul
   */
  bool hit() override;

  /**
   * @brief Obtenir la texture de la brique
   * @return std::shared_ptr<SDL_Texture>& Texture de la brique
   */
  static std::shared_ptr<SDL_Texture>& getTexture() {
    return Derived::getTexture();
  }
};

#include "SpecialBrick.hpp"

#endif  // MALUS_BONUS_H