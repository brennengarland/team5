
#include "GameObject.hpp"


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



