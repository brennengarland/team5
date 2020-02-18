#ifndef __TEXTURE_UTILS_HPP__
#define __TEXTURE_UTILS_HPP__

#include "SDL2/SDL.h"

namespace texture
{

SDL_Texture* load_texture(const char* filename);

void draw(SDL_Texture*, SDL_Rect src, SDL_Rect dest);

}

#endif
