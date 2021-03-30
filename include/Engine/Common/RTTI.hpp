#pragma once
#include <string>
#include <iostream>

class RTTI {
public:
  std::string m_ClassName;
  const RTTI& m_Parent;
  static RTTI Default;
  RTTI(const char* name, const RTTI& parent_type = RTTI::Default);
  bool IsExactly(const RTTI& other) const;
  bool IsA(const RTTI& other) const;  // IsExactly () recursif
};


#define RTTI_DECLARATION \
	static RTTI rtti;

#define RTTI_DEFINITION_BASE(ClassName) \
	RTTI ClassName::rtti(#ClassName);

#define RTTI_DEFINITION(ClassName, parent) \
	RTTI ClassName::rtti(#ClassName, parent::rtti);