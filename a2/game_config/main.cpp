
#include "Game.hpp"
#include "lua.hpp"
#include <iostream>
#include <memory>
    

int main() {

   std::cout << "Creating game" << std::endl;

   int xpos, ypos, width, height;
   bool fullscreen;

   // read Lua script to determine initial window size infomation
   //create a new lua state
   lua_State *L = luaL_newstate();
   luaopen_base(L);
   luaopen_io(L);
   luaopen_string(L);
   luaopen_math(L);
   luaL_dofile(L, "config.lua");
   //these lines grab these variables from config.lua and place them on the stack of this program 
   lua_getglobal(L, "xpos");
   lua_getglobal(L, "ypos");
   lua_getglobal(L, "width");
   lua_getglobal(L, "height");
   lua_getglobal(L, "fullscreen");

   //these lines cast the data stored on the stack as global variables earlier as either ints or a boolean 
   xpos = static_cast<int>(lua_tonumber(L, -5));
   ypos = static_cast<int>(lua_tonumber(L, -4));
   width = static_cast<int>(lua_tonumber(L, -3));
   height = static_cast<int>(lua_tonumber(L, -2));
   fullscreen = lua_toboolean(L, -1);

   //terminate the lua process
   lua_close(L);
   //print out variables
   std::cout << "Xpos: " << xpos << "\n";
   std::cout << "Ypos: " << ypos << "\n";
   std::cout << "Width: " << width << "\n";
   std::cout << "Height: " << height << "\n";
   //instantiate new games with the values read in from config.lua
   auto game = std::make_unique<Game>("1st Game", xpos, ypos, width, height, fullscreen);

   std::cout << "Starting game loop" << std::endl;
   while (game->running()) {
      game->handle_events();
      game->update();
      game->render();
   }

   return 0;
}

