#include <memory>

#include <cxxopts.hpp>

#include <Engine/Game.hpp>

#include <PongScene.hpp>

#include <Pool.hpp>
#include <iostream>
#define TRACE_METHOD() std::cout << this << " " << "test" << "\n";
void testPools();

int main(int argc, char** argv) {
  cxxopts::Options options(argv[0], "A pong game which use a simple game engine!");

  // Création de la PongScene
  std::shared_ptr<Scene> scene = std::make_shared<PongScene>();

  // Création du jeu
  Game pong(scene);

  // On lance le jeu
  pong.run();

  testPools();
  return 0;
}


struct Foo {
  int x = 42;
  Foo() { TRACE_METHOD(); }
  Foo(int x) : x(x) { TRACE_METHOD(); }
  ~Foo() { TRACE_METHOD(); };
};

void testPools(){
  minipool<Foo> mp(256);

  Foo *p1 = mp.alloc();
  Foo *p2 = mp.alloc(44);

  std::cout << "p1->x=" << p1->x << "\n";
  std::cout << "p2->x=" << p2->x << "\n";

  mp.free(p1);
  mp.free(p2);
}