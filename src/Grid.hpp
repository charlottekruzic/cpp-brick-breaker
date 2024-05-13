#include <cassert>

#include "Grid.h"
#include "HexagonCell.h"
#include "SquareCell.h"
#include "TriangleCell.h"
#include "bricks/EnlargeBrick.h"
#include "bricks/ShrinkBrick.h"
#include "bricks/SlowedDownBrick.h"
#include "bricks/SpedUpBrick.h"

template <typename Shape>
Grid<Shape>::Grid(const std::string& filename, const int width,
                  const int height, std::shared_ptr<SDL_Renderer>& renderer,
                  Game<Shape>* game)
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
    std::vector<std::shared_ptr<Cell<Shape>>> gridRow;
    for (char c : row) {
      if (c == ' ') {
        gridRow.push_back(std::make_shared<Empty<Shape>>());
      } else if (c >= '1' && c <= '5') {
        gridRow.push_back(std::make_shared<BasicBrick<Shape>>(c - '0', game_));
        remainingBricks_++;
      } else if (c == 'A') {
        gridRow.push_back(
            std::make_shared<SpedUpBrick<Shape>>(game_, renderer));
      } else if (c == 'D') {
        gridRow.push_back(
            std::make_shared<SlowedDownBrick<Shape>>(game_, renderer));
      } else if (c == 'S') {
        gridRow.push_back(
            std::make_shared<ShrinkBrick<Shape>>(game_, renderer));
      } else if (c == 'E') {
        gridRow.push_back(
            std::make_shared<EnlargeBrick<Shape>>(game_, renderer));
      } else if (c == 'W') {
        gridRow.push_back(std::make_shared<Wall<Shape>>(renderer));
      } else {
        std::cerr << "Caractère inconnu '" << c
                  << "'. Remplacé par une case vide" << std::endl;
        gridRow.push_back(std::make_shared<Empty<Shape>>());
      }
    }
    grid_.push_back(std::move(gridRow));
  }
}

template <>
Grid<TriangleCell>::Grid(const std::string& filename, const int width,
                         const int height,
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
    std::vector<std::shared_ptr<Cell<TriangleCell>>> gridRow;
    for (size_t j = 0; j < board[i].size(); j++) {
      char c = board[i][j];
      TriangleCell::Orientation orientation =
          ((i + j) % 2 == 0) ? TriangleCell::Orientation::UP
                             : TriangleCell::Orientation::DOWN;
      if (c == ' ') {
        gridRow.push_back(std::make_shared<Empty<TriangleCell>>(orientation));
      } else if (c >= '1' && c <= '5') {
        gridRow.push_back(std::make_shared<BasicBrick<TriangleCell>>(
            c - '0', game_, orientation));
        remainingBricks_++;
      } else if (c == 'A') {
        gridRow.push_back(std::make_shared<SpedUpBrick<TriangleCell>>(
            game_, renderer, orientation));
      } else if (c == 'D') {
        gridRow.push_back(std::make_shared<SlowedDownBrick<TriangleCell>>(
            game_, renderer, orientation));
      } else if (c == 'S') {
        gridRow.push_back(std::make_shared<ShrinkBrick<TriangleCell>>(
            game_, renderer, orientation));
      } else if (c == 'E') {
        gridRow.push_back(std::make_shared<EnlargeBrick<TriangleCell>>(
            game_, renderer, orientation));
      } else if (c == 'W') {
        gridRow.push_back(
            std::make_shared<Wall<TriangleCell>>(renderer, orientation));
      } else {
        std::cerr << "Caractère inconnu: " << c << std::endl;
        gridRow.push_back(std::make_shared<Empty<TriangleCell>>(orientation));
      }
    }
    grid_.push_back(std::move(gridRow));
  }
}

template <>
void Grid<SquareCell>::renderGrid(std::shared_ptr<SDL_Renderer>& renderer,
                                  const int screenWidth,
                                  const int screenHeight) const {
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
                                    const int screenWidth,
                                    const int screenHeight) const {
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
                                   const int screenWidth,
                                   const int screenHeight) const {
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

template <>
void Grid<TriangleCell>::hitCell(const int x, const int y) {
  auto& cell = getCell(x, y);
  bool detruit = cell->hit();
  if (detruit) {
    TriangleCell::Orientation orientation =
        ((x + y) % 2 == 0) ? TriangleCell::Orientation::UP
                           : TriangleCell::Orientation::DOWN;
    auto basicBrick = std::dynamic_pointer_cast<BasicBrick<TriangleCell>>(cell);
    auto newCell = std::make_shared<Empty<TriangleCell>>(orientation);
    cell = newCell;
    if (basicBrick) remainingBricks_--;
  }
}

template <typename Shape>
void Grid<Shape>::hitCell(const int x, const int y) {
  auto& cell = getCell(x, y);
  bool detruit = cell->hit();
  if (detruit) {
    auto basicBrick = std::dynamic_pointer_cast<BasicBrick<Shape>>(cell);
    auto newCell = std::make_shared<Empty<Shape>>();
    cell = newCell;
    if (basicBrick) remainingBricks_--;
  }
}

template <typename Shape>
std::shared_ptr<Cell<Shape>>& Grid<Shape>::getCell(const int row,
                                                   const int col) {
  assert(row >= 0 && row < rows_ && col >= 0 && col < cols_);
  return grid_[row][col];
}

template <typename Shape>
Grid<Shape>::~Grid() {
  for (auto& row : grid_) {
    for (auto& cell : row) {
      cell.reset();
    }
  }
}