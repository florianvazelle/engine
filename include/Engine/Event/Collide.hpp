#pragma once

#include <Engine/Event/IEvent.hpp>

class Collide final : public IEvent {
 public:
  RTTI_DECLARATION

  inline Collide(const Entity& e1, const Entity& e2) : e1(e1), e2(e2) {}
  inline const Entity& entity1() const { return e1; }
  inline const Entity& entity2() const { return e2; }

 private:
  const Entity& e1;
  const Entity& e2;
};