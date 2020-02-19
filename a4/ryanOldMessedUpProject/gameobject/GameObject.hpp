
#ifndef __GameObject_HPP__
#define __GameObject_HPP__
#include "texture_utils.hpp"
#include "Game.hpp"
#include "SDL2/SDL.h"

class GameObject {
public:
   // GameObject(const char* filename_img,
   //            const float xpos, const float ypos,
   //            const float xvel, const float yvel);
   // ~GameObject();
   virtual void update(const float dt) = 0;
   virtual void render() = 0;
   // GameObject(const char* filename_img,
   //            const float xpos, const float ypos,
   //            const float xvel, const float yvel);
   // GameObject(
   //            const float xpos, const float ypos,
   //            const float xvel, const float yvel);

private:
   float xpos{}, ypos{};
   float xvel{}, yvel{};

   SDL_Texture* texture{};
   SDL_Rect src_rect, dest_rect;
   //virtual void loadDefaultTexture() = 0;

};

#endif

