
#include "Game.hpp"

#include <iostream>
#include <memory>
#include <chrono>
#include <thread>
#include <stdexcept>

int main() {

   std::cout << "Creating game" << std::endl;
   std::unique_ptr<Game> game;
   try
   {
		game = std::make_unique<Game>("1st Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, false);
   }
   catch(std::runtime_error x)
   {
	   std::cout<<"ERROR OCCURED: " << x.what() << "\n";
	   exit(0);
   }
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
      //Sleep in main(), pdf said to slow main()
      auto sleep_time = frame_rate - elapsed_time;
      // Sleep for however much time is left 
      std::this_thread::sleep_for(std::chrono::duration_cast<std::chrono::seconds>(sleep_time));

      //Output to verify our frame rate
      std::cout << "Loop Time: " << std::chrono::duration_cast<std::chrono::microseconds>(elapsed_time).count() << "\n";
      std::cout << "Sleep time: " << std::chrono::duration_cast<std::chrono::microseconds>(sleep_time).count() << "\n";
      std::cout << "Total execution time: " << std::chrono::duration_cast<std::chrono::microseconds>(elapsed_time + sleep_time).count() << "\n\n";
      std::cout << "Total execution time in Hertz: " << (elapsed_time + sleep_time).count()/1000.0 << "\n\n";

   }

   return 0;
}
