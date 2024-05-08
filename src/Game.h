#ifndef GAME_H
#define GAME_H

#include <SDL2/SDL.h>

#include "Ball.h"
#include "CollisionManager.h"
#include "Grid.h"
#include "Plateform.h"

class Game {
 public:
  Game();
  ~Game();
  void initGameComponents();  // POur retarder chargement des images
  int execute();

 private:
  const int screen_width_ = 400;
  const int screen_height_ = 800;
  bool quit_ = false;
  bool game_over_ = false;
  bool game_finished_ = false;
  bool left_key_down_ = false;
  bool right_key_down_ = false;
  bool paused_ = true;

  SDL_Window* window_ = nullptr;
  SDL_Renderer* renderer_ = nullptr;
  Grid* grid_;
  Plateform plateform_;
  Ball ball_;

  void initSDL();
  void createWindowAndRenderer();
  void mainLoop();
  void cleanUp();
  void handleEvents(SDL_Event& event);
  void updateGame(float dt);
  void render();
  void togglePause();
};

#endif  // GAME_H
