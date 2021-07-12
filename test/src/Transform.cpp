#include <doctest.h>

#include <engine/engine.hpp>

TEST_CASE("Identity") {
  Transform t;
  CHECK(t[0] == float4(1, 0, 0, 0));
  CHECK(t[1] == float4(0, 1, 0, 0));
  CHECK(t[2] == float4(0, 0, 1, 0));
  CHECK(t[3] == float4(0, 0, 0, 1));
}

TEST_CASE("Translate") {
  Transform t;
  t.translate({-1, -1, 0, 1});

  CHECK(t.a == float4{1, 0, 0, -1});
  CHECK(t.b == float4{0, 1, 0, -1});
  CHECK(t.c == float4{0, 0, 1, 0});
  CHECK(t.d == float4{0, 0, 0, 1});

  t.translate({2, 5, 1, 1});

  CHECK(t.a == float4{1, 0, 0, 1});
  CHECK(t.b == float4{0, 1, 0, 4});
  CHECK(t.c == float4{0, 0, 1, 1});
  CHECK(t.d == float4{0, 0, 0, 1});
}

TEST_CASE("Inverse") {
  Transform mat;

  float data[16] = {-1, 0, 1, 1, 1, -2, 1, -1, 1, 0, -1, 1, 1, 0, 1, -1};
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      mat[i][j] = data[i + j * 4];
    }
  }

  float result[16] = {0.0f, 0.0f, 0.5f, 0.5f, 0.0f, -0.5f, 0.0f, 0.5f,
                      0.5f, 0.0f, 0.0f, 0.5f, 0.5f, 0.0f,  0.5f, 0.0f};

  Transform inv = mat.inverse();
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      CHECK(result[i + j * 4] == inv[i][j]);
    }
  }
}

TEST_CASE("Vector Multiplication") {
  float4 v = {-1, -1, 0, 0};
  float4 result = {-1, -1, 0, 0};

  Transform t;
  t.translate({0, 0, 3, 1});

  CHECK(t * v == result);
}

TEST_CASE("Point Multiplication") {
  float4 v = {-1, -1, 0, 1};
  float4 result = {-1, -1, 3, 1};

  Transform t;
  t.translate({0, 0, 3, 1});

  CHECK(t * v == result);
}

TEST_CASE("float4 Multiplication") {
  float4 v = {-1, -1, 0, 1};
  float4 r = {0, 0, 3, 1};

  CHECK((r * v) == 1);
}

TEST_CASE("float4 Multiplication") {
  float4 v = {-1, -1, 0, 1};
  float4 result = {-4, -4, 0, 4};

  v *= 4;

  CHECK(v == result);
}

// TEST_CASE("Intersection 1") {
//   Transform t1;
//   t1.a = {1, 0, 0, 0};
//   t1.b = {0, 1, 0, 0};
//   t1.c = {0, 0, 1, 0};
//   t1.d = {0, 0, 0, 1};

//   Transform t2;
//   t1.a = {1, 0, 0, 0.5f};
//   t1.b = {0, 1, 0, 1};
//   t1.c = {0, 0, 1, 0};
//   t1.d = {0, 0, 0, 1};

//   CHECK(t1.intersect(t2));
// }

// TEST_CASE("Intersection 2") {
//   Transform t1;
//   t1.a = {1, 0, 0, 0};
//   t1.b = {0, 1, 0, 0};
//   t1.c = {0, 0, 1, 0};
//   t1.d = {0, 0, 0, 1};

//   Transform t2;
//   t1.a = {1, 0, 0, 2};
//   t1.b = {0, 1, 0, 2};
//   t1.c = {0, 0, 1, 2};
//   t1.d = {0, 0, 0, 1};

//   CHECK(!t1.intersect(t2));
// }