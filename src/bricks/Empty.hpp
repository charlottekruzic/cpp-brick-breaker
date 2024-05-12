template <typename Shape>
Empty<Shape>::Empty() : Cell<Shape>(Color::Black) {}

template <typename Shape>
Empty<Shape>::Empty(Color color) : Cell<Shape>(color) {}

template <typename Shape>
Empty<Shape>::Empty(TriangleCell::Orientation orientation)
    : Cell<Shape>(Color::Black) {
  this->shape_ = TriangleCell(orientation);
}

template <typename Shape>
Empty<Shape>::~Empty() {}

template <typename Shape>
void Empty<Shape>::renderCell(std::shared_ptr<SDL_Renderer>& renderer, int x,
                              int y, int cellWidth, int cellHeight) {
  this->shape_.draw(renderer, x, y, cellWidth, cellHeight,
                    ColorUtils::convertColor(getColor()));
}