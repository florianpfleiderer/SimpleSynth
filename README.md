# SimpleSynth

## Proposal
https://stea.iue.tuwien.ac.at/CppProjects2023/GroupKProposal

## Build
Clone:
```
git clone https://stea.iue.tuwien.ac.at/CppProjects2023/GroupKProject 
```
### macos
```
mkdir build
cd build
cmake ..
```

## Test
for this project, the catch2 test framework is used.
link to docs: https://github.com/catchorg/Catch2/blob/devel/docs/tutorial.md

### macos
in build directory:
```
cd tests
make <test_name>
./<test_name>
```
build and run all tetsts:
```
make
ctest
```
### windows
Import in VS or VSCode with CMake Tools and C/C++ Plugin.

### linux
TODO Test
