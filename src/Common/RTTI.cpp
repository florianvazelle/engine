#include <Engine/Common/RTTI.hpp>

RTTI RTTI::Default(crc32(""), *((RTTI*)nullptr));

RTTI::RTTI(const RTTI::type& id, const RTTI& parent_type) : m_Parent(parent_type), m_ClassId(id) {}

bool RTTI::IsExactly(const RTTI& other) const { return m_ClassId == other.m_ClassId; }

bool RTTI::IsA(const RTTI& other) const {
  const RTTI* p = this;
  do {
    if (p->IsExactly(other)) return true;
    p = &(p->m_Parent);
  } while (p != nullptr);

  return false;
}
