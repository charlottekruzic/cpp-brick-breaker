#ifndef BALL_H
#define BALL_H

#include <SDL2/SDL.h>

#include "Grid.h"
#include "Plateform.h"

/**
 * @brief Classe représentant une balle dans le jeu.
 */
class Ball {
 private:
  int radius_;       /**< Rayon de la balle. */
  int speed_;        /**< Vitesse de la balle. */
  float pos_x_;      /**< Position horizontale de la balle. */
  float pos_y_;      /**< Position verticale de la balle. */
  float velocity_x_; /**< Vitesse horizontale de la balle. */
  float velocity_y_; /**< Vitesse verticale de la balle. */
  float prev_pos_x_; /**< Position horizontale précédente de la balle. */
  float prev_pos_y_; /**< Position verticale précédente de la balle. */

 public:
  /**
   * @brief Constructeur par défaut de la classe Ball.
   */
  Ball();

  /**
   * @brief Constructeur de la classe Ball avec initialisation des paramètres.
   * @param radius Le rayon de la balle.
   * @param speed La vitesse de la balle.
   * @param platformPosX La position horizontale de la plateforme.
   * @param platformPosY La position verticale de la plateforme.
   * @param platformLength La longueur de la plateforme.
   * @param velocity_x La vitesse horizontale initiale de la balle.
   * @param velocity_y La vitesse verticale initiale de la balle.
   */
  Ball(int radius, int speed, float platformPosX, float platformPosY,
       int platformLength, float velocity_x, float velocity_y);

  /**
   * @brief Affiche la balle sur le rendu SDL.
   * @param renderer Le rendu SDL sur lequel afficher la balle.
   */
  void render(std::shared_ptr<SDL_Renderer>& renderer);

  /**
   * @brief Met à jour la position de la balle en fonction du temps écoulé et de
   * la taille de l'écran.
   * @param dt Le temps écoulé depuis la dernière mise à jour.
   * @param screenWidth La largeur de l'écran.
   * @param screenHeight La hauteur de l'écran.
   * @return True si la balle est encore dans les limites de l'écran, sinon
   * false.
   */
  bool updatePosition(float dt, int screenWidth, int screenHeight);
  // void checkCollide(const Plateform& p, const Grid& grid);

  // Méthodes set et get
  /**
   * @brief Récupère la vitesse de la balle.
   * @return La vitesse de la balle.
   */
  inline int getSpeed() const { return speed_; }
  /**
   * @brief Récupère la position horizontale de la balle.
   * @return La position horizontale de la balle.
   */
  inline float getPosX() const { return pos_x_; }
  /**
   * @brief Récupère la position verticale de la balle.
   * @return La position verticale de la balle.
   */
  inline float getPosY() const { return pos_y_; }
  /**
   * @brief Récupère la position horizontale précédente de la balle.
   * @return La position horizontale précédente de la balle.
   */
  inline float getPrevPosX() const { return prev_pos_x_; }
  /**
   * @brief Récupère la position verticale précédente de la balle.
   * @return La position verticale précédente de la balle.
   */
  inline float getPrevPosY() const { return prev_pos_y_; }
  /**
   * @brief Récupère le rayon de la balle.
   * @return Le rayon de la balle.
   */
  inline int getRadius() const { return radius_; }
  /**
   * @brief Récupère la vitesse horizontale de la balle.
   * @return La vitesse horizontale de la balle.
   */
  inline float getVelocityX() const { return velocity_x_; }
  /**
   * @brief Récupère la vitesse verticale de la balle.
   * @return La vitesse verticale de la balle.
   */
  inline float getVelocityY() const { return velocity_y_; }

  /**
   * @brief Définit la vitesse de la balle.
   * @param speed La nouvelle vitesse de la balle.
   */
  inline void setSpeed(int speed) { speed_ = speed; }
  /**
   * @brief Définit la position horizontale de la balle.
   * @param pos_x La nouvelle position horizontale de la balle.
   */
  inline void setPosX(const float pos_x) { pos_x_ = pos_x; }
  /**
   * @brief Définit la position verticale de la balle.
   * @param pos_y La nouvelle position verticale de la balle.
   */
  inline void setPosY(const float pos_y) { pos_y_ = pos_y; }
  /**
   * @brief Définit la vitesse horizontale de la balle.
   * @param velocity_x La nouvelle vitesse horizontale de la balle.
   */
  inline void setVelocityX(const float velocity_x) { velocity_x_ = velocity_x; }
  /**
   * @brief Définit la vitesse verticale de la balle.
   * @param velocity_y La nouvelle vitesse verticale de la balle.
   */
  inline void setVelocityY(const float velocity_y) { velocity_y_ = velocity_y; }

  // méthodes pour inverser les directions de la balle
  /**
   * @brief Inverse la direction horizontale de la balle.
   */
  inline void reverseVelocityX() { velocity_x_ = -velocity_x_; }
  /**
   * @brief Inverse la direction verticale de la balle.
   */
  inline void reverseVelocityY() { velocity_y_ = -velocity_y_; }
};

#endif  // BALL_H