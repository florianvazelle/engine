#pragma once

#include <iostream>
#include <map>

#include <Engine/Common/RTTI.hpp>
#include <Engine/Component/Component.hpp>

class Entity {
public:
  RTTI_DECLARATION

  std::map<std::string, Component *> components;

  template <typename... Args> Entity(Args &&... args) {
    (
        [&](auto &arg) {
          std::cout << arg->rtti.m_ClassName << std::endl;
          Component *&el = components[arg->rtti.m_ClassName];
          el             = arg;
        }(args),
        ...);
  }
};