
#include "Game.hpp"
#include <iostream>

Game::Game(const char* title, int xpos, int ypos, int width, int height, bool fullscreen)
{
   //initilize lua. Must be done here rather than in update so that it is not reinitialized on each update
   lua.script_file("logic.lua");
	

   Uint32 flags{};
   if (fullscreen) {
      flags = SDL_WINDOW_FULLSCREEN;
   }

   if (SDL_Init(SDL_INIT_EVERYTHING) == 0) {
      std::cout << "Subsystems initialized..." << std::endl;
      window = SDL_CreateWindow(title, xpos, ypos, width, height, flags);
      if (window) {
         std::cout << "Window created..." << std::endl;
      }
      renderer = SDL_CreateRenderer(window, -1, 0);
      if (renderer) {
         SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
         std::cout << "Renderer created..." << std::endl;
      }
   is_running = true;
   } else {
      is_running = false;
   }
}

Game::~Game()
{
   SDL_DestroyRenderer(renderer);
   SDL_DestroyWindow(window);
   SDL_Quit();
   std::cout << "Game cleaned..." << std::endl;
}

void Game::handle_events()
{
   SDL_Event event;
   SDL_PollEvent(&event);
   switch (event.type) {
      case SDL_QUIT:
         is_running = false;
         break;
      default:
         break;
   }
}

void Game::update()
{
	//this line instantiates updateLua as a reference to the function "update" in the file logic.lua
   sol::function updateLua = lua["update"];
   //this line indirectly calls the function update inside of logic.lua. This function increments a counter variable.
   //after incrementing this variable, the function returns the value of the variable. In this line, that returned value
   //is stored in incrementor
	int incrementor = updateLua();
   std::cout << incrementor << "\n";
}

void Game::render()
{
   SDL_RenderClear(renderer);
   // this is where we would add stuff to render
   SDL_RenderPresent(renderer);
}

