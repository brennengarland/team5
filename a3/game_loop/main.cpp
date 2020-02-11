
#include "Game.hpp"

#include <iostream>
#include <memory>
#include <chrono>
#include <thread>

int main() {

   std::cout << "Creating game" << std::endl;
   auto game = std::make_unique<Game>("1st Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, false);

   std::cout << "Starting game loop" << std::endl;
   auto frame_rate = std::chrono::microseconds(16667);
   while (game->running()) {
      // 60 frames per second = 16.7ms for each frame
      auto t0 = std::chrono::high_resolution_clock::now();

      game->handle_events();
      game->update();
      game->render();

      auto t1 = std::chrono::high_resolution_clock::now();
      auto duration = t1 - t0;
      auto sleep_time = std::chrono::duration_cast<std::chrono::seconds>(frame_rate - duration);
      std::this_thread::sleep_for(sleep_time);
      std::cout << "Loop Time: " << std::chrono::duration_cast<std::chrono::milliseconds>(t1 - t0).count() << "\n";
      std::cout << "Sleep time: " << sleep_time.count() << "\n\n";
   }

   return 0;
}
