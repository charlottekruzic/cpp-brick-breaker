#include "InputParser.h"

#include <fstream>
#include <iostream>

InputParser::InputParser(const std::string& filename) : filename_(filename) {}

bool InputParser::parseFile() {
  std::ifstream file(filename_);
  if (!file.is_open()) {
    std::cerr << "Unable to open file: " << filename_ << std::endl;
    return false;
  }

  // Lire le nombre de lignes et de colonnes
  file >> rows_ >> cols_;
  file.ignore();  // Ignorer le caractère de fin de ligne

  // Lire le plateau de jeu
  for (int i = 0; i < rows_ + 1; ++i) {
    std::string line;
    std::getline(file, line);
    if (line.length() != static_cast<size_t>(cols_)) {
      std::cerr << "Invalid input: incorrect number of characters in row "
                << (i + 1) << std::endl;
      return false;
    }
    board_.push_back(line);
  }

  for (const std::string& row : board_) {
    std::cout << row << std::endl;
  }

  file.close();
  return true;
}

int InputParser::getRows() const { return rows_; }

int InputParser::getCols() const { return cols_; }

const std::vector<std::string>& InputParser::getBoard() const { return board_; }
