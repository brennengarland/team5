
#include "EntityManager.hpp"

#include <iostream>

void EntityManager::clear_data()
{
   for (auto& entity: entities) {
      entity->destroy();
   }
}

bool EntityManager::has_no_entities() const
{
   return entities.size() == 0;
}

void EntityManager::update(const float dt)
{
   for (auto& entity: entities) {
      entity->update(dt);
   }
}

void EntityManager::render()
{
   for (auto& entity: entities) {
      entity->render();
   }
}

Entity& EntityManager::add_entity(const std::string name)
{
   Entity* entity = new Entity(*this, name);
   entities.emplace_back(entity);
   return *entity;
}

std::vector<Entity*> EntityManager::get_entities() const
{
   return entities;
}

std::size_t EntityManager::get_entity_count() const
{
   return entities.size();
}

void EntityManager::list_all_entities() const
{
   std::size_t i{};
   for (auto& entity: entities) {
      std::cout << "Entity[" << i << "]:" << entity->name << std::endl;
      entity->list_all_components();
      i++;
   }
}

