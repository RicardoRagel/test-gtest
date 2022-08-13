# Test-GTest

## Overview

This repository contains some tests using [GoogleTest](https://google.github.io/googletest/) together with CMake.

The download and compilation of GoogleTest is performed directly by the first section of the [CMakeLists.txt](CMakeLists.txt) file of this project.

So, you can directly compile it as usual:

```bash
mkdir build
cd build
cmake ..    # Configure the project, downloading GoogleTest
make        # Compile the project, including also the compilation of GoogleTest
```

## Testing

The google tests are included from the CMakeLists.txt as program executables that use the `GTest::gtest_main` library together with our libraries. In particular, in this repository we are including from the main CMakeLists the subdirectory `test`, where another CMakeLists file is generating these google test executables (for example, [example_test.cpp](test/example_test.cpp)).

Once we have build our project, we can simply execute our GoogleTests using:

```bash
ctest -V
```

> Note: -V options enables verbose information.