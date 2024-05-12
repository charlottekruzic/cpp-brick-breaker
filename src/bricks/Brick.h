#ifndef BRICK_H
#define BRICK_H

#include <map>
#include <string>

#include "../Cell.h"
#include "../Colors.h"
// #include "Game.h"

class Game;

// Classe représentant une brique
template <typename Shape>
class Brick : public Cell<Shape> {
 public:
  bool rebondir() const override {
    return (hitsLeft_ > 0);  // Les objets rebondissent sur une brique
  }
  // retourne vrai si détruit
  bool hit() {
    if (hitsLeft_ > 0) {
      hitsLeft_--;
    }
    if (hitsLeft_ == 0) {
      return true;
    }
    return false;
  }
  // idem à Cell
  void renderCell(std::shared_ptr<SDL_Renderer>& renderer, int x, int y,
                  int cellWidth, int cellHeight) {
    /*int padding = 1;  // Espace entre chaque case
    int size = cellWidth - 2 * padding;
    // Taille effective de la case avec l'espace
    SDL_Rect rect = {x + padding, y + padding, size, size};
    // Utilise les coordonnées et la taille du carré avec l'espace
    SDL_Color color = ColorUtils::convertColor(getColor());
    SDL_SetRenderDrawColor(renderer.get(), color.r, color.g, color.b, color.a);
    SDL_RenderFillRect(renderer.get(), &rect);*/
    // Appel SquareCell pour dessiner le carré
    this->shape_.draw(renderer, x, y, cellWidth, cellHeight,
                      ColorUtils::convertColor(getColor()));
  }

  int getStrength() const {
    return strength_;  // Renvoie la force de la brique
  }  // Méthode pour obtenir la force de la brique
  int getHitsLeft() const {
    return hitsLeft_;  // Renvoie le nombre de coups restants
  }
  // Méthode pour obtenir le nombre de coups restants
  Color getColor() const override {
    auto it = strengthColorMap_.find(hitsLeft_);
    if (it != strengthColorMap_.end()) {
      return it
          ->second;  // Retourne la couleur associée à la force de la brique
    } else {
      // Gérer le cas où la force n'est pas trouvée dans le dictionnaire
      return Color::DEFAULT_COLOR;
    }
  }

  // protected:
  Brick(int strength, Game* game)
      : strength_(strength), hitsLeft_(strength), game_(game) {}

  Brick(int strength, Game* game, TriangleCell::Orientation orientation)
      : strength_(strength),
        hitsLeft_(strength),
        game_(game),
        Cell<Shape>(orientation) {}

 protected:
  Game* game_;    // Attribut pour stocker un pointeur vers l'objet Game
  int hitsLeft_;  // Nombre de coups restants

 private:
  int strength_;  // Force de la brique
  Color color_;   // protected .
  std::map<int, Color> strengthColorMap_ = {
      {1, Color::Green},
      {2, Color::Yellow},
      {3, Color::Orange},
      {4, Color::Red},
      {5, Color::Purple}};  // Dictionnaire associant une force à une couleur
};

#endif  // BRICK_H
