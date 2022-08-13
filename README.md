# Test-GTest

## Overview

This repository contains some tests using [GoogleTest](https://google.github.io/googletest/) together with CMake.

The downloading and compilation of GoogleTest is performed directly by the first section of the main [CMakeLists.txt](CMakeLists.txt) file of this project.

So, you can directly compile it as usual:

```bash
mkdir build
cd build
cmake ..    # Configure the project, downloading GoogleTest
make        # Compile the project, including also the compilation of GoogleTest
```

It will also compile an Example C++ library and include the fo

## Testing

The google tests are included from the CMakeLists.txt as program executables that use the `GTest::gtest_main` library together with our libraries to be tested. In particular, in this repository we are including from the main CMakeLists the subdirectory `test`, where another [CMakeLists file](test/CMakeLists.txt) is generating these google test executables (in particular, [example_test.cpp](test/example_test.cpp)).

Once we have build our project (that compile both, our code and the gtests), we can simply execute our GoogleTests using:

```bash
ctest -V
```

> Note: -V options enables verbose information.

Another way to execute the tests is simply executing the generated executable program. From the build folder:

```bash
./test/example_test
```

The result is the same, although the output information and colors could be better/different and it allows some arguments like `--gtest_filter` to run just a specific or a specific group of tests, for example:

```bash
./test/example_test --gtest_filter=ExampleTestClass.TestSquare
```