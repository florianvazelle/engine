
#include <doctest/doctest.h>

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

TEST_CASE("Simple Pool with ID") {
  Pool<Foo> mp(5);

  Foo* p1 = mp.alloc_with_id(3);
  Foo* p2 = mp.alloc_with_id(2, 44);

  CHECK(p1->x == 42);
  CHECK(p2->x == 44);

  CHECK(mp.at(3)->get_storage()->x == 42);
  CHECK(mp.at(2)->get_storage()->x == 44);

  CHECK(!(mp.in_free_list(mp.at(3))));
  CHECK(!(mp.in_free_list(mp.at(2))));
  CHECK(mp.in_free_list(mp.at(0)));
  CHECK(mp.in_free_list(mp.at(1)));
  CHECK(mp.in_free_list(mp.at(4)));

  mp.free_with_id(3);
  CHECK(mp.in_free_list(mp.at(3)));

  Foo* p3 = mp.alloc_with_id(3);
  CHECK(p3 == p1);

  mp.free(p2);
}
