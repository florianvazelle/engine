#pragma once

#include <memory>
#include <vector>

class Context;

class Engine {
 public:
  void FixedUpdate(const Context& context) const;
  void Render(const Context& context) const;
};