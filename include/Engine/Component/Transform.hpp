#pragma once

#include <Engine/Component/Component.hpp>
#include <Engine/Matrix.hpp>

class Transform : public Component {
public:
  Matrix<float, 4, 4> trans;
};