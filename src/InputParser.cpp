#include "InputParser.h"

#include <fstream>
#include <iostream>

InputParser::InputParser(const std::string& filename) : filename_(filename) {}

bool InputParser::parseFile() {
  std::ifstream file(filename_);
  if (!file.is_open()) {
    std::cerr << "Impossible d'ouvrir le fichier: " << filename_ << std::endl;
    return false;
  }

  // Lire le nombre de lignes et de colonnes
  file >> rows_ >> cols_;
  file.ignore();  // Ignorer le caractère de fin de ligne

  // Lire le plateau de jeu
  for (int i = 0; i < rows_; ++i) {
    std::string line;
    std::getline(file, line);
    if (line.length() != static_cast<size_t>(cols_)) {
      std::cerr << "Invalid input: incorrect number of characters in line "
                << (i + 1) << " : " << line.length() << "," << cols_
                << std::endl;
      return false;
    }
    board_.push_back(line);
  }

  file.close();
  std::cout << "cols = " << cols_;
  return true;
}

int InputParser::getRows() const { return rows_; }

int InputParser::getCols() const { return cols_; }

const std::vector<std::string>& InputParser::getBoard() const { return board_; }
