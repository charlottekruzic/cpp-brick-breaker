#ifndef COLORS_H
#define COLORS_H

#include <SDL2/SDL.h>

// Énumération pour représenter les couleurs
enum class Color {
  Red,
  Green,
  Blue,
  Black,
  White,
  Yellow,
  Orange,
  Purple,
  Cyan,
  Magenta,
  Gray,
  DarkRed,
  DarkGreen,
  DarkBlue,
  LightGray,
  Brown,
  DEFAULT_COLOR,
  // Ajoutez d'autres couleurs selon vos besoins
};

class ColorUtils {
 public:
  static SDL_Color convertColor(Color color) {
    switch (color) {
      case Color::Red:
        return {255, 0, 0, 255};
      case Color::Green:
        return {0, 255, 0, 255};
      case Color::Blue:
        return {0, 0, 255, 255};
      case Color::White:
        return {255, 255, 255, 255};
      case Color::Black:
        return {0, 0, 0, 255};
      case Color::Yellow:
        return {255, 255, 0, 255};
      case Color::Orange:
        return {255, 165, 0, 255};
      case Color::Purple:
        return {128, 0, 128, 255};
      case Color::Cyan:
        return {0, 255, 255, 255};
      case Color::Magenta:
        return {255, 0, 255, 255};
      case Color::Gray:
        return {128, 128, 128, 255};
      case Color::DarkRed:
        return {139, 0, 0, 255};
      case Color::DarkGreen:
        return {0, 100, 0, 255};
      case Color::DarkBlue:
        return {0, 0, 139, 255};
      case Color::Brown:  // Ajout de la couleur Brown
        return {165, 42, 42, 255};
      case Color::LightGray:
      case Color::DEFAULT_COLOR:
        return {211, 211, 211, 255};
      // Ajoutez d'autres couleurs selon vos besoins
      default:
        return {255, 255, 255, 255};  // Par défaut, renvoie blanc
    }
  }
};

#endif  // COLORS_H
