#ifndef BONUS_MALUS_H
#define BONUS_MALUS_H

#include <SDL2/SDL.h>

#include <memory>

#include "../Colors.h"
// #include "Game.h"

class Game;

class BonusMalus {
 public:
  BonusMalus(Game* game, Color color, int x, int y);

  int getX() const { return x_; }
  int getY() const { return y_; }
  int getWidth() const { return width_; }
  int getHeight() const { return height_; }

  void update() {
    // Déplacer vers le bas pour simuler la chute
    y_ += fall_speed_;
  }
  Color getColor() { return color_; }
  virtual void applyEffect() = 0;
  // void applyEffect();
  void render(std::shared_ptr<SDL_Renderer>& renderer);

 protected:
  Color color_{Color::DEFAULT_COLOR};
  Game* game_;

 private:
  int x_;
  int y_;
  int width_{10};
  int height_{10};
  static constexpr int fall_speed_ = 2;  // Vitesse de chute
};

#endif  // BONUS_MALUS_H