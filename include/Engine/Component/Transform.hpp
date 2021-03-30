#pragma once

#include <Engine/Common/Matrix.hpp>
#include <Engine/Component/Component.hpp>

class Transform : public Component {
public:
  Matrix<float, 4, 4> trans;
  std::string name() { return "transfrom"; }
};