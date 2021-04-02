#include <memory>

#include <cxxopts.hpp>

#include <Engine/Game.hpp>

#include <PongScene.hpp>

#include "Engine/System/ThreadPoolSystem.hpp"

/*Test ThreadPool*/
//ThreadPoolSystem func_pool;
//
//class quit_worker_exception : public std::exception {};
//
//void example_function() { std::cout << "bla" << std::endl; }

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

/*
   //Utilisation multithreading dans main
std::cout << "stating operation" << std::endl;
int num_threads = std::thread::hardware_concurrency();
std::cout << "number of threads = " << num_threads << std::endl;
std::vector<std::thread> thread_pool;
for (int i = 0; i < num_threads; i++) {
  thread_pool.push_back(std::thread(&ThreadPoolSystem::infinite_loop_func, &func_pool));
}

// here we should send our functions
for (int i = 0; i < 500000; i++) {
  func_pool.push(example_function);
}
func_pool.done();
for (unsigned int i = 0; i < thread_pool.size(); i++) {
  thread_pool.at(i).join();
}

std::cout << "fin du processus" << std::endl;

*/