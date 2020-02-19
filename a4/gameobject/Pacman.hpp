#ifndef __Pacman_HPP__
#define __Pacman_HPP__

#include "SDL2/SDL.h"
#include "GameObject.hpp"
#include <vector>
#include <memory>

class Pacman : public GameObject{
public:
   Pacman(const char* filename_img,
              const float xpos, const float ypos,
              const float xvel, const float yvel);
   Pacman(
              const float xpos, const float ypos,
              const float xvel, const float yvel);
   ~Pacman();

   void update(const float dt);
   void render();

private:
   float xpos{}, ypos{};
   float xvel{}, yvel{};

   SDL_Texture* texture = texture::load_texture("../assets/images//pacman/pacman_32x32.png");;
   SDL_Rect src_rect, dest_rect;
   //void loadDefaultTexture();

};

#endif