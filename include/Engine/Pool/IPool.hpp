#pragma once

class IPool {
public:
  virtual ~IPool() = default;

  virtual void Allocate(const Entity &e) = 0;
  virtual void Free(const Entity &e)     = 0;
  virtual void *Get(const Entity &e)     = 0;
};