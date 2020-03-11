
#ifndef __TransformComponent_HPP__
#define __TransformComponent_HPP__

#include "../EntityManager.hpp"
#include "../Component.hpp"
#include "glm/vec2.hpp"
#include "SDL2/SDL.h"
#include "../Game.hpp"

class TransformComponent: public Component
{
public:
   glm::vec2 position;
   glm::vec2 velocity;
   int width{};
   int height{};
   int scale{};

   TransformComponent(int posX, int posY, int velX, int velY, int w, int h, int s) {
      position = glm::vec2(posX, posY);
      velocity = glm::vec2(velX, velY);
      width = w;
      height = h;
      scale = s;
   }

   void initialize() override {
   }

   void update(const float dt) override {
      position.x += velocity.x * dt;
      position.y += velocity.y * dt;
   }

   void render() override {
   }

private:

};


#endif

