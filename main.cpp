#include <SDL2/SDL.h>

#include <iostream>

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

  // Attendre 5 secondes
  // SDL_Delay(5000);
  Grille maGrille(
      "grille.txt");  // Remplacez "grille.txt" par le nom de votre fichier
                      // ASCII contenant la grille de briques
  maGrille.afficherGrille();

  // Nettoyage et fermeture de la SDL2
  SDL_DestroyWindow(window);
  SDL_Quit();

  return 0;
}
