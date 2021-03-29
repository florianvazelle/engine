#include <Engine/RTTI.hpp>

bool RTTI::IsExactly (const RTTI & rtti ) const {return this == &rtti;}
bool RTTI::IsA(const RTTI& rtti) const {}  // IsExactly () recursif