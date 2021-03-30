#include <PongScene.hpp>

#include <Engine/Common/EntityManager.hpp>
#include <Engine/Common/Log.hpp>

void PongScene::preload() {}

void PongScene::create() {
  EntityFactory* obdb = EntityManager::GetInstance();
  Bar* player1        = obdb->allocate<Bar>();
  Bar* player2        = obdb->allocate<Bar>();
  Ball* ball          = obdb->allocate<Ball>();
}

void PongScene::update(double deltaTime) { LOG("update!"); }

void PongScene::destroy() {
  EntityFactory* obdb = EntityManager::GetInstance();
  obdb->free<Ball>(ball);
  obdb->free<Bar>(player2);
  obdb->free<Bar>(player1);
}