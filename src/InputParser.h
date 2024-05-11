#ifndef INPUTPARSER_H
#define INPUTPARSER_H

#include <string>
#include <vector>

/**
 * @brief Classe pour parser un fichier d'entrée.
 *
 * Cette classe permet de lire et de parser un fichier d'entrée contenant des
 * informations sur une grille de jeu.
 */
class InputParser {
 public:
  /**
   * @brief Constructeur de la classe InputParser.
   * @param filename Le nom du fichier à parser.
   */
  InputParser(const std::string& filename);

  /**
   * @brief Fonction pour parser le fichier.
   * @return True si le parsing s'est déroulé avec succès, sinon false.
   */
  bool parseFile();

  /**
   * @brief Récupère le nombre de lignes du tableau.
   * @return Le nombre de lignes du tableau.
   */
  inline int getRows() const { return rows_; }
  /**
   * @brief Récupère le nombre de colonnes du tableau.
   * @return Le nombre de colonnes du tableau.
   */
  inline int getCols() const { return cols_; }

  /**
   * @brief Récupère la grille de jeu.
   * @return La grille de jeu sous forme d'un vecteur de chaînes de caractères.
   */
  inline const std::vector<std::string>& getBoard() const { return board_; }

 private:
  std::string filename_;           /**< Nom du fichier à parser. */
  int rows_ = 0;                   /**< Nombre de lignes du tableau. */
  int cols_ = 0;                   /**< Nombre de colonnes du tableau. */
  std::vector<std::string> board_; /**< Tableau de jeu. */
};

#endif /* INPUTPARSER_H */
