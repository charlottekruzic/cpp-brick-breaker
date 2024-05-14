#include <SDL2/SDL_ttf.h>

#include <iostream>
#include <memory>
#include <string>

#include "Game.h"

void startInterface(std::shared_ptr<SDL_Renderer>& renderer,
                    std::string& shapeCellule) {
  bool selected = false;
  SDL_Event event;

  // Initialisation SDL_ttf
  if (TTF_Init() == -1) {
    std::cerr << "Erreur d'initialisation de TTF : " << TTF_GetError()
              << std::endl;
    return;
  }

  // Charger les polices
  std::unique_ptr<TTF_Font, decltype(&TTF_CloseFont)> font_button(
      TTF_OpenFont("../ttf/Super Creamy Personal Use.ttf", 24), TTF_CloseFont);
  if (!font_button) {
    std::cerr << "Erreur lors du chargement de la police  pour les boutons"
              << std::endl;
    return;
  }

  std::unique_ptr<TTF_Font, decltype(&TTF_CloseFont)> font_title(
      TTF_OpenFont("../ttf/Super Creamy Personal Use.ttf", 50), TTF_CloseFont);
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
  std::unique_ptr<SDL_Surface, decltype(&SDL_FreeSurface)> textSurfaceSquare(
      TTF_RenderText_Solid(font_button.get(), "Square", textColor),
      SDL_FreeSurface);
  std::unique_ptr<SDL_Surface, decltype(&SDL_FreeSurface)> textSurfaceTriangle(
      TTF_RenderText_Solid(font_button.get(), "Triangle", textColor),
      SDL_FreeSurface);
  std::unique_ptr<SDL_Surface, decltype(&SDL_FreeSurface)> textSurfaceHexagon(
      TTF_RenderText_Solid(font_button.get(), "Hexagon", textColor),
      SDL_FreeSurface);
  std::shared_ptr<SDL_Texture> textTextureSquare(
      SDL_CreateTextureFromSurface(renderer.get(), textSurfaceSquare.get()),
      SDL_DestroyTexture);
  std::shared_ptr<SDL_Texture> textTextureTriangle(
      SDL_CreateTextureFromSurface(renderer.get(), textSurfaceTriangle.get()),
      SDL_DestroyTexture);
  std::shared_ptr<SDL_Texture> textTextureHexagon(
      SDL_CreateTextureFromSurface(renderer.get(), textSurfaceHexagon.get()),
      SDL_DestroyTexture);

  // Texte titre
  std::unique_ptr<SDL_Surface, decltype(&SDL_FreeSurface)> titleSurface(
      TTF_RenderText_Solid(font_title.get(), "Brick Breaker", textColor),
      SDL_FreeSurface);
  std::shared_ptr<SDL_Texture> titleTexture(
      SDL_CreateTextureFromSurface(renderer.get(), titleSurface.get()),
      SDL_DestroyTexture);
  int titleWidth, titleHeight;
  TTF_SizeText(font_title.get(), "Brick Breaker", &titleWidth, &titleHeight);
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
    SDL_SetRenderDrawColor(renderer.get(), 0, 0, 0, 255);
    SDL_RenderClear(renderer.get());
    SDL_SetRenderDrawColor(renderer.get(), 169, 40, 255, 255);
    SDL_RenderFillRect(renderer.get(), &squareButton);
    SDL_RenderFillRect(renderer.get(), &triangleButton);
    SDL_RenderFillRect(renderer.get(), &hexagonButton);

    // Affichage texte
    TTF_SizeText(font_button.get(), "Square", &textWidth, &textHeight);
    SDL_Rect textRectSquare = {
        squareButton.x + (squareButton.w - textWidth) / 2,
        squareButton.y + (squareButton.h - textHeight) / 2, textWidth,
        textHeight};
    TTF_SizeText(font_button.get(), "Triangle", &textWidth, &textHeight);
    SDL_Rect textRectTriangle = {
        triangleButton.x + (triangleButton.w - textWidth) / 2,
        triangleButton.y + (triangleButton.h - textHeight) / 2, textWidth,
        textHeight};
    TTF_SizeText(font_button.get(), "Hexagon", &textWidth, &textHeight);
    SDL_Rect textRectHexagon = {
        hexagonButton.x + (hexagonButton.w - textWidth) / 2,
        hexagonButton.y + (hexagonButton.h - textHeight) / 2, textWidth,
        textHeight};

    SDL_RenderCopy(renderer.get(), textTextureSquare.get(), NULL,
                   &textRectSquare);
    SDL_RenderCopy(renderer.get(), textTextureTriangle.get(), NULL,
                   &textRectTriangle);
    SDL_RenderCopy(renderer.get(), textTextureHexagon.get(), NULL,
                   &textRectHexagon);

    // Affichage du titre
    SDL_RenderCopy(renderer.get(), titleTexture.get(), NULL, &titleRect);

    SDL_RenderPresent(renderer.get());
  }
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

  std::unique_ptr<SDL_Window, decltype(&SDL_DestroyWindow)> window(
      SDL_CreateWindow("Game Board", SDL_WINDOWPOS_CENTERED,
                       SDL_WINDOWPOS_CENTERED, 400, 800, SDL_WINDOW_SHOWN),
      SDL_DestroyWindow);
  std::shared_ptr<SDL_Renderer> renderer(
      SDL_CreateRenderer(window.get(), -1, SDL_RENDERER_ACCELERATED),
      SDL_DestroyRenderer);

  std::string shapeCellule;

  // Lancement de la fenêtre de choix + attente du choix
  startInterface(renderer, shapeCellule);

  // fermeture fenetre de choix
  SDL_DestroyRenderer(renderer.get());
  SDL_DestroyWindow(window.get());
  SDL_Quit();
  TTF_Quit();

  if (shapeCellule == "-t") {
    // demarrage du jeu
    Game<TriangleCell> game_triangle(nomFichierGrille);
    game_triangle.execute();
  } else if (shapeCellule == "-s") {
    // demarrage du jeu
    Game<SquareCell> game_square(nomFichierGrille);
    game_square.execute();
  } else if (shapeCellule == "-h") {
    // demarrage du jeu
    Game<HexagonCell> game_hexagon(nomFichierGrille);
    game_hexagon.execute();
  }

  return 0;
}
