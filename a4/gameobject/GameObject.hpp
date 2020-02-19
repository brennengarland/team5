
#ifndef __GameObject_HPP__
#define __GameObject_HPP__

#include "SDL2/SDL.h"

class GameObject {
public:
   // GameObject(const char* filename_img,
   //            const float xpos, const float ypos,
   //            const float xvel, const float yvel);
   virtual ~GameObject() {};

   virtual void update(const float dt) = 0;
   virtual void render() = 0;

private:
   GameObject() {}
	GameObject(const GameObject&) = delete; //copy constructor
	GameObject& operator=(GameObject&&) = delete; //move assignment operator

   float xpos{}, ypos{};
   float xvel{}, yvel{};

   SDL_Texture* texture{};
   SDL_Rect src_rect, dest_rect;
};

#endif

