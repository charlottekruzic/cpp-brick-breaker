#include <SDL2/SDL_ttf.h>

#include <iostream>
#include <string>

#include "Game.h"

void startInterface(SDL_Renderer* renderer, std::string& shapeCellule) {
  bool selected = false;
  SDL_Event event;

  // Initialisation SDL_ttf
  if (TTF_Init() == -1) {
    std::cerr << "Erreur d'initialisation de TTF : " << TTF_GetError()
              << std::endl;
    return;
  }

  // Charger les polices
  TTF_Font* font_button =
      TTF_OpenFont("../ttf/Super Creamy Personal Use.ttf", 24);
  if (!font_button) {
    std::cerr << "Erreur lors du chargement de la police  pour les boutons"
              << std::endl;
    return;
  }

  TTF_Font* font_title =
      TTF_OpenFont("../ttf/Super Creamy Personal Use.ttf", 50);
  if (!font_title) {
    std::cerr << "Erreur lors du chargement de la police pour le titre"
              << std::endl;
    return;
  }

  // Boutons
  SDL_Rect squareButton = {100, 200, 200, 50};
  SDL_Rect triangleButton = {100, 300, 200, 50};
  SDL_Rect hexagonButton = {100, 400, 200, 50};

  // Texte boutons
  SDL_Color textColor = {255, 255, 255};
  int textWidth, textHeight;
  SDL_Surface* textSurfaceSquare =
      TTF_RenderText_Solid(font_button, "Square", textColor);
  SDL_Surface* textSurfaceTriangle =
      TTF_RenderText_Solid(font_button, "Triangle", textColor);
  SDL_Surface* textSurfaceHexagon =
      TTF_RenderText_Solid(font_button, "Hexagon", textColor);
  SDL_Texture* textTextureSquare =
      SDL_CreateTextureFromSurface(renderer, textSurfaceSquare);
  SDL_Texture* textTextureTriangle =
      SDL_CreateTextureFromSurface(renderer, textSurfaceTriangle);
  SDL_Texture* textTextureHexagon =
      SDL_CreateTextureFromSurface(renderer, textSurfaceHexagon);

  // Texte titre
  SDL_Surface* titleSurface =
      TTF_RenderText_Solid(font_title, "Brick Breaker", textColor);
  SDL_Texture* titleTexture =
      SDL_CreateTextureFromSurface(renderer, titleSurface);
  int titleWidth, titleHeight;
  TTF_SizeText(font_title, "Brick Breaker", &titleWidth, &titleHeight);
  SDL_Rect titleRect = {(400 - titleWidth) / 2, 50, titleWidth, titleHeight};

  // Attente clique
  while (!selected) {
    while (SDL_PollEvent(&event)) {
      if (event.type == SDL_QUIT) {
        exit(0);
      }
      // Cliques
      else if (event.type == SDL_MOUSEBUTTONDOWN) {
        int x = event.button.x;
        int y = event.button.y;

        if (x >= squareButton.x && x <= squareButton.x + squareButton.w &&
            y >= squareButton.y && y <= squareButton.y + squareButton.h) {
          shapeCellule = "-s";
          selected = true;
        } else if (x >= triangleButton.x &&
                   x <= triangleButton.x + triangleButton.w &&
                   y >= triangleButton.y &&
                   y <= triangleButton.y + triangleButton.h) {
          shapeCellule = "-t";
          selected = true;
        } else if (x >= hexagonButton.x &&
                   x <= hexagonButton.x + hexagonButton.w &&
                   y >= hexagonButton.y &&
                   y <= hexagonButton.y + hexagonButton.h) {
          shapeCellule = "-h";
          selected = true;
        }
      }
    }

    // Affichage fond
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
    SDL_SetRenderDrawColor(renderer, 169, 40, 255, 255);
    SDL_RenderFillRect(renderer, &squareButton);
    SDL_RenderFillRect(renderer, &triangleButton);
    SDL_RenderFillRect(renderer, &hexagonButton);

    // Affichage texte
    TTF_SizeText(font_button, "Square", &textWidth, &textHeight);
    SDL_Rect textRectSquare = {
        squareButton.x + (squareButton.w - textWidth) / 2,
        squareButton.y + (squareButton.h - textHeight) / 2, textWidth,
        textHeight};
    TTF_SizeText(font_button, "Triangle", &textWidth, &textHeight);
    SDL_Rect textRectTriangle = {
        triangleButton.x + (triangleButton.w - textWidth) / 2,
        triangleButton.y + (triangleButton.h - textHeight) / 2, textWidth,
        textHeight};
    TTF_SizeText(font_button, "Hexagon", &textWidth, &textHeight);
    SDL_Rect textRectHexagon = {
        hexagonButton.x + (hexagonButton.w - textWidth) / 2,
        hexagonButton.y + (hexagonButton.h - textHeight) / 2, textWidth,
        textHeight};

    SDL_RenderCopy(renderer, textTextureSquare, NULL, &textRectSquare);
    SDL_RenderCopy(renderer, textTextureTriangle, NULL, &textRectTriangle);
    SDL_RenderCopy(renderer, textTextureHexagon, NULL, &textRectHexagon);

    // Affichage du titre
    SDL_RenderCopy(renderer, titleTexture, NULL, &titleRect);

    SDL_RenderPresent(renderer);
  }

  // Libérer ressources
  SDL_FreeSurface(textSurfaceSquare);
  SDL_FreeSurface(textSurfaceTriangle);
  SDL_FreeSurface(textSurfaceHexagon);
  SDL_FreeSurface(titleSurface);
  SDL_DestroyTexture(textTextureSquare);
  SDL_DestroyTexture(textTextureTriangle);
  SDL_DestroyTexture(textTextureHexagon);
  SDL_DestroyTexture(titleTexture);
  TTF_CloseFont(font_title);
  TTF_CloseFont(font_button);
  TTF_Quit();
}

int main(int argc, char* argv[]) {
  if (argc != 2) {
    std::cerr << "Usage: " << argv[0] << " <nom_fichier_grille>" << std::endl;
    return 1;
  }

  std::string nomFichierGrille = argv[1];

  if (SDL_Init(SDL_INIT_VIDEO) != 0) {
    std::cerr << "Erreur lors de l'initialisation de la SDL2: "
              << SDL_GetError() << std::endl;
    return 1;
  }

  SDL_Window* window =
      SDL_CreateWindow("Game Board", SDL_WINDOWPOS_CENTERED,
                       SDL_WINDOWPOS_CENTERED, 400, 800, SDL_WINDOW_SHOWN);
  SDL_Renderer* renderer =
      SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

  std::string shapeCellule;

  // Lancement de la fenêtre de choix + attente du choix
  startInterface(renderer, shapeCellule);

  if (shapeCellule == "-t") {
    // fermeture fenetre
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    // demarrage du jeu
    Game<TriangleCell> game_triangle(nomFichierGrille, shapeCellule);
    game_triangle.execute();
  } else if (shapeCellule == "-s") {
    // fermeture fenetre
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    // demarrage du jeu
    Game<SquareCell> game_square(nomFichierGrille, shapeCellule);
    game_square.execute();
  } else if (shapeCellule == "-h") {
    // fermeture fenetre
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    // demarrage du jeu
    Game<HexagonCell> game_hexagon(nomFichierGrille, shapeCellule);
    game_hexagon.execute();
  }

  return 0;
}
