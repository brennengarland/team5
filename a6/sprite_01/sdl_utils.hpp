
#ifndef __sdl_utils_HPP__
#define __sdl_utils_HPP__

#include "SDL2/SDL.h"
#include <string>

namespace sdl_utils
{

SDL_Texture* load_texture(const std::string filename);

void draw(SDL_Texture*, SDL_Rect* src_rect, SDL_Rect* dst_rect, SDL_RendererFlip flip);

}

#endif
