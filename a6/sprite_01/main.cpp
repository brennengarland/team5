
#include "Game.hpp"

#include <iostream>
#include <memory>

int main() {

   std::cout << "Creating game" << std::endl;
   auto game = std::make_unique<Game>("Sprite Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 640, false);
   game->initialize();

   std::cout << "Starting game loop" << std::endl;
   while (game->running()) {
      game->handle_events();
      game->update(static_cast<float>(0.001));
      game->render();
   }

   return 0;
}

