
// Constructeurs de la classe Empty
template <typename Shape>
Empty<Shape>::Empty() : Cell<Shape>(Color::Black) {}

template <typename Shape>
Empty<Shape>::Empty(const Color color) : Cell<Shape>(color) {}

template <typename Shape>
Empty<Shape>::Empty(const TriangleCell::Orientation orientation)
    : Cell<Shape>(Color::Black) {
  this->shape_ = TriangleCell(orientation);
}

// Destructeur de la classe Empty
template <typename Shape>
Empty<Shape>::~Empty() {}

// Afficher la case vide
template <typename Shape>
void Empty<Shape>::renderCell(std::shared_ptr<SDL_Renderer>& renderer,
                              const int x, const int y, const float cellWidth,
                              const float cellHeight) {
  this->shape_.draw(renderer, x, y, cellWidth, cellHeight,
                    ColorUtils::convertColor(getColor()));
}