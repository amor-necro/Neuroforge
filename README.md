<div align="center">

# Neuroforge

**A modern C++23 numerical computing framework, engineered from first principles.**

[![C++23](https://img.shields.io/badge/C%2B%2B-23-00599C?logo=cplusplus&logoColor=white)](https://en.cppreference.com/w/cpp/23)
[![Header-Only](https://img.shields.io/badge/library-header--only-informational)](#folder-structure)
[![Build System](https://img.shields.io/badge/build-CMake-064F8C?logo=cmake&logoColor=white)](https://cmake.org/)
[![License](https://img.shields.io/badge/license-MIT-green.svg)](LICENSE)
[![Version](https://img.shields.io/badge/version-v0.x-orange.svg)](#current-status)

</div>

---

## Table of Contents

1. [Overview](#overview)
2. [Features](#features)
3. [Architecture](#architecture)
4. [Folder Structure](#folder-structure)
5. [Current Status](#current-status)
6. [Installation](#installation)
7. [Quick Example](#quick-example)
8. [Philosophy](#philosophy)
9. [Engineering Principles](#engineering-principles)
10. [Roadmap](#roadmap)
11. [Project Goals](#project-goals)
12. [Future Ecosystem](#future-ecosystem)
13. [Contributing](#contributing)
14. [License](#license)

---

## Overview

Neuroforge is a modern C++23 numerical computing framework built completely from first principles. The objective is not simply to implement a set of mathematical algorithms, but to engineer an extensible numerical computing ecosystem — one where architecture, performance, correctness, and maintainability are treated as equally important design constraints from the outset.

Every component in Neuroforge is designed as part of a layered system: a `Matrix` container that owns no more responsibility than a container should, algorithms that operate on containers without owning memory, and memory and runtime systems that remain entirely ignorant of the mathematics running on top of them. The result is a codebase where each layer can be understood, tested, and reasoned about independently.

## Features

Neuroforge currently provides:

- A general-purpose `Matrix` container with value semantics and STL-consistent iteration
- Full Rule of Five compliance, with move semantics as the default path
- Element access via both linear and multi-dimensional indexing
- STL-style iterators supporting range-based iteration and standard algorithm interop
- Arithmetic operators (`+`, `-`, `*`, scalar operations) with well-defined, tested semantics
- Matrix multiplication with a straightforward, correctness-first implementation
- A unit test suite covering constructors, element access, iterators, and arithmetic
- Reference documentation for all public APIs
- A modern CMake build system with clean target-based configuration

Planned features are tracked in the [Roadmap](#roadmap) below and are not represented as complete.

## Architecture

Neuroforge is built in independent layers, with a small number of architectural rules enforced across the codebase:

- **Mathematical algorithms never own memory.** Algorithms operate on containers passed to them; they do not allocate, own, or manage storage themselves.
- **Memory systems never implement mathematics.** Allocators and memory utilities are generic and have no awareness of the mathematical types built on top of them.
- **Runtime systems never modify mathematical APIs.** Parallelism and scheduling are applied *around* mathematical code, never baked into its interface.
- **Every higher layer depends only on lower layers.** There are no upward or circular dependencies between layers.

```
Neuroforge
├── Core
├── Math
│      ├── Matrix
│      └── StaticMatrix          (future)
├── Linear Algebra
├── Numerical Computing
├── Statistics
├── Optimization
├── Random
├── Memory
│      ├── Alignment
│      ├── Arena Allocator
│      ├── Pool Allocator
│      └── Custom Allocators
├── Runtime
│      ├── Thread Pool
│      ├── Parallel Algorithms
│      └── Task Scheduler
├── SIMD Backend
└── Machine Learning Foundation
```

This layering is a design constraint, not a suggestion: pull requests that introduce a dependency from a lower layer to a higher one are considered architectural violations regardless of how small the change is.

## Folder Structure

```
neuroforge/
├── include/neuroforge/      # Public, header-only library headers
│   ├── core/                  # Core abstractions shared across the library
│   ├── math/                  # Matrix, StaticMatrix (future)
│   ├── linalg/                 # Linear algebra
│   ├── numeric/                 # Numerical computing
│   ├── stats/                   # Statistics
│   ├── optim/                    # Optimization
│   ├── random/                    # Random number generation
│   ├── memory/                     # Allocators, alignment utilities
│   ├── runtime/                     # Thread pool, parallel algorithms, scheduler
│   ├── simd/                         # SIMD backend
│   └── ml/                            # Machine learning foundation
├── src/                      # Implementation for any non-header-only components
├── tests/                    # Unit tests, mirroring include/ structure
├── benchmarks/               # Google Benchmark suites
├── examples/                 # Standalone usage examples
├── docs/                     # Design notes and API documentation
├── cmake/                    # CMake modules and helper scripts
├── scripts/                  # Developer and CI utility scripts
├── third_party/              # Vendored or fetched dependencies (kept minimal)
├── CMakeLists.txt
└── README.md
```

## Current Status

**Version:** v0.x — pre-release, active development.

| Component | Status |
|---|---|
| Matrix container | Complete |
| Constructors | Complete |
| Rule of Five | Complete |
| Element access | Complete |
| Iterators | Complete |
| Arithmetic operators | Complete |
| Matrix multiplication | Complete |
| Unit tests | Complete |
| Documentation | Complete |
| CMake build system | Complete |

Everything below the Matrix container in the [architecture](#architecture) diagram — linear algebra, numerical computing, statistics, optimization, memory systems, runtime, SIMD, and machine learning — is planned and not yet implemented. See the [Roadmap](#roadmap).

## Installation

### Prerequisites

- A C++23-capable compiler (recent GCC or Clang)
- CMake 3.25 or newer
- Ninja (recommended) or another CMake-supported generator

### Building from Source

```bash
git clone https://github.com/amor-eng/neuroforge.git
cd neuroforge

cmake -S . -B build -G Ninja -DCMAKE_BUILD_TYPE=Release
cmake --build build
```

### Running Tests

```bash
cd build
ctest --output-on-failure
```

### Using Neuroforge in Your Project

As a header-only library, Neuroforge can be consumed by adding `include/` to your project's include path:

```cmake
add_subdirectory(third_party/neuroforge)
target_link_libraries(your_target PRIVATE neuroforge::neuroforge)
```

An interface CMake target and install rules are provided so Neuroforge can be integrated via `add_subdirectory` or `find_package` once installed.

## Quick Example

```cpp
#include <neuroforge/math/matrix.hpp>

#include <iostream>

int main() {
    using neuroforge::Matrix;

    Matrix<double> a{2, 2, {1.0, 2.0,
                            3.0, 4.0}};

    Matrix<double> b{2, 2, {5.0, 6.0,
                            7.0, 8.0}};

    Matrix<double> c = a * b;   // matrix multiplication

    for (std::size_t row = 0; row < c.rows(); ++row) {
        for (std::size_t col = 0; col < c.cols(); ++col) {
            std::cout << c(row, col) << ' ';
        }
        std::cout << '\n';
    }

    return 0;
}
```

Additional, buildable examples are maintained in `examples/` and kept in sync with the current public API.

## Philosophy

Neuroforge is not intended to replace Eigen, Blaze, Armadillo, or xtensor — that is not a realistic or useful goal for a project at this stage, and no claim to the contrary is made anywhere in this repository. Those libraries represent years of accumulated engineering and are the right choice for production numerical work today.

Neuroforge is, instead, an educational and engineering journey toward building a production-quality numerical computing framework from first principles. Every abstraction — from the Matrix container's storage layout to the eventual SIMD backend — is implemented deliberately, so that the reasons behind each design decision are understood rather than inherited from an existing library's implementation.

## Engineering Principles

- **Modern C++23.** The codebase uses current language and standard library facilities as the default, not legacy idioms preserved for compatibility.
- **STL-style APIs.** Container and algorithm interfaces follow STL naming, iterator, and concept conventions wherever they apply.
- **RAII.** Resource lifetimes are always tied to object lifetimes; there are no manual acquire/release pairs in public APIs.
- **Strong exception safety.** Operations either complete fully or leave affected objects in their original state.
- **Header-only where appropriate.** Templates and performance-sensitive components remain header-only; this is relaxed only where compile-time cost or binary size genuinely requires it.
- **Performance without sacrificing readability.** Optimization is applied deliberately and measured, not embedded reflexively at the cost of clarity.
- **Extensive testing.** Every public component ships with a corresponding test suite before it is considered complete.
- **Incremental engineering.** Features are developed and merged in small, reviewable units, not large speculative rewrites.
- **First-principles implementation.** Algorithms are implemented and understood directly rather than wrapped around an existing library.

## Roadmap

| Phase | Focus | Status |
|---|---|---|
| 1 | Matrix Container | Complete |
| 2 | Linear Algebra | Planned |
| 3 | Numerical Computing | Planned |
| 4 | Statistics | Planned |
| 5 | Optimization | Planned |
| 6 | Memory Systems | Planned |
| 7 | Cache Optimization | Planned |
| 8 | SIMD | Planned |
| 9 | Parallel Runtime | Planned |
| 10 | Machine Learning Foundation | Planned |

Phases are developed sequentially where a genuine dependency exists (for example, Linear Algebra depends on the Matrix container), and are reordered only when a dependency analysis justifies it. Each phase is expected to ship with its own documentation, tests, and — once Phase 8 lands — benchmark coverage.

## Project Goals

Neuroforge's long-term goals include:

- High-performance linear algebra (decompositions, eigenvalue problems, solvers)
- A broader set of numerical algorithms (root finding, integration, interpolation)
- Memory optimization through custom allocators and arena-based strategies
- Cache-aware algorithm and data-layout design
- SIMD-accelerated numerical kernels
- Parallel execution via a first-party thread pool and task scheduler
- Support for quantitative finance workloads
- Machine learning primitives (tensors, automatic differentiation, layers, optimizers)

These are stated as directions, not commitments with fixed timelines. Each is only claimed as delivered once it appears as "Complete" in the [Roadmap](#roadmap).

## Future Ecosystem

Neuroforge is designed to serve as the mathematical backend for [Blazebook](https://github.com/amor-eng/blazebook), a separate project building low-latency trading infrastructure. In that role, Neuroforge is responsible for the numerical computing layer — matrix operations, linear algebra, and eventually statistics and optimization — while Blazebook builds the trading-specific systems (order book, matching engine, execution, risk) on top of it.

This separation is deliberate: Neuroforge remains a general-purpose numerical library with no trading-specific assumptions, and Blazebook remains free to evolve its domain logic independently of Neuroforge's internals.

## Contributing

Contributions are welcome, with the expectation that they respect the architectural rules described above.

To contribute:

1. Open an issue describing the proposed change before submitting a substantial pull request.
2. Respect the layering rules in [Architecture](#architecture) — no upward or circular dependencies between layers.
3. Include unit tests for any new or modified behavior.
4. Keep pull requests scoped to a single logical change.
5. Update relevant documentation in the same pull request as the code change.

Proposals that affect the public API or introduce a new architectural layer should be discussed in an issue before implementation begins.

## License

This project is licensed under the [MIT License](LICENSE) unless otherwise noted.

---

<div align="center">

**Neuroforge** — numerical computing, engineered from first principles.

</div>
