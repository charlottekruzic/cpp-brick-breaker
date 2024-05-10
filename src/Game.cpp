#include "Game.h"

#include <iostream>
#include <random>
#include <vector>

#include "bonus_malus/Enlarge.h"
#include "bonus_malus/MultiBall.h"
#include "bonus_malus/Shrink.h"
#include "bonus_malus/SlowedDown.h"
#include "bonus_malus/SpedUp.h"

Game::Game(const std::string& nomFichierGrille)
    : plateform_(screen_width_, screen_height_) {
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
  window_ = std::shared_ptr<SDL_Window>(
      SDL_CreateWindow("Game Board", SDL_WINDOWPOS_CENTERED,
                       SDL_WINDOWPOS_CENTERED, screen_width_, screen_height_,
                       SDL_WINDOW_SHOWN),
      [](SDL_Window* window) {
        if (window) SDL_DestroyWindow(window);
      });

  if (!window_) {
    std::cerr << "Error creating windows_: " << SDL_GetError() << std::endl;
    SDL_Quit();
    exit(1);
  }

  renderer_ = std::shared_ptr<SDL_Renderer>(
      SDL_CreateRenderer(window_.get(), -1, SDL_RENDERER_ACCELERATED),
      [](SDL_Renderer* renderer) {
        if (renderer) SDL_DestroyRenderer(renderer);
      });
  if (!renderer_) {
    std::cerr << "Error creating renderer_: " << SDL_GetError() << std::endl;
    SDL_DestroyWindow(window_.get());
    SDL_Quit();
    exit(1);
  }
}

void Game::initGameComponents(const std::string& nomFichierGrille) {
  grid_ = std::make_shared<Grid<SquareCell>>(nomFichierGrille, screen_width_,
                                             screen_height_, renderer_, this);
  balls_.insert(std::make_shared<Ball>(10, 500, plateform_.getPosX(),
                                       plateform_.getPosY(),
                                       plateform_.getWidth(), 0.5, -0.5));
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
  // update tous les bonus malus de bonus_maluses__
  for (auto& bonusMalus : bonus_maluses_) {
    bonusMalus->update();
  }
  // supprimer les bonus malus en bas de l'image du vector
  for (auto it = bonus_maluses_.begin(); it != bonus_maluses_.end();) {
    // Si le bonus/malus est en dehors de l'écran (en bas), supprimez-le
    if ((*it)->getY() >= screen_height_) {
      it = bonus_maluses_.erase(it);
      // Supprime l'élément et renvoie l'itérateur suivant
    } else {
      ++it;  // Passe à l'élément suivant
    }
  }

  generateBonusMalus();

  /*
  // Supprimer les bonus/malus en bas de l'écran du vecteur
  bonus_maluses_.erase(
      std::remove_if(bonus_maluses_.begin(), bonus_maluses_.end(),
                     [this](const auto& bonusMalus) {
                       return bonusMalus->getY() >= screen_height_;
                     }),
      bonus_maluses_.end());
  */
  // Mise à jour de la position de chaque balle dans le vecteur balls_
  for (auto it = balls_.begin(); it != balls_.end();) {
    // Mettre à jour la position de la balle et vérifier si elle est en dehors
    // de l'écran
    if ((*it)->updatePosition(dt, screen_width_, screen_height_)) {
      // Si une balle est hors de l'écran, la supprimer de l'ensemble balls_
      it = balls_.erase(it);
    } else {
      ++it;  // Passer à l'élément suivant dans le cas où la balle est toujours
             // à l'intérieur de l'écran
    }
  }

  // Vérifier les collisions
  CollisionManager::checkCollisions(plateform_, balls_, grid_, bonus_maluses_);

  game_finished_ = !grid_->hasRemainingBricks();
  game_over_ = balls_.empty();
}

