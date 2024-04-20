#include "Grid.h"

#include "BasicBrick.h"
#include "Brick.h"
#include "Empty.h"
#include "Wall.h"

Grid::Grid(const std::string& filename, SDL_Renderer* renderer) {
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
        gridRow.push_back(new Wall(renderer));
      } else if (c == ' ') {
        gridRow.push_back(new Empty());
      } else if (c == 'B') {
        gridRow.push_back(new BasicBrick(Color::Blue));
      } else if (c == 'G') {
        gridRow.push_back(new BasicBrick(Color::Gray));
      } else if (c == 'O') {
        gridRow.push_back(new BasicBrick(Color::Orange));
      } else if (c == 'Y') {
        gridRow.push_back(new BasicBrick(Color::Yellow));
      } else if (c == 'R') {
        gridRow.push_back(new BasicBrick(Color::Red));
      } else if (c == 'V') {
        gridRow.push_back(new BasicBrick(Color::Green));
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
