# Requirements

Ubuntu 16.04
+ python3.6
+ apt install python3.6-dev

Windows
Cmake version > 3.5.1


# Python Bindings for BL JPS algorithm

Python bindings for using the BL_JPS algorithm. Requires CMake. To compile:

```
mkdir build
cd build
cmake .. -DCMAKE_BUILD_TYPE=Release
cmake --build . --config Release
```

Windows may require specific 64 bit instruction for visual studio such as

```
mkdir build
cd build
cmake .. -G"Visual Studio 15 2017 Win64" -DCMAKE_BUILD_TYPE=Release
cmake --build . --config Release
```


This will generate a binary file in the `build` directory (`./lib/` for Linux and `./Debug/`/`./Release` for MSVC).

To run, copy the `.a/.so` (Linux) or `.pyd` (Windows) file to project and import with
`import BL_JPS`


## Example usage

```
import BL_JPS

map_data = [0, 0, 0, 1]
bljps = BL_JPS.BL_JPS()
bljps.preProcessGrid(map_data, width=2, height=2)
path = bljps.findSolution(sX=0, sY=0, eX=1, eY=0)
```
Note that the path is in revers ordr (i.e. `path[0] = eX,eY`, if reachable)

Path is made up of coordinate structs, which can be accessed with either `c.x`/`c.y` or `c[0]`/`c[1]` (where `c = path[0]`).


## Changes from original BL_JPS code

The following changes were required for the Python bindings to work:

- Make a copy of the grid in BL_JPS rather than use the pointer (as Python GC cleans up the original data)
- Refactor findSolution to return a vector rather than use an out param
- Extend coordinate with `operator[], operator==, operator!=`
