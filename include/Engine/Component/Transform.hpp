#pragma once

#include <Engine/Common/Matrix.hpp>
#include <Engine/Component/Component.hpp>

class Transform : public Component {
public:
  RTTI_DECLARATION(Transform)
  Matrix<float, 4, 4> trans;
};