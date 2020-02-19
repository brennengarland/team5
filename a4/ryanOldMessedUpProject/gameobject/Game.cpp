
#include "Game.hpp"
#include <iostream>
#include "SDL2/SDL_image.h"
#include "Tank.hpp"
#include "Chopper.hpp"
#include "Pacman.hpp"
#include "Tank.cpp"
#include "Chopper.cpp"
#include "Pacman.cpp"


SDL_Renderer* Game::renderer{};
SDL_Window* Game::window{};

GameObject* tank{};
GameObject* chopper{};
GameObject* pacman{};

Game::Game(const char* title, int xpos, int ypos, int width, int height, bool fullscreen)
{
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

   for(auto & object : game_objects) {
      object.reset();
   }

   std::cout << "Game cleaned..." << std::endl;
}

void Game::load_level()
{
   Tank* newTank = new Tank(0.0f, 0.0f, 0.5f, 0.5f);
   //game_objects.push_back(std::make_unique<Tank>( 0.0f, 0.0f, 0.5f, 0.5f));
   //game_objects.push_back(std::make_unique<Chopper>( 50.0f, 50.0f, 0.5f, 0.5f));
   //game_objects.push_back(std::make_unique<Pacman>( 100.0f, 100.0f, 0.5f, 0.5f));
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

void Game::update(const float dt)
{
   for(auto & object : game_objects) {
      object->update(dt);
   }
}

void Game::render()
{
   SDL_RenderClear(renderer);
   for(auto & object : game_objects) {
      object->render();
   }
   SDL_RenderPresent(renderer);
}

