#ifndef BONUS_MALUS_H
#define BONUS_MALUS_H

#include <SDL2/SDL.h>

#include <memory>

#include "../Colors.h"

template <typename Shape>
class Game;

/**
 * @brief Classe représentant un bonus ou un malus
 * @tparam Shape Type de cellule de la grille
 */
template <typename Shape>
class BonusMalus {
 public:
  /**
   * @brief Constructeur de la classe BonusMalus
   * @param game Game auquel appartient le bonus/malus
   * @param color Couleur du bonus/malus
   * @param x Position x du bonus/malus
   * @param y Position y du bonus/malus
   */
  BonusMalus(Game<Shape>* game, const Color color, const int x, const int y);

  /**
   * @brief Récupérer la position x du bonus/malus
   * @return Position x du bonus/malus
   */
  int getX() const { return x_; }

  /**
   * @brief Récupérer la position y du bonus/malus
   * @return Position y du bonus/malus
   */
  int getY() const { return y_; }

  /**
   * @brief Récupérer la largeur du bonus/malus
   * @return Largeur du bonus/malus
   */
  int getWidth() const { return width_; }

  /**
   * @brief Récupérer la hauteur du bonus/malus
   * @return Hauteur du bonus/malus
   */
  int getHeight() const { return height_; }

  /**
   * @brief Mettre à jour la position du bonus/malus
   * @details Déplacer le bonus/malus vers le bas pour simuler la chute
   * @return void
   */
  void update() { y_ += fall_speed_; }

  /**
   * @brief Récupérer la couleur du bonus/malus
   * @return Couleur du bonus/malus
   */
  Color getColor() const { return color_; }

  /**
   * @brief Appliquer l'effet du bonus/malus
   * @return void
   * @details Méthode virtuelle pure à implémenter dans les classes filles
   */
  virtual void applyEffect() = 0;

  /**
   * @brief Afiicher le bonus/malus
   * @param renderer Renderer sur lequel dessiner le bonus/malus
   * @return void
   */
  void render(const std::shared_ptr<SDL_Renderer>& renderer);

 protected:
  Color color_{Color::DEFAULT_COLOR}; /**< Couleur du bonus/malus */
  Game<Shape>* game_; /**< Game auquel appartient le bonus/malus */

 private:
  int x_;                               /**< Position x du bonus/malus */
  int y_;                               /**< Position y du bonus/malus */
  int width_{10};                       /**< Largeur du bonus/malus */
  int height_{10};                      /**< Hauteur du bonus/malus */
  static constexpr int fall_speed_ = 2; /**< Vitesse de chute du bonus/malus */
};

#include "BonusMalus.hpp"
#endif  // BONUS_MALUS_H