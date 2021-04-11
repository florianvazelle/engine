#include <Engine/Game.hpp>
#include <PongScene.hpp>
#include <cxxopts.hpp>
#include <memory>

int main(int argc, char** argv) {
  cxxopts::Options options(argv[0], "A pong game which use a simple game engine!");

  // Création du jeu
  Game pong("pong", WINDOW_WIDTH, WINDOW_HEIGHT,
            SDL_WINDOW_SHOWN | SDL_WINDOW_INPUT_FOCUS | SDL_WINDOW_MOUSE_FOCUS |
                SDL_WINDOW_ALLOW_HIGHDPI);

  // Création de la PongScene
  std::shared_ptr<Scene> scene = std::make_shared<PongScene>();

  // On lance le jeu
  pong.run(scene);

  // testPools();
  return 0;
}
