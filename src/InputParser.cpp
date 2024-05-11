#include "InputParser.h"

#include <fstream>
#include <iostream>

InputParser::InputParser(const std::string& filename) : filename_(filename) {}

bool InputParser::parseFile() {
  std::ifstream file(filename_);
  if (!file.is_open()) {
    std::cerr << "Impossible d'ouvrir le fichier: " << filename_ << std::endl;
    // erreur gérée dans Grid.h
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
      std::cerr
          << "Entrée invalide : nombre incorrect de caractères dans la ligne "
          << (i + 2) << " : longueur de la ligne : " << line.length()
          << ", nombre de caractères attendu : " << cols_ << std::endl;
      return false;
    }
    board_.push_back(line);
  }

  file.close();
  return true;
}