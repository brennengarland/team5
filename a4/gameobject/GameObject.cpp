
#include "GameObject.hpp"
#include "texture_utils.hpp"
#include "Game.hpp"

GameObject::GameObject(const char* filename_img,
                       const float xpos, const float ypos,
                       const float xvel, const float yvel)
: xpos(xpos), ypos(ypos), xvel(xvel), yvel(yvel)
{
   texture = texture::load_texture(filename_img);
}

GameObject::~GameObject()
{
   SDL_DestroyTexture(texture);
}

void GameObject::update(const float dt)
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

void GameObject::render()
{
   SDL_RenderCopy(Game::renderer, texture, &src_rect, &dest_rect);
}

