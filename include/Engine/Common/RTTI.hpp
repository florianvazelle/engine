#pragma once
#include <string>

class RTTI {
public:
  const std::string m_ClassName;
  const RTTI* m_Base;
  const enum {};

private:
  bool IsExactly(const RTTI& rtti) const;
  bool IsA(const RTTI& rtti) const;  // IsExactly () recursif
};