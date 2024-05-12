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
  BrickLight,        // Couleur 1 : Brique claire
  BrickLightMedium,  // Couleur 2
  BrickMedium,       // Couleur 3
  BrickDarkMedium,   // Couleur 4
  BrickDark,         // Couleur 5 : Brique foncée
  BrickColor,        // Couleur pour représenter les briques : Rouge orangé
  MalusColor,        // Couleur pour représenter les malus : Bleu gris
  BonusColor,        // Couleur pour représenter les bonus : Vert menthe
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
      case Color::Brown:
        return {165, 42, 42, 255};
      case Color::LightGray:
      case Color::DEFAULT_COLOR:
        return {211, 211, 211, 255};
      // Couleurs pour les briques en dégradé
      case Color::BrickLight:
        return {173, 216, 230, 255};  // Couleur 1 : Brique claire
      case Color::BrickLightMedium:
        return {138, 173, 219, 255};  // Couleur 2
      case Color::BrickMedium:
        return {104, 134, 214, 255};  // Couleur 3
      case Color::BrickDarkMedium:
        return {148, 0, 211, 255};  // Couleur 4
      case Color::BrickDark:
        return {75, 0, 130, 255};  // Couleur 5 : Brique foncée
      // Couleurs pour les éléments du jeu
      case Color::BrickColor:
        return {
            139, 69, 19,
            255};  // Couleur pour représenter les murs : Marron orangé foncé
      case Color::MalusColor:
        return {139, 0, 0, 255};  // Couleur pour représenter les malus : Rouge
      // foncé
      case Color::BonusColor:
        return {130, 196, 187,
                255};  // Couleur pour représenter les bonus : Vert menthe
      // Ajoutez d'autres couleurs selon vos besoins
      default:
        return {255, 255, 255, 255};  // Par défaut, renvoie blanc
    }
  }
};

#endif  // COLORS_H
