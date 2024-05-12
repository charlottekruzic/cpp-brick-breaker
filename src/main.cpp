#include <iostream>
#include <string>

#include "Game.h"

int main(int argc, char* argv[]) {
  if (argc != 3) {
    //-t pour triangle
    //-s pour square
    std::cerr << "Usage: " << argv[0] << " <nom_fichier_grille>"
              << " <type_cellule>\n"
              << std::endl;
    return 1;
  }

  std::string nomFichierGrille = argv[1];
  std::string shapeCellule = argv[2];

  // Vérifier si l'utilisateur demande de l'aide
  std::string argument = argv[1];
  if (argument == "--help") {
    std::cout
        << "Ce programme est un jeu de casse-briques.\n"
        << "Pour jouer, veuillez fournir le nom du fichier de grille "
        << "en tant qu'argument.\n"
        << "Exemple d'utilisation: " << argv[0] << " grille.txt\n"
        << "Commandes:\n"
        << "\tAu clavier :\n"
        << "\t - Utilisez les touches gauche et droite pour déplacer la "
           "plateforme.\n"
        << "\t - Appuyez sur la barre d'espace pour mettre en pause ou "
           "reprendre le jeu.\n"
        << "\tÀ la souris :\n"
        << "\t - Utilisez la souris pour déplacer la plateforme et cliquez "
           "pour mettre en pause ou reprendre le jeu.\n"

        << "Programme réalisé par Charlotte Kruzic et Zoé Marquis dans "
           "le cadre du cours de "
        << "programmation avancée de Master 1 informatique - SDSC.\n";
    return 0;
  }

  int ret = 0;
  if (shapeCellule == "-t") {
    Game<TriangleCell> game_triangle(nomFichierGrille, shapeCellule);
    ret = game_triangle.execute();
  } else {
    Game<SquareCell> game_square(nomFichierGrille, shapeCellule);
    ret = game_square.execute();
  }

  return ret;
}
