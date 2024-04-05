#include "Grid.h"

#include "Brick.h"
#include "Empty.h"
#include "Wall.h"

Grid::Grid(const std::string& filename) {
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
      if (c == '#') {
        gridRow.push_back(new Wall());
      } else if (c == ' ') {
        gridRow.push_back(new Empty());
      } else if (c == 'B') {
        gridRow.push_back(new Brick(1, Color::Red));
      } else {
        // Gérer les caractères inconnus ou non pris en charge
        std::cerr << "Caractère inconnu: " << c << std::endl;
        gridRow.push_back(new Empty());
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

/*
void Grid::renderGrid(SDL_Renderer* renderer) const {
  // std::cout << "renderGrid" << std::endl;
  int cellSize = 100;  // Taille de chaque case
  int i = 0;
  for (const auto& row : grid_) {
    int j = 0;
    for (const auto& cell : row) {
      cell->renderCell(renderer, j, i, cellSize);
      ++j;
    }
    ++i;
  }
}*/

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
