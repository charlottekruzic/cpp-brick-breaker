#include "Game.h"

#include <iostream>

Game::Game(const std::string& nomFichierGrille)
    : plateform_(screen_width_, screen_height_), ball_(nullptr) {
  initSDL();
  createWindowAndRenderer();
  initGameComponents(nomFichierGrille);
}

Game::~Game() { cleanUp(); }

void Game::initSDL() {
  if (SDL_Init(SDL_INIT_VIDEO) != 0) {
    std::cerr << "Erreur lors de l'initialisation de la SDL2: "
              << SDL_GetError() << std::endl;
    exit(1);
  }
}

void Game::createWindowAndRenderer() {
  window_ = SDL_CreateWindow("Game Board", SDL_WINDOWPOS_CENTERED,
                             SDL_WINDOWPOS_CENTERED, screen_width_,
                             screen_height_, SDL_WINDOW_SHOWN);
  if (!window_) {
    std::cerr << "Error creating windows_: " << SDL_GetError() << std::endl;
    SDL_Quit();
    exit(1);
  }

  renderer_ = SDL_CreateRenderer(window_, -1, SDL_RENDERER_ACCELERATED);
  if (!renderer_) {
    std::cerr << "Error creating renderer_: " << SDL_GetError() << std::endl;
    SDL_DestroyWindow(window_);
    SDL_Quit();
    exit(1);
  }
}

void Game::initGameComponents(const std::string& nomFichierGrille) {
  grid_ = new Grid(nomFichierGrille, screen_width_, screen_height_, renderer_,
                   this);
  ball_ = new Ball(10, 500, plateform_.getPosX(), plateform_.getPosY(),
                   plateform_.getWidth(), 0.5, -0.5);
}

int Game::execute() {
  mainLoop();
  return 0;
}

void Game::togglePause() { paused_ = !paused_; }

void Game::mainLoop() {
  Uint32 previousTime = SDL_GetTicks();
  const int frameRate = 50;
  const int maxFrameTime = 1000 / frameRate;

  SDL_Event event;
  bool premiere_iter = true;
  while (!quit_ && !game_over_ && !game_finished_) {
    Uint32 startTime = SDL_GetTicks();
    float dt = (startTime - previousTime) / 1000.0f;
    previousTime = startTime;

    while (SDL_PollEvent(&event)) {
      handleEvents(event);
    }

    if (premiere_iter || !paused_) {
      updateGame(dt);
      render();
    }

    // Pause si boucle trop rapide
    int frameTime = SDL_GetTicks() - startTime;
    if (frameTime < maxFrameTime) {
      SDL_Delay(maxFrameTime - frameTime);
    }

    premiere_iter = false;
  }

  if (game_finished_) {
    std::cout << "Bravo !!" << std::endl;
  }
  if (game_over_) {
    std::cout << "Game Over !!" << std::endl;
  }
}

void Game::handleEvents(SDL_Event& event) {
  if (event.type == SDL_QUIT) {
    quit_ = true;
  }
  // Clavier
  else if (event.type == SDL_KEYDOWN) {
    if (event.key.keysym.sym == SDLK_LEFT) {
      left_key_down_ = true;
    } else if (event.key.keysym.sym == SDLK_RIGHT) {
      right_key_down_ = true;
    } else if (event.key.keysym.sym == SDLK_SPACE) {
      // Mettre en pause ou reprendre le jeu lorsque la barre d'espace est
      // enfoncée
      togglePause();
    }
  } else if (event.type == SDL_KEYUP) {
    if (event.key.keysym.sym == SDLK_LEFT) {
      left_key_down_ = false;
    } else if (event.key.keysym.sym == SDLK_RIGHT) {
      right_key_down_ = false;
    }
  }

  // Souris
  else if (event.type == SDL_MOUSEMOTION) {
    int mouseX, mouseY;
    SDL_GetMouseState(&mouseX, &mouseY);
    plateform_.move_mouse(mouseX, mouseY, screen_width_);
  } else if (event.type == SDL_MOUSEBUTTONDOWN) {
    // Mettre en pause ou reprendre le jeu lors d'un clic de souris
    togglePause();
  }
}

void Game::updateGame(float dt) {
  // Mise à jour position balle
  game_over_ = ball_->updatePosition(dt, screen_width_, screen_height_);
  // Vérifier les collisions
  CollisionManager::checkCollisions(plateform_, ball_, *grid_);

  game_finished_ = !grid_->hasRemainingBricks();
}

void Game::render() {
  // Mise à jour affichage
  SDL_SetRenderDrawColor(renderer_, 0, 0, 0, 255);
  SDL_RenderClear(renderer_);

  grid_->renderGrid(renderer_, screen_width_, screen_height_);
  plateform_.render(renderer_);
  ball_->render(renderer_);

  SDL_RenderPresent(renderer_);
}

void Game::cleanUp() {
  SDL_DestroyRenderer(renderer_);
  SDL_DestroyWindow(window_);
  SDL_Quit();
}

//

void Game::startBallAcceleration() {
  ball_accelerating_ = true;
  acceleration_start_time_ = std::chrono::steady_clock::now();
}

bool Game::isBallAccelerating() const {
  if (ball_accelerating_) {
    auto current_time = std::chrono::steady_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::seconds>(
        current_time - acceleration_start_time_);
    return duration.count() < 5;  // Vérifie si l'accélération est active depuis
                                  // moins de 5 secondes
  }
  return false;
}
