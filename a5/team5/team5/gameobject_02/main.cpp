
#include "SDL2/SDL.h"

#include "Game.hpp"

#include <iostream>
#include <memory>
#include <cmath>

int main() {

   std::cout << "Creating game" << std::endl;
   std::unique_ptr<Game> game;
   //game initialization try catch error checker
   try{
      game = std::make_unique<Game>("1st Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 640, false);
   }
   catch(std::runtime_error x)
   {
	   std::cout<<"ERROR OCCURED: " << x.what() << "\n";
	   exit(0);
   }   

   //load level try catch error checker
   try{
      game->load_level();
   }
   catch(std::runtime_error x){
      std::cout<<"ERROR OCCURED: " << x.what() << "\n";
	   exit(0);
   }
   
   float fps{30};                     // frame rate (e.g., 30 frames per seconds)
   float delta_time{1.0f/fps};        // in seconds (e.g., 30 Hz => 0.03333)

   std::cout << "Starting game loop" << std::endl;
   while (game->running()) {
      Uint64 start_time = SDL_GetPerformanceCounter();
      game->handle_events();
      game->update(delta_time);
      game->render();
      Uint64 end_time = SDL_GetPerformanceCounter();
      float elapsed_time = (end_time-start_time) / static_cast<float>(SDL_GetPerformanceFrequency() * 1000.0f); // (secs)
      if (elapsed_time < delta_time) {
         SDL_Delay(static_cast<Uint32>(std::floor((delta_time - elapsed_time)/1000.0f)));  // (ms)
      }
   }
   return 0;
}


