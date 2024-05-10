#include "Game.h"

#include <iostream>
#include <random>
#include <vector>

#include "bonus_malus/Enlarge.h"
#include "bonus_malus/Shrink.h"

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
  grid_ = std::make_shared<Grid>(nomFichierGrille, screen_width_,
                                 screen_height_, renderer_, this);
  ball_ = std::make_shared<Ball>(10, 500, plateform_.getPosX(),
                                 plateform_.getPosY(), plateform_.getWidth(),
                                 0.5, -0.5);
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
  // Mise à jour position balle
  game_over_ = ball_->updatePosition(dt, screen_width_, screen_height_);
  // Vérifier les collisions
  CollisionManager::checkCollisions(plateform_, ball_, grid_, bonus_maluses_);

  game_finished_ = !grid_->hasRemainingBricks();
}

void Game::render() {
  // Mise à jour affichage
  SDL_SetRenderDrawColor(renderer_.get(), 0, 0, 0, 255);
  SDL_RenderClear(renderer_.get());

  grid_->renderGrid(renderer_, screen_width_, screen_height_);
  plateform_.render(renderer_);
  ball_->render(renderer_);
  // pour tous les éléments de la liste bonus malus -> render
  for (auto bonus_malus : bonus_maluses_) {
    bonus_malus->render(renderer_);
  }

  SDL_RenderPresent(renderer_.get());
}

void Game::cleanUp() {
  SDL_DestroyRenderer(renderer_.get());
  SDL_DestroyWindow(window_.get());
  SDL_Quit();
}
void Game::setBallAccelerating() { ball_->setSpeed(700); }

void Game::setBallDecelerating() {
  if (ball_->getSpeed() == 500)
    ball_->setSpeed(300);
  else
    ball_->setSpeed(300);  // retour à la normale
}

void Game::shrinkPlateformWidth() {
  if (plateform_.getWidth() > 50)
    plateform_.setWidth(plateform_.getWidth() - 30);
}
void Game::enlargePlateformWidth() {
  if (plateform_.getWidth() < 200)
    plateform_.setWidth(plateform_.getWidth() + 30);
}

/* grére des threads pour n'accélrer que pendant 5 secondes :
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
*/

/*
void Game::generateBonusMalus() {
  int random = rand() % 90 + 2;

  // Si le nombre aléatoire est égal à 1, générer un objet Shrink
  if (random == 1) {
    // Générer une position aléatoire en largeur
    int randomX =
        rand() % (screen_width_ - 10);  // Ajustez la plage selon vos besoins

    BonusMalus* bm;
    if (rand() % 2)
      // Créer un nouvel objet Shrink avec la position aléatoire en largeur
      bm = new Shrink(this, randomX, 0);
    else
      bm = new Enlarge(this, randomX, 0);

    // Ajouter l'objet Shrink à une liste ou un vecteur de BonusMalus
    // par exemple:
    bonus_maluses_.insert(bm);
  }
}
*/

void Game::generateBonusMalus() {
  // Générateur de nombres aléatoires
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<> distrib(1, 100);

  // Générer un nombre aléatoire entre 1 et 100
  int random = distrib(gen);

  // Si le nombre aléatoire est égal à 1, générer un objet Shrink ou Enlarge
  if (random == 1) {
    // Générer une position aléatoire en largeur
    int randomX = std::uniform_int_distribution<>(0, screen_width_ - 10)(gen);

    // Créer un nouvel objet Shrink avec la position aléatoire en largeur
    std::shared_ptr<BonusMalus> bm;
    if (std::uniform_int_distribution<>(0, 1)(gen) == 0)
      bm = std::make_shared<Shrink>(this, randomX, 0);
    else
      bm = std::make_shared<Enlarge>(this, randomX, 0);

    // Ajouter l'objet Shrink ou Enlarge au vecteur de BonusMalus
    // bonus_maluses_.push_back(std::move(bm));
    bonus_maluses_.insert(bm);
  }
}
