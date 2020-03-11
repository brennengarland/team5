
#include "sdl_utils.hpp"

#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"

#include "Game.hpp"
#include <iostream>
#include <string>

namespace sdl_utils
{

SDL_Texture* load_texture(const std::string filename)
{
   SDL_Surface* surface = IMG_Load(filename.c_str());
   if (!surface) {
      std::cout << "IMG_Load: " << IMG_GetError() << std::endl;
      exit(-1);
   }
   SDL_Texture* texture = SDL_CreateTextureFromSurface(Game::renderer, surface);
   SDL_FreeSurface(surface);
   return texture;
}

void draw(SDL_Texture* tex, SDL_Rect* src_rect, SDL_Rect* dst_rect, SDL_RendererFlip flip)
{
   SDL_RenderCopyEx(Game::renderer, tex, src_rect, dst_rect, 0.0, NULL, flip);
}

}


