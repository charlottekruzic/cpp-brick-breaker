#include "SlowedDownBrick.h"

#include <thread>

void SlowedDownBrick::performAction() {
  std::cout << "SLOWED DOWN" << std::endl;
  // Démarrer l'accélération de la balle
  game_->setBallDecelerating();
}