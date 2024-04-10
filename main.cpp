#include <SDL2/SDL.h>

#include <iostream>

#include "src/plateform.h"

int main() {
  // Initialisation de la SDL2
  if (SDL_Init(SDL_INIT_VIDEO) != 0) {
    std::cerr << "Erreur lors de l'initialisation de la SDL2 : "
              << SDL_GetError() << std::endl;
    return 1;
  }

  // Création de la fenêtre
  SDL_Window* window =
      SDL_CreateWindow("Fenetre simple", SDL_WINDOWPOS_CENTERED,
                       SDL_WINDOWPOS_CENTERED, 640, 480, SDL_WINDOW_SHOWN);
  if (window == nullptr) {
    std::cerr << "Erreur lors de la création de la fenêtre : " << SDL_GetError()
              << std::endl;
    SDL_Quit();
    return 1;
  }

  // Création d'un renderer
  SDL_Renderer* renderer =
      SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

  if (renderer == nullptr) {
    std::cerr << "Erreur lors de la création du renderer: " << SDL_GetError()
              << std::endl;
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 1;
  }

  int window_width, window_height;
  SDL_GetWindowSize(window, &window_width, &window_height);

  Plateform MyPlateform(window_width, window_height);
  MyPlateform.render(renderer);
  SDL_RenderPresent(renderer);

  bool end = false;
  SDL_Event event;

  // boucle de jeu
  while (!end) {
    while (SDL_PollEvent(&event)) {
      if (event.type == SDL_QUIT) {
        end = true;
      } else if (event.type == SDL_KEYDOWN) {
        std::cout << "Key pressed: " << event.key.keysym.sym << std::endl;
        MyPlateform.move_keyboard(event.key.keysym.sym);
      }
    }

    // Mise à jour affichage
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    MyPlateform.render(renderer);

    SDL_RenderPresent(renderer);
  }

  // Attendre 5 secondes
  // SDL_Delay(5000);

  // Nettoyage et fermeture de la SDL2
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();

  return 0;
}
