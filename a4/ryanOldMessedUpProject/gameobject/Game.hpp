
#ifndef __GAME_HPP__
#define __GAME_HPP__

#include "SDL2/SDL.h"
#include "GameObject.hpp"
#include <vector>
#include <memory>
#include "Tank.hpp"
#include "Chopper.hpp"
#include "Pacman.hpp"
#include "texture_utils.hpp"

class Game {

public:
   Game(const char* title, int xpos, int ypos, int width, int height, bool fullscreen);
   ~Game();

   void load_level();

   void handle_events();
   void update(const float dt);
   void render();

   bool running()                { return is_running; }

   static SDL_Renderer* renderer;
   static SDL_Window* window;

private:
   int counter{};
   bool is_running{};
   std::vector<std::unique_ptr<GameObject>> game_objects;
};

#endif

