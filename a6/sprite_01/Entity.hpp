
#ifndef __Entity_HPP__
#define __Entity_HPP__

#include <vector>
#include <string>
#include <map>

class EntityManager;
class Component;

class Entity {
public:
   std::string name;
   Entity(EntityManager& manager);
   Entity(EntityManager& manager, std::string name);
   void update(const float dt);
   void render();
   void destroy();
   bool is_active() const   { return active; };

   template <typename T, typename... TArgs>
   T& add_component(TArgs&&... args) {
      T* component(new T(std::forward<TArgs>(args)...));
      component->owner = this;
      components.emplace_back(component);
      component_type_map[&typeid(*component)] = component;
      component->initialize();
      return *component;
   }

   template <typename T>
   T* get_component() {
      return static_cast<T*>(component_type_map[&typeid(T)]);
   }

   template <typename T>
   bool has_component() const {
      return true;
   }

   void list_all_components() const;

private:
   EntityManager& manager;

   bool active{true};
   std::vector<Component*> components;
   std::map<const std::type_info*, Component*> component_type_map;
};

#endif

