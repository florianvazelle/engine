#include <Engine/System/LogicalSystem.hpp>

#include <Engine/Common/Log.hpp>
#include <Engine/Common/Manager.hpp>
#include <Engine/Component/Collider.hpp>
#include <Engine/Component/Transform.hpp>
#include <Engine/Component/Velocity.hpp>

#include <stdlib.h>

void LogicalSystem::update(double deltaTime) {
  LOG("Update");

  Manager* obdb = Manager::GetInstance();

  // Apply Velocity
  // for (int i = 0; i < entitiesQuery.size(); i++) {
  //   std::cout << entitiesQuery[i] << std::endl;
  // }

  obdb->GetObjectsWithTag(entitiesQuery, Transform::rtti, Velocity::rtti);

  // for (int i = 0; i < entitiesQuery.size(); i++) {
  //   std::cout << entitiesQuery[i] << std::endl;
  // }

  // for (int i = 0; i < entitiesQuery.size(); i++) {
  //   func_pool.push([](Entity* e) {
  //     e->trans += e->velo;
  //   });
  // }

  // func_pool.done();

  // for (unsigned int i = 0; i < thread_pool.size(); i++) {
  //   thread_pool.at(i).join();
  // }

  // exit(0);
}