
#include <doctest.h>

#include <Engine/Pool/Pool.hpp>
#include <iostream>

struct Foo {
  int x = 42;
  Foo() {}
  Foo(int x) : x(x) {}
  ~Foo() {}
};

TEST_CASE("Simple Pool 1") {
  Pool<Foo> mp(5);

  Foo* p1 = mp.alloc();
  Foo* p2 = mp.alloc(44);

  CHECK(p1->x == 42);
  CHECK(p2->x == 44);

  mp.free(p1);
  mp.free(p2);
}

TEST_CASE("Simple Pool 2") {
  Pool<Foo> mp(5);

  Foo* p1 = mp.alloc();
  Foo* p2 = mp.alloc(44);
  mp.free(p2);

  Foo* p3 = mp.alloc(45);

  CHECK(p3 == p2);

  CHECK(p1->x == 42);
  CHECK(p3->x == 45);

  mp.free(p1);
  mp.free(p3);
}