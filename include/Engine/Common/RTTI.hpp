#pragma once

#include <iostream>
#include <string>

#include <Engine/Common/fnv1a.hpp>
#include <Engine/Pool/Pool.hpp>

class RTTI {
public:
  typedef uint32_t type;

  const RTTI& m_Parent;
  static RTTI Default;

  RTTI(const char* name, const RTTI& parent_type = RTTI::Default);

  /**
   * @brief Dit si le RTTI est identique
   * @param other Le RTTI a comparé
   * @return Retourne vrai si, exactement identique
   */
  bool IsExactly(const RTTI& other) const;

  /**
   * @brief Comme IsExactly mais recursif
   * @param other Le RTTI a comparé
   * @return Retourne vrai si, exactement identique ou au moins un parent
   */
  bool IsA(const RTTI& other) const;

  inline const RTTI::type& id() const { return m_ClassId; }
  inline const std::string& name() const { return m_ClassName; }

private:
  const std::string m_ClassName;
  const RTTI::type m_ClassId;
};

#define RTTI_DECLARATION(ClassName) static RTTI rtti;

#define RTTI_DEFINITION_BASE(ClassName) RTTI ClassName::rtti(#ClassName);

#define RTTI_DEFINITION(ClassName, parent) RTTI ClassName::rtti(#ClassName, parent::rtti);