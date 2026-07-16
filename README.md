# Neuroforge

> A high-performance numerical computing engine built from first principles in Modern C++23.

[![Build Status](https://img.shields.io/badge/build-pending-lightgrey)](#build-status)
[![License](https://img.shields.io/badge/license-pending-lightgrey)](#license)
[![C++](https://img.shields.io/badge/C%2B%2B-23-blue)](https://isocpp.org/)

Neuroforge is a long-term open-source systems project for building numerical computing infrastructure from scratch in modern C++23. It is a place to learn systems programming and performance engineering while developing reusable engineering components: memory-aware data structures, mathematical primitives, numerical algorithms, runtime facilities, and measurement tools. Machine learning is an important application of this foundation, not the definition of the project. The work emphasizes understanding how low-latency C++ techniques, clean interfaces, and empirical performance work together.

## Architecture

```text
Neuroforge
|
|-- Core
|   `-- Fundamental types, utilities, and project-wide facilities
|-- Memory Engine
|   `-- Allocation strategies and memory-management infrastructure
|-- Math Engine
|   `-- Matrices, tensors, and foundational mathematical operations
|-- Numerical Algorithms
|   `-- Linear algebra, reductions, and optimization-oriented algorithms
|-- Runtime
|   `-- Execution, scheduling, and concurrency facilities
|-- Benchmark Suite
|   `-- Repeatable performance measurement and regression tracking
|-- Machine Learning
|   `-- Models and training primitives built on the numerical engine
`-- Future Quant Extensions
    `-- Quantitative-computing components built on the shared foundation
```

The architecture above is the intended direction, not a claim that every subsystem exists today. The current work is focused on the core infrastructure, build, documentation, and engineering foundations required before numerical-engine implementation begins.

## Current Status

Neuroforge is in active early development. Module 1 establishes the project scaffold, build configuration, documentation, and public module boundaries. No numerical engine, matrix, tensor, runtime, or machine-learning implementation is currently provided. Broader subsystems are developed incrementally according to the roadmap.

## Design Philosophy

- **Performance first.** Design decisions should make data movement, allocation, and execution costs visible and measurable.
- **Modern C++23.** Use the current standard library and language facilities where they improve clarity, safety, or efficiency.
- **Zero-cost abstractions.** Prefer interfaces that express intent without imposing unnecessary runtime overhead.
- **RAII and value semantics.** Make ownership and resource lifetime explicit, safe, and local.
- **Benchmark-driven development.** Establish measurements before and after meaningful performance work.
- **Test-driven development.** Build confidence through focused, repeatable tests alongside each primitive.
- **Clean architecture.** Keep foundational layers independent, composable, and approachable to study.
- **Learn by building from first principles.** Implement the core machinery directly to understand its mathematical and systems-level trade-offs.

## Project Goals

### Current Goals

- Establish core project infrastructure and clear subsystem boundaries.
- Maintain a disciplined C++23 build, documentation, and test workflow.
- Document API choices, invariants, and performance trade-offs before implementation begins.
- Prepare the foundation for numerical primitives without external numerical or machine-learning libraries.

### Mid-term Goals

- Extend the math engine with linear algebra and practical numerical algorithms.
- Introduce reproducible benchmarks and performance-regression tracking.
- Build runtime facilities for structured concurrency and parallel execution.
- Provide the numerical infrastructure on which machine-learning components can be implemented cleanly.

### Long-term Vision

- Develop a cohesive, high-performance numerical computing engine suitable for experimentation and study.
- Demonstrate how modern C++ systems techniques apply to numerical software.
- Support machine learning and quantitative-computing extensions as clients of the core engine.
- Become a durable engineering record of decisions, measurements, and implementation trade-offs.

## Roadmap

The roadmap is directional. A version represents a bounded, tested capability rather than a release-date commitment.

| Version | Focus | Status |
| --- | --- | --- |
| v0.1 | Core Infrastructure | In progress |
| v0.2 | Memory Engine | Planned |
| v0.3 | Math Engine | Planned |
| v0.4 | Numerical Algorithms | Planned |
| v0.5 | Benchmark Suite | Planned |
| v0.6 | Runtime | Planned |
| v0.7 | Machine Learning | Planned |
| v0.8 | Performance Optimizations | Planned |
| v0.9 | Quantitative Computing Extensions | Planned |
| v1.0 | Stable Release | Planned |

## Repository Layout

```text
Neuroforge/
|-- cmake/                         Shared CMake modules
|-- docs/                          Architecture, roadmap, benchmarks, and decisions
|-- include/
|   |-- core/                      Public foundational APIs
|   |-- memory/                    Public memory-engine APIs
|   |-- math/                      Public mathematical APIs
|   |-- numerical/                 Public numerical-algorithm APIs
|   |-- runtime/                   Public runtime APIs
|   |-- ml/                        Public machine-learning APIs
|   `-- utils/                     Public supporting utilities
|-- src/
|   |-- core/                      Foundational implementation units
|   |-- memory/                    Memory-engine implementation units
|   |-- math/                      Mathematical implementation units
|   |-- numerical/                 Numerical-algorithm implementation units
|   |-- runtime/                   Runtime implementation units
|   |-- ml/                        Machine-learning implementation units
|   `-- utils/                     Supporting implementation units
|-- tests/                         Test sources
|-- benchmarks/                    Benchmark sources and measurement support
|-- examples/                      Small executable examples
|-- third_party/                   Vendored dependencies, when explicitly approved
|-- scripts/                       Development and automation scripts
|-- AGENTS.md                      Development workflow and project conventions
|-- CMakeLists.txt                 Top-level build configuration
|-- LICENSE                        MIT License
`-- README.md
```

## Build Status

Continuous integration has not yet been configured. The build-status badge will
be updated when a workflow is added.

### Requirements

- CMake 3.25 or newer
- A C++23-capable compiler: MSVC 19.3+, GCC 13+, or Clang 16+

### Build

```powershell
cmake -B build -DCMAKE_BUILD_TYPE=Debug
cmake --build build
```

### Run Tests

```powershell
ctest --test-dir build --output-on-failure
```

## Why Neuroforge?

Numerical software is where algorithms meet memory layout, compiler behavior, concurrency, and hardware constraints. Neuroforge treats those concerns as first-class engineering problems. Rather than hiding the foundation behind a large dependency stack, the project builds it deliberately and documents why each layer is shaped the way it is.

The result is intended to be useful both as a growing numerical foundation and as a practical study of modern C++ systems design.

## Future Directions

The following areas are under consideration and are not implemented unless explicitly identified in the current-status section:

- SIMD execution
- Custom allocators
- Thread pools
- Lock-free data structures
- Tensor engine
- Optimization algorithms
- Automatic differentiation
- Quantitative computing

## Contributing

Contributions are welcome as the project matures. Start by reading [AGENTS.md](AGENTS.md) for the development workflow, code conventions, and the feature-by-feature process used in this repository.

Good contributions are small, scoped, tested, and accompanied by a clear explanation of correctness and, where relevant, performance impact. Please avoid introducing external numerical or machine-learning libraries: the purpose of Neuroforge is to develop and understand the underlying infrastructure directly.

## Learning Journey

Neuroforge is not a collection of algorithm implementations in isolation. It is an engineering journal expressed in code: design choices, API boundaries, test cases, benchmarks, and the trade-offs that motivated them are part of the project.

Each component is an opportunity to examine how a mathematical idea becomes reliable, maintainable, and efficient C++ software. The goal is not merely to reproduce known algorithms, but to develop the judgment required to build numerical systems that endure.

## License

Neuroforge is distributed under the [MIT License](LICENSE).

Neuroforge is built patiently: one well-understood, well-tested, and well-measured layer at a time.
