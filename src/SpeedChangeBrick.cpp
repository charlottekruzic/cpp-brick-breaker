#include "SpeedChangeBrick.h"

#include <thread>

void SpeedChangeBrick::performAction() {
  std::cout << "perform action speed change" << std::endl;
  // Démarrer l'accélération de la balle
  game_->setBallAccelerating();
}