#pragma once

#include <memory>
#include <vector>

class Context;

class Engine {
 public:
  void FixedUpdate() const;
  void Render() const;
};