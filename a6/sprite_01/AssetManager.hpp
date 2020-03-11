
#ifndef __AssetManager_HPP__
#define __AssetManager_HPP__

#include <map>
#include <string>
#include "SDL2/SDL.h"

class AssetManager
{
public:
   AssetManager() =default;
   ~AssetManager();

   void clear_data();
   void add_texture(const std::string& id, const char* filename);
   SDL_Texture* get_texture(const std::string& id);

private:
   std::map<std::string, SDL_Texture*> textures;

};

#endif

