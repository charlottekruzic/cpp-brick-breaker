#include <iostream>

#include "Game.h"

int main(int argc, char* argv[]) {
  if (argc != 2) {
    std::cerr << "Usage: " << argv[0] << " <nom_fichier_grille>" << std::endl;
    return 1;
  }

  std::string nomFichierGrille = argv[1];

  Game game(nomFichierGrille);  // Passer le nom du fichier à Game

  return game.execute();
}
