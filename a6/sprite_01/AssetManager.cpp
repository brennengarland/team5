
#include "AssetManager.hpp"
#include "sdl_utils.hpp"

AssetManager::~AssetManager()
{}

void AssetManager::clear_data()
{
   textures.clear();
}

void AssetManager::add_texture(const std::string& id, const char* filename)
{
   textures.emplace(id, sdl_utils::load_texture(filename));
}

SDL_Texture* AssetManager::get_texture(const std::string& id)
{
   return textures[id];
}



