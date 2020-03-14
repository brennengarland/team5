
#include "Game.hpp"

#include <iostream>
#include "SDL2/SDL_image.h"

#include "sdl_utils.hpp"
#include "gameobjects/Chopper.hpp"
#include "gameobjects/Tank.hpp"
#include "gameobjects/Pacman.hpp"

//lua state
sol::state Game::luaInterpreterState;

SDL_Renderer* Game::renderer{};
SDL_Window* Game::window{};

//lua exception thrower, specifically for loading script in initially
void Throw_Lua_Exception() {
	   throw std::runtime_error("Lua Error, please check config.lua for syntax errors");
   }

Game::Game(const char* title, int xpos, int ypos, int width, int height, bool fullscreen)
{
   //added error checking from previous assignment as well
   //open libraries
   try{
      luaInterpreterState.open_libraries(sol::lib::base, sol::lib::package, sol::lib::string, sol::lib::math, sol::lib::io);
   }
	catch( const sol::error& e ) {
      std::string outError = std::string("failed to load lua libraries") + std::string(e.what()) + std::string("\n");

      throw std::runtime_error(outError);

	}

   //load config file
   try {
		luaInterpreterState.script_file("config.lua");
	}
	catch( const sol::error& e ) {
      std::string outError = std::string("failed to load lua config file") + std::string(e.what()) + std::string("\n");
      throw std::runtime_error(outError);

	}

   //***Was initializing counter here to iterate, but we switched to a different iterating method for load_level()***

   //set a function to throw an exception if lua errors happen
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

   //check to see if table can be loaded from config file
   if(!luaInterpreterState["gameobjs"].valid()){
         throw std::runtime_error("Loading of gameobjs in Lua Config File Failed");
   }
   sol::table luagameobjs = luaInterpreterState["gameobjs"];

   //iterate over table
   for(const auto& table : luagameobjs){

      //get values and check for misloads
      std::string kind = "";
      float xposIn = 0;
      float yposIn = 0;
      float xvelIn = 0;
      float yvelIn = 0;
      if(!table.second.valid()){
         throw std::runtime_error("Failed to load a row in the gameobjs table");
      }
      sol::table row = table.second;

      //CHANGED to slide deck 11 page 15 iterating method
      //kind
      if(!row["kind"].valid()){
         throw std::runtime_error("Failed to load kind in an item");
      }
      kind = row["kind"];

      //xpos
      if(!row["xpos"].valid()){
         throw std::runtime_error("Failed to load xpos in an item");
      }      
      xposIn = row["xpos"];

      //ypos
      if(!row["ypos"].valid()){
         throw std::runtime_error("Failed to load ypos in an item");
      }
      yposIn = row["ypos"];

      //xvel
      if(!row["xvel"].valid()){
         throw std::runtime_error("Failed to load xvel in an item");
      }
      xvelIn = row["xvel"];

      //yvel
      if(!row["yvel"].valid()){
         throw std::runtime_error("Failed to load yvel in an item");
      }
      yvelIn = row["yvel"];
      

      //create game objects
      if(kind == "chopper")
         game_objs.emplace_back(std::move(std::make_unique<Chopper>(xposIn, yposIn, xvelIn, yvelIn)));
      else if(kind == "tank")
         game_objs.emplace_back(std::move(std::make_unique<Tank>(xposIn, yposIn, xvelIn, yvelIn)));
      else if(kind == "pacman")
         game_objs.emplace_back(std::move(std::make_unique<Pacman>(xposIn, yposIn, xvelIn, yvelIn)));
      else {
         //one item failed to load correctly because kind wasn't matched
         //won't throw an exception, but will let the user know
         std::cout << "\nOne of the Item's kind did not match Pacman, Chopper, or Tank...Couldn't create item...\n";
      }
   }
      

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

