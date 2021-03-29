#include <memory>

#include <cxxopts.hpp>

#include <Engine/Game.hpp>

#include <PongScene.hpp>

#include <Engine/Pool.hpp>

int main(int argc, char** argv) {
  cxxopts::Options options(argv[0], "A pong game which use a simple game engine!");

  // Création de la PongScene
  std::shared_ptr<Scene> scene = std::make_shared<PongScene>();

  // Création du jeu
  Game pong(scene);

  // On lance le jeu
  pong.run();

  //testPools();
  return 0;
}