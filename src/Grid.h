#ifndef GRID_H
#define GRID_H

#include <iostream>
#include <string>
#include <vector>

#include "Cell.h"
#include "Game.h"
#include "InputParser.h"
#include "bricks/BasicBrick.h"
#include "bricks/Empty.h"
// #include "bricks/BasicBrick.h"
// #include "bricks/Empty.h"
//  #include "bricks/EnlargeBrick.h"
//  #include "bricks/MalusBrick.h"
//  #include "bricks/ShrinkBrick.h"
//  #include "bricks/SlowedDownBrick.h"
//  #include "bricks/SpedUpBrick.h"
//  #include "bricks/Wall.h"

class Game;

template <typename Shape>
class Grid {
 public:
  Grid(const std::string& filename, int width, int height,
       std::shared_ptr<SDL_Renderer>& renderer, Game* game)
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
      std::vector<Cell<Shape>*> gridRow;
      for (char c : row) {
        if (c == ' ') {
          gridRow.push_back(new Empty<Shape>());
        } else if (c >= '1' && c <= '5') {
          gridRow.push_back(new BasicBrick<Shape>(c - '0', game_));
          remainingBricks_++;
        } /*else if (c == 'A') {
          gridRow.push_back(new SpedUpBrick(game_, renderer));
        } else if (c == 'D') {
          gridRow.push_back(new SlowedDownBrick(game_, renderer));
        } else if (c == 'E') {
          gridRow.push_back(new EnlargeBrick(game_, renderer));
        } else if (c == 'S') {
          gridRow.push_back(new ShrinkBrick(game_, renderer));
        } else if (c == 'W') {
          gridRow.push_back(new Wall(renderer));
        }*/
        else {
          std::cerr << "Caractère inconnu '" << c
                    << "'. Remplacé par une case vide" << std::endl;
          gridRow.push_back(new Empty<Shape>());
        }
      }
      grid_.push_back(gridRow);
    }
  }

  ~Grid() {
    for (auto& row : grid_) {
      for (auto& cell : row) {
        delete cell;
      }
    }
  }

  void renderGrid(std::shared_ptr<SDL_Renderer>& renderer, int screenWidth,
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
        grid_[i][j]->renderCell(renderer, x, y, cellWidth, cellHeight);
      }
    }
  }

  inline int getRows() const { return rows_; }
  inline int getCols() const { return cols_; }
  inline int getCellSize() const {
    return std::min(width_ / getCols(), height_ / getRows());
  }
  Cell<Shape>* getCell(int row, int col) const {
    if (row < 0 || row >= rows_ || col < 0 || col >= cols_) {
      return nullptr;
    }
    return grid_[row][col];
  }

  void hitCell(int x, int y) {
    Cell<Shape>* c = getCell(x, y);
    BasicBrick<Shape>* basicBrick =
        dynamic_cast<BasicBrick<Shape>*>(c);  // Vérifie si c est un BasicBrick

    bool detruit = c->hit();
    if (detruit) {
      delete grid_[x][y];
      grid_[x][y] = new Empty<Shape>();
      if (basicBrick) remainingBricks_--;
    }
  }

  inline bool hasRemainingBricks() const { return remainingBricks_ > 0; }

 private:
  int rows_;
  int cols_;
  int width_;
  int height_;
  Game* game_;
  std::vector<std::vector<Cell<Shape>*>> grid_;
  std::shared_ptr<SDL_Renderer>& renderer_;
  int remainingBricks_;  // Nouvel attribut pour su
};

// Definir que Shape est un SquareCell
// typedef Grid<SquareCell> SquareGrid;

#endif  // GRID_H
