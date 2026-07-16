# Neuroforge — Engineering Manual for AI Assistants

## Project Identity

Neuroforge is a high-performance numerical computing engine built from first
principles in Modern C++23. It is a long-term educational and research-oriented
project and a vehicle for understanding systems programming,
performance engineering, numerical computing, linear algebra, low-latency
techniques, and reusable software infrastructure.

The project is educational, but it is guided by production-quality engineering
standards. Correctness precedes optimization. Machine learning is not the
foundation of Neuroforge; it is a future client of the numerical engine, as are
potential quantitative-computing extensions. The objective is engineering
excellence and documented understanding, not feature count.

## Hard Constraints

- Use C++23 only.
- Use the C++ standard library only unless an external dependency is explicitly
  approved.
- Do not use Eigen, Blaze, xtensor, Armadillo, BLAS, LAPACK, PyTorch,
  TensorFlow, OpenCV numerical utilities, or another numerical or ML library.
- Build mathematical, numerical, and ML primitives from first principles.
- Prefer RAII and value semantics; do not use raw owning pointers.
- Avoid unnecessary heap allocations, abstractions, and copies.
- Avoid premature optimization. Every optimization requires benchmark evidence.
- Do not silently redesign an existing API.
- Work on one bounded feature at a time.
- Do not prioritize rapid code generation over understanding.

## Engineering Philosophy

- Prefer zero-cost abstractions: express intent without hidden runtime cost.
- Start with the simplest correct and readable design.
- Measure before optimizing and retain the evidence for performance decisions.
- Build reusable, composable infrastructure rather than one-off solutions.
- Favor deterministic behavior wherever the problem permits it.
- Design clean, explicit APIs with clear ownership and error behavior.
- Optimize for long-term maintainability, reviewability, and learning value.

## Systems Programming Principles

- Prefer contiguous memory and make data layout a deliberate design choice.
- Consider cache locality, data movement, and allocation behavior in every
  performance-relevant design.
- Keep ownership, lifetime, and mutation explicit.
- Avoid hidden runtime cost, implicit allocation, and unnecessary indirection.
- Minimize copies without compromising clarity or correctness.
- Benchmark performance-critical code; do not infer performance from style.

## AI Development Workflow

For every feature, an AI assistant must:

1. Inspect the relevant project structure, code, and documentation.
2. Explain the relevant mathematics, when applicable.
3. Explain the required C++ concepts.
4. Explain relevant systems concepts, such as layout, ownership, concurrency, or cache behavior.
5. Propose a small, bounded API and implementation plan.
6. List every file to be created or modified.
7. Wait for explicit user approval.
8. Implement only the approved scope.
9. Add focused tests and build and run them.
10. Add benchmarks when performance is a stated requirement or affected concern.
11. Update module and decision documentation, then explain the implementation in educational detail.

Do not write or modify implementation code before approval unless the user
explicitly asks for implementation. Stop before starting the next roadmap item.

## Code Conventions

- Root namespace: `neuroforge`.
- Module namespaces follow `neuroforge::<module>` (for example,
  `neuroforge::math`). Keep nested namespaces purposeful and shallow.
- Public headers live in `include/<module>/`; implementation units live in
  `src/<module>/`; tests live in `tests/` and mirror public API layout.
- Use `snake_case.hpp` for headers and `snake_case.cpp` for implementation
  units. Use descriptive, stable names for public types and functions.
- Use simple template declarations such as `template<typename T>` until a
  stronger design is explicitly approved.
- Use contiguous row-major storage for matrix-like types unless an approved
  design documents a different layout.
- Include order: the corresponding project header, other project headers,
  standard-library headers, then third-party headers when approved.
- Apply const correctness consistently. Prefer `const` member functions and
  `const` references when mutation or ownership transfer is not intended.
- Use `noexcept` only when it is correct, meaningful, and does not obscure the
  API contract.
- Use `[[nodiscard]]` for values whose accidental discard can plausibly hide an
  error, failed operation, or important computed result.
- Use standard-library `assert` for tests until a testing framework is
  explicitly introduced.

## Template Policy

- Start with simple `template<typename T>`.
- Do not introduce CRTP, expression templates, heavy template metaprogramming,
  SFINAE, advanced concepts, policy classes, variadic templates, type traits,
  or template specialization without explicit approval.
- Numeric type constraints and C++20/23 concepts may be explored only after
  the foundational types they constrain are stable and explicitly approved.

## Numerical Comparison Policy

- Do not overload `operator==` with approximate floating-point semantics unless
  explicitly approved.
- Design numerical comparison through an explicit API, such as `is_close`, with
  documented absolute and relative tolerances.

## Benchmark Policy

Every optimization must follow this sequence:

```text
Baseline
  ↓
Benchmark
  ↓
Profile
  ↓
Optimize
  ↓
Benchmark Again
```

Never optimize without measurement. Benchmark methodology, inputs, environment,
and results belong in the benchmark and decision documentation when they inform
an engineering choice.

## Testing Policy

- Every module must include focused tests for its public behavior.
- No feature is complete without tests.
- Tests should cover normal behavior, boundary conditions, and documented error
  behavior relevant to the feature.
- Build and run the relevant tests before reporting completion.

## Documentation Policy

Every module must document:

- Purpose
- Architecture
- Design decisions
- Complexity
- Memory layout
- Future work
- Known limitations

Keep module-level documentation close to the module and record cross-cutting or
significant decisions in `docs/decisions.md`.

## Git Workflow

Use focused feature branches, such as:

- `feature/matrix`
- `feature/memory`
- `feature/runtime`
- `feature/numerical`
- `feature/benchmarks`
- `feature/ml`
- `feature/quant`

Before merging a feature branch, ensure that tests pass, documentation is
updated, and benchmarks are included when the change is performance-related.

## Commit Convention

Use concise, scoped commit prefixes:

- `docs:`
- `build:`
- `core:`
- `memory:`
- `math:`
- `runtime:`
- `bench:`
- `perf:`
- `test:`
- `refactor:`
- `ci:`

## Module Roadmap

### Current Module

| Module | Focus | Status |
| --- | --- | --- |
| Module 1 | Core Infrastructure | Current: repository, build, documentation, and engineering foundations |

### Future Modules

| Module | Focus |
| --- | --- |
| Module 2 | Memory Engine |
| Module 3 | Math Engine |
| Module 4 | Numerical Algorithms |
| Module 5 | Benchmark Suite |
| Module 6 | Runtime |
| Module 7 | Machine Learning |
| Module 8 | Quantitative Computing Extensions |

### Out-of-Scope Modules

Production deployment systems, hardware-specific backends, and additional
domain libraries are out of scope unless explicitly added to the roadmap. A
future module does not authorize implementation before its scope is approved.

## Never Do

Never:

- redesign APIs silently;
- introduce hidden allocations;
- optimize before benchmarks;
- add unnecessary abstractions;
- add dependencies without approval;
- implement multiple unrelated features in one change; or
- sacrifice readability for cleverness.

## Engineering Workflow

```text
Understand Mathematics
  ↓
Understand C++
  ↓
Understand Systems
  ↓
Design
  ↓
Implement
  ↓
Test
  ↓
Benchmark
  ↓
Profile
  ↓
Optimize
  ↓
Document
  ↓
Commit
```
