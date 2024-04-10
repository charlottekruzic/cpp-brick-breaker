#include <SDL2/SDL.h>

#include <iostream>

#include "Ball.h"
#include "Grid.h"
#include "Plateform.h"

int main() {
  const int screenWidth = 400;
  const int screenHeight = 400;

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
  Grid grid("../grilles/grille2.txt");

  // Création grille
  Plateform MyPlateform(screenWidth, screenHeight);
  MyPlateform.render(renderer);
  SDL_RenderPresent(renderer);

  // Création de la balle
  Ball MyBall(10, 400, MyPlateform.getPosX(), MyPlateform.getPosY(),
              MyPlateform.getWidth(), 0.5, -0.5);

  bool quit = false;
  SDL_Event event;

  // Gestion temps
  Uint32 previousTime = SDL_GetTicks();
  Uint32 currentTime, deltaTime;
  float dt;  // en s

  while (!quit) {
    currentTime = SDL_GetTicks();
    dt = (currentTime - previousTime) / 1000.0f;

    previousTime = currentTime;

    if (SDL_PollEvent(&event)) {
      if (event.type == SDL_QUIT) {
        quit = true;
      }
      // Clavier
      else if (event.type == SDL_KEYDOWN) {
        MyPlateform.move_keyboard(event.key.keysym.sym, screenWidth);
      }
      // Souris
      else if (event.type == SDL_MOUSEMOTION) {
        int mouseX, mouseY;
        SDL_GetMouseState(&mouseX, &mouseY);
        MyPlateform.move_mouse(mouseX, mouseY, screenWidth);
      }
    }

    // Mise à jour position balle
    MyBall.updatePosition(dt, screenWidth, screenHeight);

    // Check collisions avec plateforme
    MyBall.checkCollide(MyPlateform);

    // Mise à jour affichage
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    // grid.renderGrid(renderer, screenWidth, screenHeight);
    MyPlateform.render(renderer);
    MyBall.render(renderer);

    SDL_RenderPresent(renderer);
  }

  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();

  return 0;
}
