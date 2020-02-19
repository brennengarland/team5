#include "Pacman.hpp"
#include "Game.hpp"
#include <iostream>
#include "SDL2/SDL_image.h"

constructor with supplied image
Pacman::Pacman(const char* filename_img,
                       const float xpos, const float ypos,
                       const float xvel, const float yvel)
: xpos(xpos), ypos(ypos), xvel(xvel), yvel(yvel)
{
   texture = texture::load_texture(filename_img);
}

//constructor with default pacman image
Pacman::Pacman(
                       const float xpos, const float ypos,
                       const float xvel, const float yvel)
: xpos(xpos), ypos(ypos), xvel(xvel), yvel(yvel)
{
   loadDefaultTexture();
}

Pacman::~Pacman()
{
   SDL_DestroyTexture(texture);
}

void Pacman::update(const float dt)
{
   xpos += xvel * dt;
   ypos += yvel * dt;

   src_rect.h = 32;
   src_rect.w = 32;
   src_rect.x = 0;
   src_rect.y = 0;

   dest_rect.x = static_cast<int>(xpos);
   dest_rect.y = static_cast<int>(ypos);
   dest_rect.w = src_rect.w * 2;
   dest_rect.h = src_rect.h * 2;
}

void Pacman::render()
{
   SDL_RenderCopy(Game::renderer, texture, &src_rect, &dest_rect);
}
// void Pacman::loadDefaultTexture()
// {
//       texture = texture::load_texture("../assets/images//pacman/pacman_32x32.png");

// }