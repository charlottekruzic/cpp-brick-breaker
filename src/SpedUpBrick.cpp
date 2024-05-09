#include "SpedUpBrick.h"

#include <thread>

void SpedUpBrick::performAction() {
  std::cout << "perform action speed change" << std::endl;
  // Démarrer l'accélération de la balle
  game_->setBallAccelerating();
}