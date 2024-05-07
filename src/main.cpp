#include <SDL2/SDL.h>

#include <iostream>

#include "Ball.h"
#include "CollisionManager.h"
#include "Grid.h"
#include "Plateform.h"

int main() {
  const int screenWidth = 400;
  const int screenHeight = 800;

  // Initialisation de la SDL2
  if (SDL_Init(SDL_INIT_VIDEO) != 0) {
    std::cerr << "Erreur lors de l'initialisation de la SDL2 : "
              << SDL_GetError() << std::endl;
    return 1;
  }

  // Création de la fenêtre
  SDL_Window* window = SDL_CreateWindow("Game Board", SDL_WINDOWPOS_CENTERED,
                                        SDL_WINDOWPOS_CENTERED, screenWidth,
                                        screenHeight, SDL_WINDOW_SHOWN);
  if (!window) {
    std::cerr << "Error creating window: " << SDL_GetError() << std::endl;
    SDL_Quit();
    return 1;
  }

  SDL_Renderer* renderer =
      SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
  if (!renderer) {
    std::cerr << "Error creating renderer: " << SDL_GetError() << std::endl;
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 1;
  }

  // Création de la grille en utilisant le constructeur prenant en charge le
  // fichier d'entrée
  Grid grid("../grilles/grille2.txt", screenWidth, screenHeight, renderer);

  // Création grille
  bool leftKeyDown = false;
  bool rightKeyDown = false;
  Plateform MyPlateform(screenWidth, screenHeight);
  MyPlateform.render(renderer);
  SDL_RenderPresent(renderer);

  // Création de la balle
  Ball MyBall(10, 300, MyPlateform.getPosX(), MyPlateform.getPosY(),
              MyPlateform.getWidth(), 0.5, -0.5);

  bool quit = false;
  bool game_over = false;
  SDL_Event event;

  // Gestion temps
  Uint32 previousTime = SDL_GetTicks();
  Uint32 currentTime, deltaTime;
  float dt;  // en s

  while (!quit && !game_over) {
    currentTime = SDL_GetTicks();
    dt = (currentTime - previousTime) / 1000.0f;

    previousTime = currentTime;

    if (SDL_PollEvent(&event)) {
      if (event.type == SDL_QUIT) {
        quit = true;
      }
      // Clavier
      else if (event.type == SDL_KEYDOWN) {
        if (event.key.keysym.sym == SDLK_LEFT) {
          leftKeyDown = true;
        } else if (event.key.keysym.sym == SDLK_RIGHT) {
          rightKeyDown = true;
        }
      } else if (event.type == SDL_KEYUP) {
        if (event.key.keysym.sym == SDLK_LEFT) {
          leftKeyDown = false;
        } else if (event.key.keysym.sym == SDLK_RIGHT) {
          rightKeyDown = false;
        }
      }

      // Souris
      else if (event.type == SDL_MOUSEMOTION) {
        int mouseX, mouseY;
        SDL_GetMouseState(&mouseX, &mouseY);
        MyPlateform.move_mouse(mouseX, mouseY, screenWidth);
      }
    }

    // MIse à jour position plateforme
    if (leftKeyDown) {
      MyPlateform.move_keyboard(SDLK_LEFT, screenWidth, dt);
    }
    if (rightKeyDown) {
      MyPlateform.move_keyboard(SDLK_RIGHT, screenWidth, dt);
    }

    // Mise à jour position balle
    game_over = MyBall.updatePosition(dt, screenWidth, screenHeight);

    CollisionManager::checkCollisions(MyPlateform, MyBall, grid);

    // Mise à jour affichage
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    grid.renderGrid(renderer, screenWidth, screenHeight);
    MyPlateform.render(renderer);
    MyBall.render(renderer);

    SDL_RenderPresent(renderer);
  }

  if (game_over) {
    std::cout << "Game Over !!" << std::endl;
  }

  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();

  return 0;
}
