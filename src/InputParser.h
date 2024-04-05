#ifndef INPUTPARSER_H
#define INPUTPARSER_H

#include <string>
#include <vector>

class InputParser {
 public:
  InputParser(const std::string& filename);

  bool parseFile();
  int getRows() const;
  int getCols() const;
  const std::vector<std::string>& getBoard() const;

 private:
  std::string filename_;
  int rows_ = 0;
  int cols_ = 0;
  std::vector<std::string> board_;
};

#endif /* INPUTPARSER_H */
