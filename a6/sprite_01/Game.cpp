
#include "Game.hpp"

#include <iostream>
#include "SDL2/SDL_image.h"

#include "AssetManager.hpp"
#include "EntityManager.hpp"
#include "Entity.hpp"
#include "components/TransformComponent.hpp"
#include "components/SpriteComponent.hpp"

SDL_Renderer* Game::renderer{};

EntityManager entity_mgr;
AssetManager* Game::asset_manager{new AssetManager()};
//lua state
sol::state Game::luaInterpreterState;
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

   load_level(1);
}

Game::~Game()
{
   SDL_DestroyRenderer(renderer);
   SDL_DestroyWindow(window);
   SDL_Quit();
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
   entity_mgr.update(dt);
}

void Game::render()
{
   SDL_RenderClear(renderer);
   entity_mgr.render();
   SDL_RenderPresent(renderer);
}

void Game::load_level(const int number)
{
   // // add assets to asset manager
   // asset_manager->add_texture("tank-image", "../assets/images/tank-big-right.png");
   // asset_manager->add_texture("chopper-image", "../assets/images/chopper-spritesheet.png");

   // // create entities and add components to them
   // Entity& tank_entity(entity_mgr.add_entity("tank"));
   // tank_entity.add_component<TransformComponent>(0,0,20,20,32,32,1);
   // tank_entity.add_component<SpriteComponent>("tank-image");

   // Entity& chopper_entity(entity_mgr.add_entity("chopper"));
   // chopper_entity.add_component<TransformComponent>(240, 106, 0, 0, 32, 32, 1);
   // chopper_entity.add_component<SpriteComponent>("chopper-image");

   // entity_mgr.list_all_entities();


   //check to see if assets table can be loaded from config file
   if(!luaInterpreterState["assets"].valid()){
         throw std::runtime_error("Loading of assets in Lua Config File Failed");
   }
   sol::table luaConfigAssets = luaInterpreterState["assets"];

   //iterate over asset table
   for(const auto& table : luaConfigAssets){
      //get values and check for misloads
      std::string assetKey = "";
      std::string assetValue = "";
      //key
      if(!table.first.valid()){
         throw std::runtime_error("Failed to load a key of an asset in the asset table");
      }
      assetKey = table.first;

      //asset value
      if(!table.second.valid()){
         throw std::runtime_error("Failed to load a value of an asset in the asset table");
      }
      assetValue = table.second;

      //add assets
      asset_manager->add_texture(assetKey, assetValue);

   }

   //check to see if entities table can be loaded from config file
   if(!luaInterpreterState["entities"].valid()){
         throw std::runtime_error("Loading of entities in Lua Config File Failed");
   }
   sol::table luaConfigEntities = luaInterpreterState["entities"];

   //iterate over entities table
   for(const auto& table : luaConfigEntities){
      //kind
      std::string entityKind = "";

      //transform
      int position_x = 0;
      int position_y = 0;
      int velocity_x = 0;
      int velocity_y = 0;
      int width = 0;
      int height = 0;
      int scale = 0;

      //sprite
      std::string texture_id = "";

      //get entities kind
      if(!table.first.valid()){
         throw std::runtime_error("Failed to load entity kind");
      }
      entityKind = table.first;
      
      //Second Table Value
      if(!table.second.valid()){
         throw std::runtime_error("Failed to load table value");
      }
      sol::table tableSecond = table.second;


      //TRANSFORM
      if(!tableSecond["transform"].valid()){
         throw std::runtime_error("Failed to load entity transform");
      }
      auto entityTransform = tableSecond["transform"];
      //position_x
      if(!entityTransform["position_x"].valid()){
         throw std::runtime_error("Failed to load entity transform position_x");
      }
      position_x = entityTransform["position_x"];
      //position_y
      if(!entityTransform["position_y"].valid()){
         throw std::runtime_error("Failed to load entity transform position_y");
      }
      position_y = entityTransform["position_y"];
      //velocity_x
      if(!entityTransform["velocity_x"].valid()){
         throw std::runtime_error("Failed to load entity transform velocity_x");
      }
      velocity_x = entityTransform["velocity_x"];
      //velocity_y
      if(!entityTransform["velocity_y"].valid()){
         throw std::runtime_error("Failed to load entity transform velocity_y");
      }
      velocity_y = entityTransform["velocity_y"];
      //width
      if(!entityTransform["width"].valid()){
         throw std::runtime_error("Failed to load entity transform width");
      }
      width = entityTransform["width"];
      //height
      if(!entityTransform["height"].valid()){
         throw std::runtime_error("Failed to load entity transform height");
      }
      height = entityTransform["height"];
      //scale
      if(!entityTransform["scale"].valid()){
         throw std::runtime_error("Failed to load entity transform scale");
      }
      scale = entityTransform["scale"];


      //SPRITE
      if(!tableSecond["sprite"].valid()){
         throw std::runtime_error("Failed to load entity sprite");
      }
      auto entitySprite = tableSecond["sprite"];
      entitySprite = tableSecond["sprite"];
      
      //texture_id
      if(!entitySprite["texture_id"].valid()){
         throw std::runtime_error("Failed to load entity sprite texture_id");
      }
      texture_id = entitySprite["texture_id"];

      // create entities and add components to them
      Entity& tank_entity(entity_mgr.add_entity(entityKind));
      tank_entity.add_component<TransformComponent>(position_x, position_y, velocity_x, velocity_y, width, height, scale);
      tank_entity.add_component<SpriteComponent>(texture_id);

   }
   entity_mgr.list_all_entities();


}

void Game::initialize() {
   entity_mgr.initialize();
}