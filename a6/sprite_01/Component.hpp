
#ifndef __Component_HPP__
#define __Component_HPP__

class Entity;

class Component
{
public:
   Component() = default;
   virtual ~Component() {}

   Entity* owner{};

   virtual void initialize()           =0;
   virtual void update(const float dt) =0;
   virtual void render()               =0;
};

#endif

