#pragma once

#include <iostream>
#include <map>

#include <Engine/Common/RTTI.hpp>
#include <Engine/Component/Component.hpp>

class Entity {
public:
  RTTI_DECLARATION

  std::map<RTTI::type, Component *> components;

  template <typename... Args> Entity(Args &&... args) {
    (
        [&](auto &arg) {
          // std::cout << arg->rtti.id() << std::endl;
          Component *&el = components[arg->rtti.id()];
          el             = arg;
        }(args),
        ...);
  }
};