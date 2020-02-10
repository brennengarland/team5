
#include "Game.hpp"

#include <iostream>
#include <memory>

int main() {

   std::cout << "Creating game" << std::endl;
   auto game = std::make_unique<Game>("1st Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, false);

   std::cout << "Starting game loop" << std::endl;
   while (game->running()) {
      game->handle_events();
      game->update();
      game->render();
   }

   return 0;
}

