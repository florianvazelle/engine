#pragma once

#include <engine/meta/Hash.hpp>

using RTTI = uint32_t;

#define RTTI_DEFINITION_BASE(ClassName)                                  \
 public:                                                                 \
  static constexpr RTTI rtti = crc32(#ClassName);                        \
  static constexpr bool IsExactly(const RTTI& id) { return id == rtti; } \
  static constexpr bool IsA(const RTTI& id) { return IsExactly(id); }

#define RTTI_DEFINITION(ClassName, ParentClass)                          \
 private:                                                                \
  using SuperClass = ParentClass;                                        \
                                                                         \
 public:                                                                 \
  static constexpr RTTI rtti = crc32(#ClassName);                        \
  static constexpr bool IsExactly(const RTTI& id) { return id == rtti; } \
  static constexpr bool IsA(const RTTI& id) {                            \
    return IsExactly(id) || SuperClass::IsA(id);                         \
  }
