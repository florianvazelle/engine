#include <PongScene.hpp>
#include <engine/engine.hpp>
#include <memory>

int main(int argv, char** args) {
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
