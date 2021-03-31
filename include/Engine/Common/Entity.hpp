#pragma once

#include <iostream>
#include <map>

#include <Engine/Common/ComponentFactory.hpp>
#include <Engine/Component/Collider.hpp>
#include <Engine/Component/Component.hpp>
#include <Engine/Component/Renderer.hpp>
#include <Engine/Component/Transform.hpp>
#include <Engine/Component/Velocity.hpp>

/**
 * L'entité n'est qu'une Map<Key, Value> de Component.
 * La Key correspond au RTTI du Component.
 * La Value est un pointeur vers son Component.
 *
 * Les components sont alloué dans des Pool de leur type.
 * Et quand on crée une entité, on utilise l'espace des pools pour l'ensemble de ses components
 */
class Entity {
public:
  Transform* trans;
  Velocity* velo;
  Collider* coll;
  Renderer* rend;
  // std::map<RTTI::type, Component *> components;

  template <typename... Args> Entity(Args&&... args) : trans(nullptr), velo(nullptr), coll(nullptr), rend(nullptr) {
    ([&](auto &arg) { 
      RTTI::type id        = arg.id(); 
      Component* component = ComponentFactory::Allocate(id);
      SetWithName(id, component);
    } (args), ...);
  }

  ~Entity() {
    ComponentFactory::Free(Transform::rtti.id(), trans);
    ComponentFactory::Free(Velocity::rtti.id(), velo);
    ComponentFactory::Free(Collider::rtti.id(), coll);
    ComponentFactory::Free(Renderer::rtti.id(), rend);
  }

  void SetWithName(const RTTI::type& id, Component* component) {
    if (id == Transform::rtti.id()) trans = (Transform*)component;
    else if (id == Velocity::rtti.id()) velo = (Velocity*)component;
    else if (id == Collider::rtti.id()) coll = (Collider*)component;
    else if (id == Renderer::rtti.id()) rend = (Renderer*)component;
  }

  Component* GetWithName(const RTTI::type& id) {
    if (id == Transform::rtti.id()) return trans;
    else if (id == Velocity::rtti.id()) return velo;
    else if (id == Collider::rtti.id()) return coll;
    else if (id == Renderer::rtti.id()) return rend;
    return nullptr;
  }

  bool Has(const RTTI::type& id) {
    if (id == Transform::rtti.id()) return trans != nullptr;
    else if (id == Velocity::rtti.id()) return velo != nullptr;
    else if (id == Collider::rtti.id()) return coll != nullptr;
    else if (id == Renderer::rtti.id()) return rend != nullptr;
    return false;
  }
};