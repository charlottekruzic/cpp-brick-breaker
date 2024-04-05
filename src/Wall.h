#ifndef WALL_H
#define WALL_H

#include "Cell.h"

class Wall : public Cell {
 public:
  Wall();
  ~Wall();

  bool rebondir() const override;
  bool traverse() const override;
};

#endif  // WALL_H
