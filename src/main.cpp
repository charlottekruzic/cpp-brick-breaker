#include <SDL2/SDL.h>

#include <iostream>

#include "Grid.h"

int main() {
  const int screenWidth = 400;
  const int screenHeight = 800;

  // Initialisation de la SDL2
  if (SDL_Init(SDL_INIT_VIDEO) != 0) {
    std::cerr << "Erreur lors de l'initialisation de la SDL2 : "
              << SDL_GetError() << std::endl;
    return 1;
  }

  SDL_Window* window = SDL_CreateWindow("Game Board", SDL_WINDOWPOS_UNDEFINED,
                                        SDL_WINDOWPOS_UNDEFINED, screenWidth,
                                        screenHeight, SDL_WINDOW_SHOWN);
  if (!window) {
    std::cerr << "Error creating window: " << SDL_GetError() << std::endl;
    return 1;
  }

  SDL_Renderer* renderer =
      SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
  if (!renderer) {
    std::cerr << "Error creating renderer: " << SDL_GetError() << std::endl;
    SDL_DestroyWindow(window);
    return 1;
  }

  // Création de la grille en utilisant le constructeur prenant en charge le
  // fichier d'entrée
  Grid grid("../grilles/grille2.txt");

  bool quit = false;
  while (!quit) {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
      if (event.type == SDL_QUIT) {
        quit = true;
      }
    }

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    grid.renderGrid(renderer, screenWidth, screenHeight);
    SDL_RenderPresent(renderer);
  }
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();

  return 0;
}
