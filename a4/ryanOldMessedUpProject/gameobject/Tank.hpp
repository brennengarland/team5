#ifndef __Tank_HPP__
#define __Tank_HPP__

#include "SDL2/SDL.h"
#include "GameObject.hpp"
#include <vector>
#include <memory>
#include "texture_utils.hpp"


class Tank : public GameObject{
public:
   Tank(const char* filename_img,
              const float xpos, const float ypos,
              const float xvel, const float yvel);
   Tank(
              const float xpos, const float ypos,
              const float xvel, const float yvel);              
   ~Tank();

   void update(const float dt);
   void render();

private:
   float xpos{}, ypos{};
   float xvel{}, yvel{};

   SDL_Texture* texture = texture::load_texture("../assets/images/tank-big-down.png");
   SDL_Rect src_rect, dest_rect;
   //void loadDefaultTexture();

};

#endif