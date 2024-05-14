#ifndef PLATEFORM_H
#define PLATEFORM_H

#include <SDL2/SDL.h>

#include <memory>

/**
 * @brief Classe représentant une plateforme dans le jeu.
 *
 * Une plateforme est utilisée pour faire rebondir les balles,
 * capturer des bonus et malus tombant. Elle est controlable à la souris et au
 * clavier.
 */
class Plateform {
 private:
  int height_;            /**< Hauteur de la plateforme. */
  int width_;             /**< Largeur de la plateforme. */
  int pos_x_;             /**< Position horizontale de la plateforme. */
  int pos_y_;             /**< Position verticale de la plateforme. */
  int speed_;             /**< Vitesse de déplacement de la plateforme. */
  SDL_Rect plateformRect; /**< Rectangle SDL représentant la plateforme. */

 public:
  /**
   * @brief Constructeur par défaut de la classe Plateform.
   */
  Plateform();
  /**
   * @brief Constructeur de la classe Plateform avec prise en compte de la
   * ltaille de la fenetre.
   * @param width_window La largeur de la fenêtre du jeu.
   * @param height_window La hauteur de la fenêtre du jeu.
   */
  Plateform(const float width_window, const float height_window);

  // Get
  /**
   * @brief Récupère la hauteur de la plateforme.
   * @return La hauteur de la plateforme.
   */
  inline int getHeight() const { return height_; }
  /**
   * @brief Récupère la largeur de la plateforme.
   * @return La largeur de la plateforme.
   */
  inline int getWidth() const { return width_; }
  /**
   * @brief Récupère la position horizontale de la plateforme.
   * @return La position horizontale de la plateforme.
   */
  inline int getPosX() const { return pos_x_; }
  /**
   * @brief Récupère la position verticale de la plateforme.
   * @return La position verticale de la plateforme.
   */
  inline int getPosY() const { return pos_y_; }
  /**
   * @brief Récupère la vitesse de déplacement de la plateforme.
   * @return La vitesse de déplacement de la plateforme.
   */
  inline float getSpeed() const { return speed_; }

  /**
   * @brief Définit la largeur de la plateforme.
   * @param width La nouvelle largeur de la plateforme.
   */
  inline void setWidth(const int width) { width_ = width; }

 private:
  // Set
  /**
   * @brief Définit la hauteur de la plateforme.
   * @param height La nouvelle hauteur de la plateforme.
   */
  inline void setHeight(const int height) { height_ = height; }
  /**
   * @brief Définit la position horizontale de la plateforme.
   * @param pos_x La nouvelle position horizontale de la plateforme.
   */
  inline void setPosX(const int pos_x) { pos_x_ = pos_x; }
  /**
   * @brief Définit la position verticale de la plateforme.
   * @param pos_y La nouvelle position verticale de la plateforme.
   */
  inline void setPosY(const int pos_y) { pos_y_ = pos_y; }
  /**
   * @brief Définit la vitesse de déplacement de la plateforme.
   * @param speed La nouvelle vitesse de déplacement de la plateforme.
   */
  inline void setSpeed(const float speed) { speed_ = speed; }

 public:
  /**
   * @brief Affiche la plateforme sur le rendu SDL.
   * @param renderer Le rendu SDL sur lequel afficher la plateforme.
   */
  void render(const std::shared_ptr<SDL_Renderer>& renderer);
  /**
   * @brief Déplace la plateforme en fonction des touches du clavier.
   * @param keyCode Le code de la touche du clavier.
   * @param screenWidth La largeur de l'écran.
   * @param dt Le temps écoulé depuis la dernière mise à jour.
   */
  void move_keyboard(const SDL_Keycode keyCode, const int screenWidth,
                     const float dt);
  /**
   * @brief Déplace la plateforme en fonction de la position de la souris.
   * @param mouseX La position horizontale de la souris.
   * @param mouseY La position verticale de la souris.
   * @param screenWidth La largeur de l'écran.
   */
  void move_mouse(const int mouseX, const int mouseY, const int screenWidth);
};

#endif  // PLATEFORM_H