# engine

It's a work in progress small game engine, usable like a C++ library.

## Features

- No allocation during game loop ([Object pooling](https://en.wikipedia.org/wiki/Object_pool_pattern))
- Custom [run-time type identification](https://en.wikipedia.org/wiki/Run-time_type_information)
- Data-driven oriented design with [Entity, Component and System](https://en.wikipedia.org/wiki/Entity_component_system)
- Multithreading system with [Thread Pool](https://en.wikipedia.org/wiki/Thread_pool)
- Basic [SIMD](https://fr.wikipedia.org/wiki/Single_instruction_multiple_data) operations for Matrix multiplication

### RTTI

- Compile-time hashing (with [`constexpr`](https://en.cppreference.com/w/cpp/language/constexpr) and [CRC32](https://stackoverflow.com/questions/10953958/can-crc32-be-used-as-a-hash-function#10962213))
- Disabling default C++ RTTI (with `-fno-rtti` flags)

### ECS

- Entity type is just an alias of `uint32_t`
- Using of [Factory Design](https://www.tutorialspoint.com/design_pattern/factory_pattern.htm) to allocate Component in Pools
- We can `GetObjectsWithTag` to retrieve entities with certain components

## Building

### Build and run the standalone target

Use the following command to build and run the executable target.

```bash
cmake -Bbuild
cmake --build build
./build/pong
```

## Dependencies

- C++17 compiler :
  - Visual Studio 2016
  - GCC 7+ or Clang 8+
- [Git](https://git-scm.com/) for cmake automatic dependencies
- [CMake](https://cmake.org/) for build system creation (>= 3.12)
- [Doxygen](https://doxygen.org/) for generate documentation (>= 1.8, optional)

## References

- [Pool and Arena](https://thinkingeek.com/2017/11/19/simple-memory-pool/)
- [ECS Tutorial](https://austinmorlan.com/posts/entity_component_system/)
- SIMD Matrix [Multiplication](https://blog.qiqitori.com/2018/05/matrix-multiplication-using-simd-instructions/), [Inverse](https://lxjk.github.io/2017/09/03/Fast-4x4-Matrix-Inverse-with-SSE-SIMD-Explained.html)
- [Fixed-Step Game Loop](https://gafferongames.com/post/fix_your_timestep/)
- [Double-check locking](https://en.wikipedia.org/wiki/Double-checked_locking)
