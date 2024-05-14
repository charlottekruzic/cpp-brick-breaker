
// Constructeurs de la classe Brick
template <typename Shape>
Brick<Shape>::Brick(const int strength, Game<Shape>* game)
    : strength_(strength), hitsLeft_(strength), game_(game) {}

template <typename Shape>
Brick<Shape>::Brick(const int strength, Game<Shape>* game,
                    const TriangleCell::Orientation orientation)
    : strength_(strength),
      hitsLeft_(strength),
      game_(game),
      orientation_(orientation),
      shape_(orientation) {}

// Savoir si un objet rebondit sur la brique
template <typename Shape>
bool Brick<Shape>::rebondir() const {
  return (hitsLeft_ > 0);  // Les objets rebondissent sur une brique
}

// Action quand la brique est touchée
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

// Afficher la brique
template <typename Shape>
void Brick<Shape>::renderCell(std::shared_ptr<SDL_Renderer>& renderer,
                              const int x, const int y, const float cellWidth,
                              const float cellHeight) {
  this->shape_.draw(renderer, x, y, cellWidth, cellHeight,
                    ColorUtils::convertColor(getColor()));
}

// Obtenir la couleur de la brique
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
