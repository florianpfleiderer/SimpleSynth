# SimpleSynth

### General Description
<!-- short description 
- what is out there so far?
- how would this project fit in?
- in one paragraph with about 100 words. -->

*Simple digital synthesizer with different modules which is easy customizable for different needs. The synthesizer will also have a simple GUI where the nodes are programmed using imnodes. The concept is based on node to node connection where each node represents either a sound producer node or a sound manipulator node. This approach helps with understanding the production of music/sounds. The nodes can have different kind of user inputs for example the cut of frequency. Also the programm should easily be expandable with selfmade plugins. This project should then be used for music production/sound generation.*


### Current Status
<!-- In this example project, there are no dependencies, but if you do require some, make sure you list them here! -->

*There are a lot of professional music/synthesizer programmms out there but not a realy simple one that can be used by beginners without a lot of learning and also can be easily expanded with selfmade plugins. The **imnodes** library already provides a good starting point for the GUI and node to node connections. The **stk** library provides a open source audio signal processing.*

### Project Goals
<!-- General description of what the final software should be able to do, including a rough description of the available API -->

*We want to offer a simple to use, easy to learn synthesizer, that can be easily extended with self-written filters or other kind of pluggins. Therefore, we want to provide an interface*

## Instructions
Clone:
```
git clone https://stea.iue.tuwien.ac.at/CppProjects2023/GroupKProject 
```
### Build
#### macos
```
mkdir build
cd build
cmake ..
```
#### windows
Import in VS or VSCode with CMake Tools and C/C++ Plugin.
#### linux
TODO

### Test
for this project, the catch2 test framework is used.
link to docs: https://github.com/catchorg/Catch2/blob/devel/docs/tutorial.md

#### macos
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
TODO
### linux
TODO

## general information
Link for an extended stk tutorial:
https://ccrma.stanford.edu/software/stk/
