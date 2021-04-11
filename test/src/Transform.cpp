#include <doctest.h>

#include <Engine/Common/Manager.hpp>
#include <Engine/Component/Transform.hpp>

TEST_CASE("Identity") {
  Transform t;
  CHECK(t[0] == float4(1, 0, 0, 0));
  CHECK(t[1] == float4(0, 1, 0, 0));
  CHECK(t[2] == float4(0, 0, 1, 0));
  CHECK(t[3] == float4(0, 0, 0, 1));
}

TEST_CASE("Translate") {
  float4 v = {-1, -1, 0, 1};

  Transform t;
  t.translate(v);

  CHECK(t.a == float4{1, 0, 0, -1});
  CHECK(t.b == float4{0, 1, 0, -1});
  CHECK(t.c == float4{0, 0, 1, 0});
  CHECK(t.d == float4{0, 0, 0, 1});
}
