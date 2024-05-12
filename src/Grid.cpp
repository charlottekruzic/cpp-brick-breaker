#include "Grid.h"

// #include <iostream>

// #include "bricks/BasicBrick.h"
// #include "bricks/Empty.h"
#include "bricks/EnlargeBrick.h"
//  #include "bricks/MalusBrick.h"
#include "bricks/ShrinkBrick.h"
#include "bricks/SlowedDownBrick.h"
#include "bricks/SpedUpBrick.h"
//  #include "bricks/Wall.h"

#include "SquareCell.h"
#include "TriangleCell.h"

template <>
Grid<SquareCell>::Grid(const std::string& filename, int width, int height,
                       std::shared_ptr<SDL_Renderer>& renderer,
                       Game<SquareCell>* game)
    : width_(width),
      height_(height),
      renderer_(renderer),
      remainingBricks_(0),
      game_(game) {
  InputParser parser(filename);
  if (!parser.parseFile()) {
    // Gérer l'erreur de lecture du fichier
    std::cerr << "Erreur lors de la lecture du fichier '" << filename << "'"
              << std::endl;
    exit(1);
    return;
  }

  // Récupérer les dimensions de la grille depuis le parser
  rows_ = parser.getRows();
  cols_ = parser.getCols();

  // Créer les cases de la grille en fonction du contenu du fichier
  const auto& board = parser.getBoard();

  for (const auto& row : board) {
    std::vector<Cell<SquareCell>*> gridRow;
    for (char c : row) {
      if (c == ' ') {
        gridRow.push_back(new Empty<SquareCell>());
      } else if (c >= '1' && c <= '5') {
        gridRow.push_back(new BasicBrick<SquareCell>(c - '0', game_));
        remainingBricks_++;
      } else if (c == 'A') {
        gridRow.push_back(new SpedUpBrick<SquareCell>(game_, renderer));
      } else if (c == 'D') {
        gridRow.push_back(new SlowedDownBrick<SquareCell>(game_, renderer));
      } else if (c == 'S') {
        gridRow.push_back(new ShrinkBrick<SquareCell>(game_, renderer));
      } else if (c == 'E') {
        gridRow.push_back(new EnlargeBrick<SquareCell>(game_, renderer));
      } else if (c == 'W') {
        gridRow.push_back(new Wall<SquareCell>(renderer));
      } else {
        std::cerr << "Caractère inconnu '" << c
                  << "'. Remplacé par une case vide" << std::endl;
        gridRow.push_back(new Empty<SquareCell>());
      }
    }
    grid_.push_back(gridRow);
  }
}

template <>
Grid<TriangleCell>::Grid(const std::string& filename, int width, int height,
                         std::shared_ptr<SDL_Renderer>& renderer,
                         Game<TriangleCell>* game)
    : width_(width),
      height_(height),
      renderer_(renderer),
      remainingBricks_(0),
      game_(game) {
  InputParser parser(filename);
  if (!parser.parseFile()) {
    // Gérer l'erreur de lecture du fichier
    std::cerr << "Erreur lors de la lecture du fichier" << std::endl;
    return;
  }

  // Récupérer les dimensions de la grille depuis le parser
  rows_ = parser.getRows();
  cols_ = parser.getCols();

  // Créer les cases de la grille en fonction du contenu du fichier
  const auto& board = parser.getBoard();

  for (size_t i = 0; i < board.size(); i++) {
    std::vector<Cell<TriangleCell>*> gridRow;
    for (size_t j = 0; j < board[i].size(); j++) {
      char c = board[i][j];
      TriangleCell::Orientation orientation =
          ((i + j) % 2 == 0) ? TriangleCell::Orientation::UP
                             : TriangleCell::Orientation::DOWN;
      if (c == ' ') {
        gridRow.push_back(new Empty<TriangleCell>());
      } else if (c >= '1' && c <= '5') {
        gridRow.push_back(
            new BasicBrick<TriangleCell>(c - '0', game_, orientation));
        remainingBricks_++;
      } else if (c == 'A') {
        gridRow.push_back(
            new SpedUpBrick<TriangleCell>(game_, renderer, orientation));
      } else if (c == 'D') {
        gridRow.push_back(
            new SlowedDownBrick<TriangleCell>(game_, renderer, orientation));
      } else if (c == 'S') {
        gridRow.push_back(
            new ShrinkBrick<TriangleCell>(game_, renderer, orientation));
      } else if (c == 'E') {
        gridRow.push_back(
            new EnlargeBrick<TriangleCell>(game_, renderer, orientation));
      } else if (c == 'W') {
        gridRow.push_back(new Wall<TriangleCell>(renderer, orientation));
      } else {
        std::cerr << "Caractère inconnu: " << c << std::endl;
        gridRow.push_back(new Empty<TriangleCell>());
      }
    }
    grid_.push_back(gridRow);
  }
}
