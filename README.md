# pslib

A collection of algorithms for use in programming competitions / online judges.

## Goal

- Easy to copy & paste (or type out in the contest environment with a printed team note)
- Unit tests as documentation
- (Planned) Auto-generate a team note

## Building

The compiler should be GCC to be able to use `bits/stdc++.h`.

### Recommended

Use CMake Tools for VS Code.

### CLI

```
CXX=/usr/local/bin/g++-9 cmake -S . -B build
cd build
make
```

Change `CXX=...` part to set the compiler in your local environment.
