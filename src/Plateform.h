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
  Plateform(float width_window, float height_window);

  // Get
  /**
   * @brief Récupère la hauteur de la plateforme.
   * @return La hauteur de la plateforme.
   */
  int getHeight() const;
  /**
   * @brief Récupère la largeur de la plateforme.
   * @return La largeur de la plateforme.
   */
  int getWidth() const;
  /**
   * @brief Récupère la position horizontale de la plateforme.
   * @return La position horizontale de la plateforme.
   */
  int getPosX() const;
  /**
   * @brief Récupère la position verticale de la plateforme.
   * @return La position verticale de la plateforme.
   */
  int getPosY() const;
  /**
   * @brief Récupère la vitesse de déplacement de la plateforme.
   * @return La vitesse de déplacement de la plateforme.
   */
  float getSpeed() const;

  /**
   * @brief Définit la largeur de la plateforme.
   * @param width La nouvelle largeur de la plateforme.
   */
  void setWidth(int width);

 private:
  // Set
  /**
   * @brief Définit la hauteur de la plateforme.
   * @param height La nouvelle hauteur de la plateforme.
   */
  void setHeight(int height);
  /**
   * @brief Définit la position horizontale de la plateforme.
   * @param pos_x La nouvelle position horizontale de la plateforme.
   */
  void setPosX(int pos_x);
  /**
   * @brief Définit la position verticale de la plateforme.
   * @param pos_y La nouvelle position verticale de la plateforme.
   */
  void setPosY(int pos_y);
  /**
   * @brief Définit la vitesse de déplacement de la plateforme.
   * @param speed La nouvelle vitesse de déplacement de la plateforme.
   */
  void setSpeed(float speed);

 public:
  /**
   * @brief Affiche la plateforme sur le rendu SDL.
   * @param renderer Le rendu SDL sur lequel afficher la plateforme.
   */
  void render(std::shared_ptr<SDL_Renderer>& renderer);
  /**
   * @brief Déplace la plateforme en fonction des touches du clavier.
   * @param keyCode Le code de la touche du clavier.
   * @param screenWidth La largeur de l'écran.
   * @param dt Le temps écoulé depuis la dernière mise à jour.
   */
  void move_keyboard(SDL_Keycode keyCode, int screenWidth, float dt);
  /**
   * @brief Déplace la plateforme en fonction de la position de la souris.
   * @param mouseX La position horizontale de la souris.
   * @param mouseY La position verticale de la souris.
   * @param screenWidth La largeur de l'écran.
   */
  void move_mouse(int mouseX, int mouseY, int screenWidth);
};

#endif  // PLATEFORM_H