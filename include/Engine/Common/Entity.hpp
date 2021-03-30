#pragma once

#include <iostream>
#include <map>

#include <Engine/Component/Component.hpp>

class Entity {
public:
  std::map<std::string, Component *> components;

  template <typename... Args> Entity(Args &&... args) {
    (
        [&](auto &arg) {
          std::cout << arg->name() << std::endl;
          Component *&el = components[arg->name()];
          el             = arg;
        }(args),
        ...);
  }
};