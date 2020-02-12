
#include "Game.hpp"
#include <iostream>
#include <stdexcept>

Game::Game(const char* title, int xpos, int ypos, int width, int height, bool fullscreen)
{
   Uint32 flags{};
   if (fullscreen) {
      flags = SDL_WINDOW_FULLSCREEN;
   }
   
   //uncomment the following to test
   //SDL_DestroyRenderer(renderer);
   //SDL_DestroyWindow(window);
   //SDL_Quit();
   //throw std::runtime_error("Constructor Failed");

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
      if(SDL_WasInit(SDL_INIT_TIMER) !=0)
      {
        SDL_QuitSubSystem(SDL_INIT_TIMER !=0);
      } 
      if(SDL_WasInit(SDL_INIT_TIMER)!=0)
      { 
        SDL_QuitSubSystem(SDL_INIT_AUDIO);
      }
      if(SDL_WasInit(SDL_INIT_VIDEO)!=0)
      {
        SDL_QuitSubSystem(SDL_INIT_VIDEO);
      }
      if(SDL_WasInit(SDL_INIT_JOYSTICK)!=0)
      {
        SDL_QuitSubSystem(SDL_INIT_JOYSTICK);
      }
      SDL_DestroyRenderer(renderer);
	  SDL_DestroyWindow(window);
      SDL_Quit();
      throw std::runtime_error("Constructor Failed");
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
   counter++;
   std::cout << counter << std::endl;
}

void Game::render()
{
   SDL_RenderClear(renderer);
   // this is where we would add stuff to render
   SDL_RenderPresent(renderer);
}

