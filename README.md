# Test-GTest

This repository contains some tests using [GoogleTest](https://google.github.io/googletest/) together with CMake.

The download and compilation of GoogleTest is performed directly by the first section of the [CMakeLists.txt](CMakeLists.txt) file of this project.

So, you can directly compile it as usual:

```bash
mkdir build
cd build
cmake ..    # Configure the project, downloading GoogleTest
make        # Compile the project, including also the compilation of GoogleTest
```