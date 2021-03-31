#include <Engine/System/LogicalSystem.hpp>

#include <Engine/Common/EntityManager.hpp>
#include <Engine/Common/Log.hpp>
#include <Engine/Component/Collider.hpp>
#include <Engine/Component/Transform.hpp>
#include <Engine/Component/Velocity.hpp>

#include <stdlib.h>

void LogicalSystem::update(double deltaTime) {
  LOG("Update");

  EntityFactory* obdb = EntityManager::GetInstance();

  // Apply Velocity
  std::vector<Entity*> entities(10);
  for (int i = 0; i < entities.size(); i++) {
    std::cout << entities[i] << std::endl;
  }

  obdb->GetObjectsWithTag(entities, Transform::rtti, Collider::rtti);

  for (int i = 0; i < entities.size(); i++) {
    std::cout << entities[i] << std::endl;
  }
  LOG("Fin du System je quitte le programme");
  exit(0);
}