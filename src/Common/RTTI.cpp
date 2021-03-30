#include <Engine/Common/RTTI.hpp>

RTTI RTTI::Default("", *((RTTI*)nullptr));

RTTI::RTTI(const char* name, const RTTI& parent_type) : m_Parent(parent_type) {
  m_ClassName = name;
  // type = fnv1a(name);
}

bool RTTI::IsExactly(const RTTI& other) const { return m_ClassName == other.m_ClassName; }

bool RTTI::IsA(const RTTI& other) const 
{
          const RTTI* p = this;
          do 
          {
            if (p->IsExactly(other)) return true;
            p = &(p->m_Parent);
          } while (p != nullptr);

          return false;
}  // IsExactly () recursif

