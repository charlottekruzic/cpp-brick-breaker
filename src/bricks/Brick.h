#ifndef BRICK_H
#define BRICK_H

#include <map>
#include <string>

#include "../Cell.h"
#include "../Colors.h"

template <typename Shape>
class Game;

/**
 * @brief Classe représentant une brique
 * @tparam Shape Type de cellule de la grille
 */
template <typename Shape>
class Brick : public Cell<Shape> {
 public:
  /**
   * @brief Constructeur de la classe Brick
   * @param strength Force de la brique
   * @param game Game auquel appartient la brique
   */
  Brick(const int strength, Game<Shape>* game);

  /**
   * @brief Constructeur de la classe Brick avec orientation pour les briques
   * triangulaires
   * @param strength Force de la brique
   * @param game Game auquel appartient la brique
   * @param orientation Orientation de la brique
   */
  Brick(const int strength, Game<Shape>* game,
        const TriangleCell::Orientation orientation);

  /**
   * @brief Savoir si un objet rebondit sur la brique
   * @return bool Vrai si l'objet rebondit, faux sinon
   * @note Les balles rebondissent sur une brique tant qu'elle n'est pas cassée
   */
  bool rebondir() const override;

  /**
   * @brief Action quand la brique est touchée
   * @return bool Vrai si la brique est cassée, faux sinon
   * @note Diminue le nombre de coups restants si la brique n'est pas cassée
   */
  bool hit() override;

  /**
   * @brief Afficher la brique
   * @param renderer Renderer SDL
   * @param x Position x de la brique
   * @param y Position y de la brique
   * @param cellWidth Largeur d'une cellule
   * @param cellHeight Hauteur d'une cellule
   * @return void
   */
  void renderCell(std::shared_ptr<SDL_Renderer>& renderer, const int x,
                  const int y, const float cellWidth, const float cellHeight);
  /**
   * @brief Obtenir la force de la brique
   * @return int Force de la brique
   */
  inline int getStrength() const { return strength_; }

  /**
   * @brief Obtenir le nombre de coups restants
   * @return int Nombre de coups restants
   */
  inline int getHitsLeft() const { return hitsLeft_; }

  /**
   * @brief Obtenir la couleur de la brique
   * @return Color Couleur de la brique
   */
  Color getColor() const override;

  /**
   * @brief Obtenir un point de la forme de la brique
   * @param i Indice du point
   * @return SDL_Point Point de la forme de la brique
   */
  inline SDL_Point getPoint(int i) override { return shape_.getPoint(i); };

 protected:
  Color color_;                           /**< Couleur de la cellule */
  Shape shape_;                           /**< Forme de la cellule */
  TriangleCell::Orientation orientation_; /**< Orientation de la cellule */
  Game<Shape>* game_;                     /**< Pointeur vers le jeu */
  int hitsLeft_;                          /**< Nombre de coups restants */

 private:
  int strength_; /**< Force de la brique */
  std::map<int, Color> strengthColorMap_ = {
      {1, Color::BrickLight},
      {2, Color::BrickLightMedium},
      {3, Color::BrickMedium},
      {4, Color::BrickDarkMedium},
      {5, Color::BrickDark}}; /**< Dictionnaire associant une force à une
                                 couleur */
};

#include "Brick.hpp"

#endif  // BRICK_H
