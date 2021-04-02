#pragma once

#include <memory>
#include <vector>

#include <Engine/IScene.hpp>
#include <Engine/System/System.hpp>

class Context;

class Engine {
public:
  Engine();

  void Update(Context& context, const std::shared_ptr<IScene>& scene);

private:
  std::vector<std::shared_ptr<System>> systems;
};