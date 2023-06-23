# SimpleSynth [![Pipeline](https://github.com/florianpfleiderer/SimpleSynth/workflows/CMake/badge.svg?branch=main)](https://github.com/florianpfleiderer/SimpleSynth/actions)

### General Description
<!-- short description 
- what is out there so far?
- how would this project fit in? -->

*Simple digital synthesizer with different modules which is easy customizable for different needs. The synthesizer will also have a simple GUI where the nodes are programmed using imnodes. The concept is based on node to node connection where each node represents either a sound producer node or a sound manipulator node. This approach helps with understanding the production of music/sounds. The nodes can have different kind of user inputs for example the cut of frequency. Also the programm should easily be expandable with selfmade plugins. This project should then be used for music production/sound generation.*


### Current Status

*There are a lot of professional music/synthesizer programmms out there but not a realy simple one that can be used by beginners without a lot of learning and also can be easily expanded with selfmade plugins. The **imnodes** library already provides a good starting point for the GUI and node to node connections. The **stk** library provides a open source audio signal processing.*

### Project Goals

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
For this project, the catch2 test framework is used.
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

## Team
- *Dennis Waniek*
- *Robert Ristic*
- *Theresa Freibauer*
- *Florian Pfleiderer*
- *Felix Widauer*
- *Moritz Mairhofer*
- *Thomas Schwabe*

## References
[1] https://github.com/Nelarius/imnodes<br>
[2] https://github.com/thestk/stk<br>
[3] https://github.com/catchorg/Catch2<br>

Link for an extended stk tutorial:
https://ccrma.stanford.edu/software/stk/
