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

#include "HexagonCell.h"
#include "SquareCell.h"
#include "TriangleCell.h"

template <>
Grid<SquareCell>::Grid(const std::string& filename, int width, int height,
                       std::shared_ptr<SDL_Renderer>& renderer,
                       std::shared_ptr<Game<SquareCell>> game)
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
        auto sharedGame = game_.lock();
        if (sharedGame) {
          gridRow.push_back(new BasicBrick<SquareCell>(c - '0', sharedGame));
        }
        remainingBricks_++;
      } else if (c == 'A') {
        auto sharedGame = game_.lock();
        if (sharedGame) {
          gridRow.push_back(new SpedUpBrick<SquareCell>(sharedGame, renderer));
        }
      } else if (c == 'D') {
        auto sharedGame = game_.lock();
        if (sharedGame) {
          gridRow.push_back(
              new SlowedDownBrick<SquareCell>(sharedGame, renderer));
        }
      } else if (c == 'S') {
        auto sharedGame = game_.lock();
        if (sharedGame) {
          gridRow.push_back(new ShrinkBrick<SquareCell>(sharedGame, renderer));
        }
      } else if (c == 'E') {
        auto sharedGame = game_.lock();
        if (sharedGame) {
          gridRow.push_back(new EnlargeBrick<SquareCell>(sharedGame, renderer));
        }
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
                         std::shared_ptr<Game<TriangleCell>> game)
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
        auto sharedGame = game_.lock();
        if (sharedGame) {
          gridRow.push_back(
              new BasicBrick<TriangleCell>(c - '0', sharedGame, orientation));
        }
        remainingBricks_++;
      } else if (c == 'A') {
        auto sharedGame = game_.lock();
        if (sharedGame) {
          gridRow.push_back(
              new SpedUpBrick<TriangleCell>(sharedGame, renderer, orientation));
        }
      } else if (c == 'D') {
        auto sharedGame = game_.lock();
        if (sharedGame) {
          gridRow.push_back(new SlowedDownBrick<TriangleCell>(
              sharedGame, renderer, orientation));
        }
      } else if (c == 'S') {
        auto sharedGame = game_.lock();
        if (sharedGame) {
          gridRow.push_back(
              new ShrinkBrick<TriangleCell>(sharedGame, renderer, orientation));
        }
      } else if (c == 'E') {
        auto sharedGame = game_.lock();
        if (sharedGame) {
          gridRow.push_back(new EnlargeBrick<TriangleCell>(sharedGame, renderer,
                                                           orientation));
        }
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

// TODO
template <>
Grid<HexagonCell>::Grid(const std::string& filename, int width, int height,
                        std::shared_ptr<SDL_Renderer>& renderer,
                        std::shared_ptr<Game<HexagonCell>> game)
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
    std::vector<Cell<HexagonCell>*> gridRow;
    for (char c : row) {
      if (c == ' ') {
        gridRow.push_back(new Empty<HexagonCell>());
      } else if (c >= '1' && c <= '5') {
        auto sharedGame = game_.lock();
        if (sharedGame) {
          gridRow.push_back(new BasicBrick<HexagonCell>(c - '0', sharedGame));
        }
        remainingBricks_++;
      } else if (c == 'A') {
        auto sharedGame = game_.lock();
        if (sharedGame) {
          gridRow.push_back(new SpedUpBrick<HexagonCell>(sharedGame, renderer));
        }
      } else if (c == 'D') {
        auto sharedGame = game_.lock();
        if (sharedGame) {
          gridRow.push_back(
              new SlowedDownBrick<HexagonCell>(sharedGame, renderer));
        }
      } else if (c == 'S') {
        auto sharedGame = game_.lock();
        if (sharedGame) {
          gridRow.push_back(new ShrinkBrick<HexagonCell>(sharedGame, renderer));
        }
      } else if (c == 'E') {
        auto sharedGame = game_.lock();
        if (sharedGame) {
          gridRow.push_back(
              new EnlargeBrick<HexagonCell>(sharedGame, renderer));
        }
      } else if (c == 'W') {
        gridRow.push_back(new Wall<HexagonCell>(renderer));
      } else {
        std::cerr << "Caractère inconnu '" << c
                  << "'. Remplacé par une case vide" << std::endl;
        gridRow.push_back(new Empty<HexagonCell>());
      }
    }
    grid_.push_back(gridRow);
  }
}

template <>
void Grid<SquareCell>::renderGrid(std::shared_ptr<SDL_Renderer>& renderer,
                                  int screenWidth, int screenHeight) const {
  float cellWidth = screenWidth / cols_;    // Largeur de chaque cellule
  float cellHeight = screenHeight / rows_;  // Hauteur de chaque cellule

  int cellSize = std::min(cellWidth, cellHeight);  // carré

  for (size_t i = 0; i < grid_.size(); ++i) {
    for (size_t j = 0; j < grid_[i].size(); ++j) {
      // Coordonnées de rendu de la cellule actuelle
      int x = j * cellSize;
      int y = i * cellSize;

      // Rendu de la cellule
      grid_[i][j]->renderCell(renderer, x, y, cellWidth, cellHeight);
    }
  }
}

template <>
void Grid<TriangleCell>::renderGrid(std::shared_ptr<SDL_Renderer>& renderer,
                                    int screenWidth, int screenHeight) const {
  float cellWidth = (screenWidth / (cols_ + 1)) * 2.0;
  float cellHeight = ((screenWidth / (cols_)) * std::sqrt(3));

  for (size_t i = 0; i < grid_.size(); ++i) {
    for (size_t j = 0; j < grid_[i].size(); ++j) {
      int x = j * cellWidth;
      int y = i * cellHeight;

      // Décalage horizontal
      if (x != 0) {
        x = j * cellWidth / 2;
        y = i * cellHeight;
      }
      // Rendu de la cellule
      grid_[i][j]->renderCell(renderer, x, y, cellWidth, cellHeight);
    }
  }
}

template <>
void Grid<HexagonCell>::renderGrid(std::shared_ptr<SDL_Renderer>& renderer,
                                   int screenWidth, int screenHeight) const {
  float cellWidth = screenWidth / (cols_ + 3);
  float cellHeight = cellWidth * (std::sqrt(3) / 2);

  for (size_t i = 0; i < grid_.size(); ++i) {
    for (size_t j = 0; j < grid_[i].size(); ++j) {
      float x = cellWidth + j * cellWidth * (sqrt(3) * 0.75);
      float y = cellHeight * (sqrt(3) / 2) + i * cellHeight * 1.75;

      // Décalage vertical
      if (j % 2 != 0) {
        y += cellHeight * sqrt(3) / 2;
      }

      // Appel de la fonction de rendu de la cellule
      grid_[i][j]->renderCell(renderer, x, y, cellWidth, cellHeight);
    }
  }
}
