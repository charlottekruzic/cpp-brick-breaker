#ifndef EMPTY_H
#define EMPTY_H

#include "Cell.h"

// Classe représentant une case vide
class Empty : public Cell {
 public:
  Empty();
  ~Empty();

  bool rebondir() const override;
  bool traverse() const override;
};

#endif  // EMPTY_H
