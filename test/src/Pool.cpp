
#include <doctest/doctest.h>

#include <Engine/Pool/Pool.hpp>

struct Foo {
  int x = 42;
  Foo() {}
  Foo(int x) : x(x) {}
  ~Foo() {}
};

void testPools() {
  Pool<Foo> mp(5);

  Foo* p1 = mp.alloc();
  Foo* p2 = mp.alloc(44);

  std::cout << "p1->x=" << p1->x << "\n";
  std::cout << "p2->x=" << p2->x << "\n";

  mp.free(p1);
  mp.free(p2);
}

TEST_CASE("Simple Pool") {
  Pool<Foo> mp(5);

  Foo* p1 = mp.alloc();
  Foo* p2 = mp.alloc(44);

  CHECK(p1->x == 42);
  CHECK(p2->x == 44);

  mp.free(p1);
  mp.free(p2);
}

TEST_CASE("Simple Pool") {
  Pool<Foo> mp(5);

  Foo* p1 = mp.alloc();
  Foo* p2 = mp.alloc(44);
  mp.free(p2);

  Foo* p3 = mp.alloc(45);

  CHECK(p1->x == 42);
  CHECK(p2->x == 45);

  mp.free(p1);
  mp.free(p2);
}
