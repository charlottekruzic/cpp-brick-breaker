#ifndef MALUS_BRICK_H
#define MALUS_BRICK_H

#include "MalusBonusBrick.h"

class MalusBrick : public MalusBonusBrick<MalusBrick> {
 public:
  MalusBrick(Game* game, std::shared_ptr<SDL_Renderer>& renderer);

  // Méthode pour obtenir la texture du malus
  static std::shared_ptr<SDL_Texture>& getTexture() {
    // Implémentation pour obtenir la texture spécifique à MalusBrick
    return malus_texture_;
  }

 private:
  static std::shared_ptr<SDL_Texture>
      malus_texture_;  // Attribut pour la texture du malus
};

#endif  // MALUS_BRICK_H
