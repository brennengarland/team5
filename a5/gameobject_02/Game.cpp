
#include "Game.hpp"

#include <iostream>
#include "SDL2/SDL_image.h"

#include "sdl_utils.hpp"
#include "gameobjects/Chopper.hpp"
#include "gameobjects/Tank.hpp"
#include "gameobjects/Pacman.hpp"

sol::state Game::luaInterpreterState;
SDL_Renderer* Game::renderer{};
SDL_Window* Game::window{};

Game::Game(const char* title, int xpos, int ypos, int width, int height, bool fullscreen)
{
   //added error checking from previous assignment as well


   //initilize lua. Must be done here rather than in update so that it is not reinitialized on each update
   luaInterpreterState.script_file("config.lua");
   void Throw_Lua_Exception() {
	   throw std::runtime_error("Lua Error, please check config.lua for syntax errors");
   }
   luaInterpreterState.set_function("Throw_Exception", &Throw_Lua_Exception);
   std::cout << "Lua Config File Loaded..." << std::endl;


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
      else{//if window wasn't created, destroy, quit, and throw exception... destroying all items just to be sure
         is_running = false;
         SDL_Quit();
         throw std::runtime_error("Window Constructor Failed");
      }
      renderer = SDL_CreateRenderer(window, -1, 0);
      if (renderer) {
         SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
         std::cout << "Renderer created..." << std::endl;
      }
      else{//if renderer wasn't created, destroy, quit, and throw exception... destroying all items just to be sure
         is_running = false;
	      SDL_DestroyWindow(window);
         SDL_Quit();
         throw std::runtime_error("Renderer Constructor Failed");
      }
   
   is_running = true;
   } else {//if SDL wasn't initialized, destroy, quit, and throw exception... destroying all items just to be sure
      is_running = false;
      SDL_Quit();
      throw std::runtime_error("SDL Initializaion Failed");
   }
}

Game::~Game()
{
   SDL_DestroyRenderer(renderer);
   SDL_DestroyWindow(window);
   SDL_Quit();
   std::cout << "Game cleaned..." << std::endl;

}

void Game::load_level()
{
   // auto chopper = std::make_unique<Chopper>(50.0f, 50.0f, 0.5f, 0.5f);
   // auto tank = std::make_unique<Tank>(0.0f, 0.0f, 0.5f, 0.5f);
   // auto pacman = std::make_unique<Pacman>(100.0f, 100.0f, 0.5f, 0.5f);
   //iterate of game_objs
   auto luagameobjs = luaInterpreterState["gameobjs"];
   
   
   //check to see if config file was loaded correctly
   if(!luagameobjs.valid()){
         is_running = false;
         SDL_Quit();
         throw std::runtime_error("Loading of Lua Config File Failed");
   }
   for( auto& newObject : game_objs ){
      if(newObject["kind"] == "chopper")
         game_objs.emplace_back(std::move(std::make_unique<Chopper>(newObject["xpos"], newObject["ypos"], newObject["xvel"], newObject["yvel"])));
      else if(newObject["kind"] == "tank")
         game_objs.emplace_back(std::move(std::make_unique<Tank>(newObject["xpos"], newObject["ypos"], newObject["xvel"], newObject["yvel"])));
      else if(newObject["kind"] == "pacman")
         game_objs.emplace_back(std::move(std::make_unique<Pacman>(newObject["xpos"], newObject["ypos"], newObject["xvel"], newObject["yvel"])));
      else {//one item failed to load correctly
         throw std::runtime_error("Failed to load an item from the config file");
      }
   }
      
   //throw exception
   // game_objs.emplace_back(std::move(chopper));
   // game_objs.emplace_back(std::move(tank));
   // game_objs.emplace_back(std::move(pacman));
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
   for (auto& i: game_objs) {
      i->update(dt);
   }
}

void Game::render()
{
   SDL_RenderClear(renderer);
   for (auto& i: game_objs) {
      i->render();
   }
   SDL_RenderPresent(renderer);
}

