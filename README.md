# engine

It's a work in progress simple game engine.

## Building

### Build and run the standalone target

Use the following command to build and run the executable target.

```bash
cmake -Bbuild
cmake --build build
./build/bin/GreeterStandalone --help
```

## Dependencies

- C++11 compiler :
  - Visual Studio 2015
  - GCC 5+ or Clang 5+
- [CMake](https://cmake.org/) for build system creation (>= 3.8)
- [Conan](https://conan.io/) for install packages (>= 1.0)
- [Doxygen](https://doxygen.org/) for generate documentation (>= 1.8, optional)

## References

- [Guidelines](https://github.com/isocpp/CppCoreGuidelines)

- [Interfaces](https://www.tutorialspoint.com/cplusplus/cpp_interfaces.htm)
- [Pool and Arena](https://thinkingeek.com/2017/11/19/simple-memory-pool/)
- [ECS](https://austinmorlan.com/posts/entity_component_system/)
- [RTTI](https://www.axelmenzel.de/articles/rtti)
- [SIMD matrix multiplication](https://blog.qiqitori.com/2018/05/matrix-multiplication-using-simd-instructions/)

- [Double-check locking](https://en.wikipedia.org/wiki/Double-checked_locking)
- [Factory Design](https://www.tutorialspoint.com/design_pattern/factory_pattern.htm)