#include <Engine/Common/Pool.hpp> 



struct Foo {
  int x = 42;
  Foo() { traceMethod(); }
  Foo(int x) : x(x) { traceMethod(); }
  ~Foo() { traceMethod(); };
  void traceMethod(){
    std::cout << this << " " << "\n";
    }
};

void testPools(){
  Pool<Foo> mp(256);

  Foo *p1 = mp.alloc();
  Foo *p2 = mp.alloc(44);

  std::cout << "p1->x=" << p1->x << "\n";
  std::cout << "p2->x=" << p2->x << "\n";

  mp.free(p1);
  mp.free(p2);
}
