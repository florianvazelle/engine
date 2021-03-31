#include <memory>

#include <cxxopts.hpp>

#include <Engine/Game.hpp>

#include <PongScene.hpp>

// #include <Engine/Pool/Pool.hpp>

// struct Foo {
//   int x = 42;
//   Foo() { traceMethod(); }
//   Foo(int x) : x(x) { traceMethod(); }
//   ~Foo() { traceMethod(); };
//   void traceMethod() { std::cout << this << "\n"; }
// };

// void testPools() {
//   Pool<Foo> mp(5);

//   Foo *p1 = mp.alloc();
//   Foo *p2 = mp.alloc(44);

//   std::cout << "p1->x=" << p1->x << "\n";
//   std::cout << "p2->x=" << p2->x << "\n";

//   mp.free(p1);
//   mp.free(p2);
// }

int main(int argc, char **argv) {
  cxxopts::Options options(argv[0], "A pong game which use a simple game engine!");

  // Création de la PongScene
  std::shared_ptr<Scene> scene = std::make_shared<PongScene>();

  // Création du jeu
  Game pong(scene);

  // On lance le jeu
  pong.run();

  // testPools();
  return 0;
}