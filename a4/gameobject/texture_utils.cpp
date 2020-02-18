
#include "texture_utils.hpp"

#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"

#include "Game.hpp"
#include <iostream>

namespace texture
{

SDL_Texture* load_texture(const char* filename_img)
{
   SDL_Surface* surface = IMG_Load(filename_img);
   if (!surface) {
      std::cout << "IMG_Load: " << IMG_GetError() << std::endl;
      exit(-1);
   }
   SDL_Texture* texture = SDL_CreateTextureFromSurface(Game::renderer, surface);
   SDL_FreeSurface(surface);
   return texture;
}

void draw(SDL_Texture* tex, SDL_Rect src, SDL_Rect dest)
{
   SDL_RenderCopy(Game::renderer, tex, &src, &dest);
}

}


