#ifndef GRID_H
#define GRID_H

#include <iostream>
#include <string>
#include <vector>

#include "Cell.h"
#include "InputParser.h"
#include "bricks/BasicBrick.h"
#include "bricks/Empty.h"
#include "bricks/Wall.h"

template <typename Shape>
class Game;

/**
 * @brief Classe représentant une grille de jeu
 * @tparam Shape Type de cellule de la grille
 */
template <typename Shape>
class Grid {
 public:
  /**
   * @brief Constructeur de la classe Grid.
   * @param filename Nom du fichier contenant la grille de jeu.
   * @param width Largeur de la fenêtre de jeu.
   * @param height Hauteur de la fenêtre de jeu.
   * @param renderer Renderer de la fenêtre de jeu.
   * @param game Game associé à la grille.
   */
  Grid(const std::string& filename, const int width, const int height,
       std::shared_ptr<SDL_Renderer>& renderer, Game<Shape>* game);

  /**
   * @brief Destructeur de la classe Grid.
   * Libère la mémoire allouée pour les cellules de la grille.
   */
  ~Grid();

  /**
   * @brief Fonction pour afficher la grille de jeu.
   * @param renderer Renderer de la fenêtre de jeu.
   * @param screenWidth Largeur de la fenêtre de jeu.
   * @param screenHeight Hauteur de la fenêtre de jeu.
   */
  void renderGrid(std::shared_ptr<SDL_Renderer>& renderer,
                  const int screenWidth, const int screenHeight) const;

  /**
   * @brief Fonction pour récupérer le nombre de lignes de la grille.
   * @return Le nombre de lignes de la grille.
   */
  inline int getRows() const { return rows_; }

  /**
   * @brief Fonction pour récupérer le nombre de colonnes de la grille.
   * @return Le nombre de colonnes de la grille.
   */
  inline int getCols() const { return cols_; }

  /**
   * @brief Fonction pour récupérer la taille d'une cellule de la grille.
   * @return La taille d'une cellule de la grille.
   * La taille est déterminée par la taille de la fenêtre de jeu et le nombre de
   * lignes et de colonnes de la grille.
   */
  inline int getCellSize() const {
    return std::min(width_ / getCols(), height_ / getRows());
  }

  /**
   * @brief Fonction pour récupérer une cellule de la grille.
   * @param row Ligne de la cellule.
   * @param col Colonne de la cellule.
   * @return La cellule de la grille à la position (row, col).
   */
  std::shared_ptr<Cell<Shape>>& getCell(const int row, const int col);

  // TODO : Zoé
  void hitCell(const int x, const int y);

  /**
   * @brief Fonction pour vérifier s'il reste des briques à casser.
   * @return true s'il reste des briques à casser, false sinon.
   * @note Utilisé pour déterminer si le joueur a gagné ou perdu.
   */
  inline bool hasRemainingBricks() const { return remainingBricks_ > 0; }

 private:
  int rows_;          /**< Nombre de lignes de la grille. */
  int cols_;          /**< Nombre de colonnes de la grille. */
  int width_;         /**< Largeur de la fenêtre de jeu. */
  int height_;        /**< Hauteur de la fenêtre de jeu. */
  Game<Shape>* game_; /**< Game associé à la grille. */
  std::vector<std::vector<std::shared_ptr<Cell<Shape>>>>
      grid_; /**< Grille de jeu. */
  std::shared_ptr<SDL_Renderer>&
      renderer_;        /**< Renderer de la fenêtre de jeu. */
  int remainingBricks_; /**< Nombre de briques restantes à casser. */
};

#include "Grid.hpp"

#endif  // GRID_H
