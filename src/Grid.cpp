#include "Grid.h"

#include "Brick.h"
#include "Empty.h"
#include "PlusieursBrick.h"
// #include "Wall.h"

Grid::Grid(const std::string& filename, int width, int height,
           SDL_Renderer* renderer)
    : width_(width), height_(height), renderer_(renderer), remainingBricks_(0) {
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

  for (const auto& row : board) {
    std::vector<Cell*> gridRow;
    for (char c : row) {
      if (c == ' ') {
        gridRow.push_back(new Empty(renderer));
      } else if (c >= '1' && c <= '5') {
        gridRow.push_back(new BasicBrick(c - '0'));
        remainingBricks_++;
      } else {
        std::cerr << "Caractère inconnu: " << c << std::endl;
        gridRow.push_back(new Empty(renderer));
      }
    }
    grid_.push_back(gridRow);
  }
}

Grid::~Grid() {
  for (auto& row : grid_) {
    for (auto& cell : row) {
      delete cell;
    }
  }
}

void Grid::renderGrid(SDL_Renderer* renderer, int screenWidth,
                      int screenHeight) const {
  int cellWidth = screenWidth / cols_;    // Largeur de chaque cellule
  int cellHeight = screenHeight / rows_;  // Hauteur de chaque cellule

  int cellSize = std::min(cellWidth, cellHeight);  // carré

  for (size_t i = 0; i < grid_.size(); ++i) {
    for (size_t j = 0; j < grid_[i].size(); ++j) {
      // Coordonnées de rendu de la cellule actuelle
      int x = j * cellSize;
      int y = i * cellSize;

      // Rendu de la cellule
      grid_[i][j]->renderCell(renderer, x, y, cellSize);
    }
  }
}

Cell* Grid::getCell(int row, int col) const {
  if (row < 0 || row >= rows_ || col < 0 || col >= cols_) {
    return nullptr;
  }
  return grid_[row][col];
}

void Grid::hitCell(int x, int y) {
  Cell* c = getCell(x, y);
  bool detruit = c->hit();
  if (detruit) {
    delete grid_[x][y];
    grid_[x][y] = new Empty(renderer_);
    remainingBricks_--;
  }
}
