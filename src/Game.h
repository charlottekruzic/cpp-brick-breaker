#ifndef GAME_H
#define GAME_H

#include <SDL2/SDL.h>

#include <chrono>

#include "Ball.h"
#include "BonusMalus.h"
#include "CollisionManager.h"
#include "Grid.h"
#include "Plateform.h"
#include "Shrink.h"

class Ball;
class Grid;

class Game {
 public:
  Game(const std::string& nomFichierGrille);
  ~Game();
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
  Ball* ball_;

  void initSDL();
  void createWindowAndRenderer();
  void mainLoop();
  void cleanUp();
  void handleEvents(SDL_Event& event);
  void initGameComponents(const std::string& nomFichierGrille);
  void updateGame(float dt);
  void render();
  void togglePause();

  void generateBonusMalus();
  std::vector<BonusMalus*> bonus_maluses_;

  bool ball_accelerating_ = false;

 public:
  void setBallAccelerating();
  void setBallDecelerating();

  void shrinkPlateformWidth();
  void enlargePlateformWidth();

  // threads :

  // Méthode pour démarrer l'accélération de la balle
  // void startBallAcceleration();
  // Méthode pour vérifier si l'accélération de la balle est toujours active
  // bool isBallAccelerating() const;
  // bool ball_accelerating_;  // Indique si la balle
  // est en train d'être
  // accélérée
  // std::chrono::steady_clock::time_point acceleration_start_time_;  // Moment
  // où l'accélération a commencé
};

#endif  // GAME_H
