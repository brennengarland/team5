
#include "Game.hpp"

#include <iostream>
#include <memory>
#include <chrono>
#include <thread>

int main() {

   std::cout << "Creating game" << std::endl;
   auto game = std::make_unique<Game>("1st Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, false);

   std::cout << "Starting game loop" << std::endl;

   // 60 frames per second = 16666666 ns for each frame
   auto frame_rate = std::chrono::nanoseconds(16666666);

   while (game->running()) {
      // returns our beginning timepoint to compare against
      auto t0 = std::chrono::high_resolution_clock::now();

      game->handle_events();
      game->update();
      game->render();
   
      auto t1 = std::chrono::high_resolution_clock::now();
      auto elapsed_time = t1 - t0;
      // Frame_rate - elapsed time will give us how much time is left to sleep 
      auto sleep_time = frame_rate - elapsed_time;
      // Sleep for however much time is left 
      std::this_thread::sleep_for(std::chrono::duration_cast<std::chrono::seconds>(sleep_time));

      // Output to verify our frame rate
      // std::cout << "Loop Time: " << std::chrono::duration_cast<std::chrono::microseconds>(duration).count() << "\n";
      // std::cout << "Sleep time: " << std::chrono::duration_cast<std::chrono::microseconds>(sleep_time).count() << "\n";
      // std::cout << "Total execution time: " << std::chrono::duration_cast<std::chrono::microseconds>(duration + sleep_time).count() << "\n\n";
   }

   return 0;
}
