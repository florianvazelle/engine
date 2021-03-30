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
  // Allocate a pool of Foo objects with an arena size of 256
  Pool<Foo> mp(3);
  std::cout << mp.arena_size  << "\n";
  
  Foo *p1 = mp.alloc(10);
  Foo *p2 = mp.alloc(20);
  Foo *p3 = mp.alloc(30);
  Foo *p4 = mp.alloc(40);

  std::cout << "p1->x=" << p1->x << "\n";
  std::cout << "p2->x=" << p2->x << "\n";
  std::cout << "p3->x=" << p3->x << "\n";
  //std::cout << "p4->x=" << p4->x << "\n";

  std::cout << "free p2 ..." << p2->x << "\n";
  mp.free(p2);
  Foo *p5 = mp.alloc(50);
  Foo *p6 = mp.alloc(60);

  std::cout << "p1->x=" << p1->x << "\n";
  std::cout << "p2->x=" << p2->x << "\n";
  std::cout << "p3->x=" << p3->x << "\n";
  //std::cout << "p4->x=" << p4->x << "\n";
  std::cout << "p5->x=" << p5->x << "\n";
  //std::cout << "p6->x=" << p6->x << "\n";

  mp.free(p1);
  //mp.free(p2);
  mp.free(p3);
  mp.free(p4);
  mp.free(p5);
  mp.free(p6);
}
