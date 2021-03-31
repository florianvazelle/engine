#pragma once

#include <map>
#include <string>

#include <Engine/Common/RTTI.hpp>
#include <Engine/Component/Component.hpp>

/**
 * Permet d'allouer un Component peut importe son type, car il va appeler la method type::pool.alloc que l'on a register
 */
struct ComponentFactory {
  // Component pas d'argument pour la création !
  static Component* Allocate(const RTTI::type& name) {
    return Registry[name]();
  }

  // On enregistre la methode de creation pour le type de Component
  static void Register(const RTTI& rtti, std::function<Component*(void)> creator) {
    if (creator) Registry[rtti.id()] = creator;
  }

  static std::map<RTTI::type, std::function<Component*(void)>> Registry; // Key   = RTTI du Component
                                                                         // Value = fonction alloc de la pool correspondante au Component 
};