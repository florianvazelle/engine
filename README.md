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

- [Interfaces](https://www.tutorialspoint.com/cplusplus/cpp_interfaces.htm)