void Game::render() {
  // Mise à jour affichage
  SDL_SetRenderDrawColor(renderer_.get(), 0, 0, 0, 255);
  SDL_RenderClear(renderer_.get());

  grid_->renderGrid(renderer_, screen_width_, screen_height_);
  plateform_.render(renderer_);
  // Rendu de chaque balle dans le vecteur
  for (const auto& ball : balls_) {
    ball->render(renderer_);
  }

  // Rendu de chaque bonus/malus dans la liste bonus_maluses_
  for (const auto& bonus_malus : bonus_maluses_) {
    bonus_malus->render(renderer_);
  }
  SDL_RenderPresent(renderer_.get());
}

void Game::cleanUp() {
  SDL_DestroyRenderer(renderer_.get());
  SDL_DestroyWindow(window_.get());
  SDL_Quit();
}

void Game::setBallAccelerating() {
  for (const auto& ball : balls_) {
    if (ball->getSpeed() == 500) {
      ball->setSpeed(700);
    } else {
      ball->setSpeed(500);
    }
  }
}

void Game::setBallDecelerating() {
  for (const auto& ball : balls_) {
    if (ball->getSpeed() == 500) {
      ball->setSpeed(300);
    } else {
      ball->setSpeed(500);
    }
  }
}

void Game::shrinkPlateformWidth() {
  if (plateform_.getWidth() > 50)
    plateform_.setWidth(plateform_.getWidth() - 30);
}
void Game::enlargePlateformWidth() {
  if (plateform_.getWidth() < 200)
    plateform_.setWidth(plateform_.getWidth() + 30);
}

void Game::generateBonusMalus() {
  // Générateur de nombres aléatoires
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<> distrib(1, 100);

  // Générer un nombre aléatoire entre 1 et 100
  int random = distrib(gen);

  // Si le nombre aléatoire est égal à 1, générer un objet Shrink, Enlarge,
  // SpeedUp ou SlowDown
  if (random == 1) {
    // Générer une position aléatoire en largeur
    int randomX = std::uniform_int_distribution<>(0, screen_width_ - 10)(gen);

    // Générer un nombre aléatoire entre 0 et 3 pour choisir le type de
    // BonusMalus
    int type = std::uniform_int_distribution<>(0, 10)(gen);

    std::shared_ptr<BonusMalus> bm;

    switch (type) {
      case 0:
      case 1:
        bm = std::make_shared<Shrink>(this, randomX, 0);
        break;

      case 2:
      case 3:
      case 4:
        bm = std::make_shared<Enlarge>(this, randomX, 0);
        break;

      case 5:
      case 6:
        bm = std::make_shared<SpedUp>(this, randomX, 0);
        break;

      case 7:
      case 8:
      case 9:
        bm = std::make_shared<SlowedDown>(this, randomX, 0);
        break;

      case 10:
        bm = std::make_shared<MultiBall>(this, randomX, 0);
        break;
      default:
        // En cas de type invalide, ne rien faire
        break;
    }

    // Ajouter l'objet au vecteur de BonusMalus
    bonus_maluses_.insert(bm);
  }
}

void Game::generateNewBalls() {
  // Créer deux nouvelles balles avec des positions aléatoires
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<> distrib(1, 100);
  int random = distrib(gen);
  int randomX1 = std::uniform_int_distribution<>(0, screen_width_ - 10)(gen);
  int randomX2 = std::uniform_int_distribution<>(0, screen_width_ - 10)(gen);

  auto ball1 = std::make_shared<Ball>(
      10, 500, std::max(plateform_.getPosX() - 20, 5), plateform_.getPosY(),
      plateform_.getWidth(), 0.5, -0.5);

  auto ball2 = std::make_shared<Ball>(
      10, 500, std::min(plateform_.getPosX() + 20, screen_width_ - 5),
      plateform_.getPosY(), plateform_.getWidth(), 0.5, -0.5);

  // Ajouter les nouvelles balles à la liste des balles du jeu
  balls_.insert(ball1);
  balls_.insert(ball2);
}