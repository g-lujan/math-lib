# Math Library

## Project Setup

- Get the required dependencies with VCPKG, as below:
```
vcpkg install boost-test
```

## Building with MSVC
### for Debug
```
cmake -B build-msvc -S . -G "Visual Studio 17 2022"
cmake --build build-msvc
```

### for Release (Dynamic linking)
```
cmake -B build-msvc -S . -G "Visual Studio 17 2022"
cmake --build build-msvc --config Release
```

### for Release (Static linking)
```
cmake -B build-msvc-static -S . -G "Visual Studio 17 2022" -DVCPKG_TARGET_TRIPLET="x64-windows-static" -DSTATIC_LINKING=ON
cmake --build build-msvc-static --config Release
```

## Building with MinGW (TODO)
```
cmake -B build-mingw -S . -G "MinGW Makefiles" -DCOMPILER="mingw" -DVCPKG_TARGET_TRIPLET="x64-mingw-dynamic"
cmake --build build-mingw'"
```