
#ifndef __SpriteComponent_HPP__
#define __SpriteComponent_HPP__

#include "../Component.hpp"
#include "../AssetManager.hpp"
#include "../Game.hpp"
#include "../sdl_utils.hpp"

#include "TransformComponent.hpp"

#include "SDL2/SDL.h"

#include <string>

class SpriteComponent: public Component
{
public:
   SDL_RendererFlip sprite_flip = SDL_FLIP_NONE;

   SpriteComponent(std::string texture_id) {
      set_texture(texture_id);
   }

   void set_texture(std::string& texture_id) {
      texture = Game::asset_manager->get_texture(texture_id);
   }

   void initialize() override {
      transform = owner->get_component<TransformComponent>();
      src_rect.x = 0;
      src_rect.y = 0;
      src_rect.w = transform->width;
      src_rect.h = transform->height;
   }

   void update(const float dt) override {
      dst_rect.x = static_cast<int>(transform->position.x);
      dst_rect.y = static_cast<int>(transform->position.y);
      dst_rect.w = static_cast<int>(transform->width * transform->scale);
      dst_rect.h = static_cast<int>(transform->height * transform->scale);
   }

   void render() override {
      sdl_utils::draw(texture, &src_rect, &dst_rect, sprite_flip); 
   }

private:
   TransformComponent* transform{};
   SDL_Texture* texture{};
   SDL_Rect src_rect;
   SDL_Rect dst_rect;
};

#endif
