# Dominique [![License](https://img.shields.io/badge/License-Apache%202.0-blue.svg)](https://opensource.org/licenses/Apache-2.0)

A Compiler Front-End based on C++

# Description
Dominque is a complete compiler front-end developed in C++ that generates three-address intermediate codes.
The project is developed based on the complete front-end compiler in Java from the [Dragon Book](https://en.wikipedia.org/wiki/Compilers:_Principles,_Techniques,_and_Tools), 
in current version, the source program consists of syntax tree, with constructors and nodes as objects. These 
objects deal with all of the following: construct a syntax-tree, check types, and generate three-address intermediate code.

## Getting Started

These instructions will get you a copy of the project up and running on your local machine for development and testing purposes.

### Prerequisites
* [Homebrew](https://brew.sh) (A package manager for MacOS and could be used to install CMake and Conan)
* [CMake](https://cmake.org)
* [LLVM](https://llvm.org)

LLVM can be installed with the HomeBrew.
```console
brew install llvm
# Finds llvm information installed from brew
brew info llvm
# Exports LLVM_DIR that allow cmake to find the LLVM
# For example, command below exports LLVM_DIR in the zsh shell
echo 'export LLVM_DR=/usr/local/Cellar/llvm/10.0.1' >> $HOME/.zshrc 
```

### Building

#### Git Clone

First we need to check out the git repo:

```console
cd ${insert your workspace folder here}
git clone https://github.com/lingbozhang/dominique
# Initializes and updates git submodule
cd dominique
git submodule init
git submodule update
```

Now we should be in the project's top level folder. 

#### Building Manually

```console
rm -rf build/manual && mkdir -p build/manual
cd build/manual
cmake ../.. && make
```
## Running Dominique
After the binary is built, run the program and feed the codes you want Dominique
to parse
* Example 1:
```console
./dominique "{int h; float i; bool j; h=1; i=2.0; j=true;}"
Program Name Is: ./dominiqueInput Codes:
{int h; float i; bool j; h=1; i=2.0; j=true;}
```
Expected result:
```console
Generated three-address intermediate code:
L1:	h = 1
L3:	i = 2.000000
L4:	j = true
L5:L2:%
```

## Running Tests
After successfully build the project in build/manual, tests can be triggered
running the command shown below:
```bash
$ ctest
```

## License
[Apache License](LICENSE)
