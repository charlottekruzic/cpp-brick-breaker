template <typename Shape>
Brick<Shape>::Brick(int strength, Game* game)
    : strength_(strength), hitsLeft_(strength), game_(game) {}

template <typename Shape>
Brick<Shape>::Brick(int strength, Game* game,
                    TriangleCell::Orientation orientation)
    : strength_(strength),
      hitsLeft_(strength),
      game_(game),
      Cell<Shape>(orientation) {}

template <typename Shape>
bool Brick<Shape>::rebondir() const {
  return (hitsLeft_ > 0);  // Les objets rebondissent sur une brique
}

template <typename Shape>
bool Brick<Shape>::hit() {
  if (hitsLeft_ > 0) {
    hitsLeft_--;
  }
  if (hitsLeft_ == 0) {
    return true;
  }
  return false;
}

template <typename Shape>
void Brick<Shape>::renderCell(std::shared_ptr<SDL_Renderer>& renderer, int x,
                              int y, int cellWidth, int cellHeight) {
  this->shape_.draw(renderer, x, y, cellWidth, cellHeight,
                    ColorUtils::convertColor(getColor()));
}

template <typename Shape>
Color Brick<Shape>::getColor() const {
  auto it = strengthColorMap_.find(hitsLeft_);
  if (it != strengthColorMap_.end()) {
    return it->second;  // Retourne la couleur associée à la force de la brique
  } else {
    // Gérer le cas où la force n'est pas trouvée dans le dictionnaire
    return Color::DEFAULT_COLOR;
  }
}
