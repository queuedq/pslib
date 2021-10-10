# pslib

A collection of algorithms for use in programming competitions / online judges.

## Goal

- Easy to copy & paste (or type out in the contest environment with a printed team note)
- Unit tests as documentation
- (Planned) Auto-generate a team note

## Building

The compiler should be GCC to be able to use `bits/stdc++.h`.
We use CMake for building this project.

### Recommended

Use CMake Tools for VS Code.
Run `CMake: Configure` every time you add a new source file.

### CLI

```
CXX=/usr/local/bin/g++-9 cmake -S . -B build
cd build
make
```

Change `CXX=...` part to set the compiler in your local environment.

## TODO

### Algorithms to Add

#### Data Structure

- Dynamic segtree
- Union-find tree
- Sparse table
- Sqaure root decomposition + **Mo's Algorithm**

#### Graph

- **LCA**
- BCC
- HLD
- Euler tour

#### Math

- Floor sum

#### String

- **Trie**
- Rabin-Karp hashing
- Suffix array
