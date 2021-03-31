#pragma once

#include <map>
#include <string>

#include <Engine/Common/RTTI.hpp>
#include <Engine/Component/Component.hpp>

/**
 * Permet d'allouer un Component peut importe son type, car il va appeler la method type::pool.alloc que l'on a register
 */
struct ComponentFactory {
  using AllocFree = std::pair<std::function<Component*(void)>, std::function<void(Component*)>>;
  
  // Component pas d'argument pour la création !
  static Component* Allocate(const RTTI::type& name) {
    return Registry[name].first();
  }

  static void Free(const RTTI::type& name, Component* component) {
    if (component != nullptr) Registry[name].second(component);
  }

  // On enregistre la methode de creation pour le type de Component
  static void Register(const RTTI& rtti, const AllocFree& creator) {
    Registry[rtti.id()] = creator;
  }

  static std::map<RTTI::type, AllocFree> Registry;  // Key   = RTTI du Component
                                                    // Value = fonction alloc de la pool correspondante au Component
};