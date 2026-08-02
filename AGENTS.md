# Neuroforge Engineering Constitution

This document is binding. It applies to every AI coding agent — Claude, ChatGPT, Kilo, Copilot, or any other automated contributor — operating on this repository. It is not a contributor guide, and it is not optional guidance: it is the set of constraints under which all automated changes to Neuroforge are made.

If any instruction given to an agent in a specific task conflicts with this document, this document takes precedence unless a human maintainer explicitly overrides it in writing for that task.

---

## Project Vision

Neuroforge is a modern C++23 numerical computing library built completely from first principles. The long-term objective is to become a high-performance alternative to Eigen and Blaze — but that objective is subordinate to, not a substitute for, correctness, readability, and engineering quality.

Performance is a goal Neuroforge earns over time, not a shortcut it takes early. An agent that trades correctness or clarity for speed, at any stage of this project, has misunderstood the assignment.

---

## Development Philosophy

Every change to Neuroforge is evaluated against a strict, ordered set of priorities. A lower priority is never pursued at the expense of a higher one.

```
Correctness
    ↓
Clean API Design
    ↓
Testing
    ↓
Documentation
    ↓
Optimization
    ↓
Memory Optimization
    ↓
Cache Optimization
    ↓
SIMD
    ↓
Parallelism
    ↓
Low Latency
```

Never optimize prematurely. If a task description asks an agent to optimize something before its correctness, API, tests, and documentation are settled, the agent should complete those first and flag the ordering, rather than optimize out of sequence.

---

## Coding Standards

All code written or modified by an agent must conform to the following:

- **C++23 only.** No legacy idioms where a modern equivalent exists; no reliance on pre-C++23 workarounds.
- **STL only.** No third-party dependencies for functionality the STL already provides.
- **No raw owning pointers.** Ownership is expressed through RAII types (`std::unique_ptr`, `std::shared_ptr`, containers, value types) — never a raw pointer that owns a resource.
- **Prefer RAII.** Every resource's lifetime is tied to an object's lifetime.
- **Rule of Five.** Any type managing a resource explicitly defines or explicitly deletes all five special member functions.
- **Templates.** Generic code is written with templates, following STL conventions for template parameter naming and constraints.
- **Exception safety.** At minimum, the strong exception safety guarantee for operations where it is achievable; never leave an object in a half-modified state on failure.
- **Const correctness.** `const` is applied everywhere it is semantically correct, with no exceptions for convenience.
- **`[[nodiscard]]` where appropriate.** Applied to any function whose return value must not be silently discarded (factory functions, query functions, error-carrying returns).
- **`noexcept` only when correct.** Never applied speculatively; only when the function genuinely cannot throw.
- **Row-major storage.** All matrix and container storage layouts follow row-major order unless a specific module documents and justifies an exception.
- **No macros unless necessary.** Macros are a last resort, used only where the language provides no alternative (e.g., certain portability concerns).
- **No comments unless requested.** Code should be self-explanatory through naming and structure; comments are added only when a human maintainer or task explicitly asks for them, or when a genuinely non-obvious invariant must be recorded.
- **Header/implementation separation.** Template implementations are separated using `.hpp`/`.tpp` pairs, keeping public interfaces readable independent of their implementation detail.

---

## Repository Structure

| Directory | Purpose |
|---|---|
| `include/` | Public, header-only library headers. This is the library's public API surface — anything here is a contract with users. |
| `src/` | Implementation for any components that are not header-only. |
| `tests/` | Unit tests, mirroring the structure of `include/`. Every public component has a corresponding test file. |
| `docs/` | Design notes, API documentation, and sprint records. |
| `examples/` | Standalone, buildable usage examples kept in sync with the current public API. |
| `benchmarks/` | Benchmark suites, introduced once a component reaches the optimization stages of the [Development Philosophy](#development-philosophy). |
| `cmake/` | CMake modules and build configuration helpers. |

An agent should not introduce new top-level directories without explicit instruction — new functionality is placed within the existing structure unless a maintainer directs otherwise.

---

## API Design Rules

Every new public API must satisfy all of the following before it is considered complete:

- **Simple.** The smallest interface that solves the problem, not the most general one that could conceivably solve it.
- **Predictable.** Behavior follows from the name and signature without needing to read the implementation.
- **STL-like.** Naming, iterator conventions, and semantics follow established STL patterns wherever they apply.
- **Consistent naming.** New APIs follow the naming conventions already established elsewhere in the codebase.
- **Minimal surprise.** No hidden allocations, no unexpected ownership transfers, no behavior that a reasonable caller would not anticipate from the signature.
- **Future SIMD-friendly.** Data layout and access patterns do not foreclose a future SIMD backend.
- **Future cache-friendly.** Layout decisions consider cache behavior even before cache optimization is the active roadmap phase.

Implementation details are never exposed through the public API. If an agent finds itself exposing an internal type, storage detail, or algorithm choice to satisfy a task, it should stop and raise the design question rather than proceed.

---

## Testing Policy

A feature is not complete until it has passed through every stage below, in order:

1. **API** — the public interface is designed and reviewed against the [API Design Rules](#api-design-rules).
2. **Implementation** — the feature is implemented against that API.
3. **Unit Tests** — tests are written covering the feature's behavior, including edge cases and failure modes.
4. **Build** — the project builds cleanly, without new warnings, on the supported compilers.
5. **CTest** — the full test suite passes via CTest, not just the tests for the new feature.
6. **Review** — the change is reviewed against this document before being considered done.

No feature is complete until its tests pass. An agent must never report a task as finished while tests are failing, skipped, or not yet written.

---

## Review Policy

Every completed sprint is reviewed against the following, regardless of how small the sprint's scope was:

- **Build review** — does the project build cleanly on all supported compilers?
- **API review** — does every new or changed API satisfy the [API Design Rules](#api-design-rules)?
- **Performance review** — has any performance-relevant change been measured, not assumed?
- **Exception safety review** — does every operation uphold its stated exception safety guarantee?
- **Const correctness review** — is `const` applied everywhere it should be?
- **Modern C++ review** — does the code use C++23 idioms rather than legacy patterns?
- **Final PR review** — does the change, as a whole, belong in this sprint and this sprint only?

An agent completing a sprint should walk through this list explicitly before declaring the sprint done.

---

## Git Workflow

All work follows this sequence, without exception:

```
Feature
   ↓
Build
   ↓
CTest
   ↓
Review
   ↓
Commit
   ↓
Push
```

Never commit code that does not build. Never push code that fails tests. If an agent cannot get a change to build or pass tests within the scope of its current task, it should stop and report the failure rather than commit around it.

---

## Roadmap

The current roadmap, in sprint order:

| Sprint | Scope |
|---|---|
| 1 | Constructors |
| 2 | Rule of Five |
| 3 | Element Access |
| 4 | Container Utilities |
| 5 | Scalar Operators |
| 6 | Comparison Operators |
| 7 | Arithmetic Operators |
| 8 | Matrix Multiplication, Unary Minus, Transpose, Identity, Zeros, Ones, Constant Matrix |
| 9 | Views, Row APIs, Column APIs, Block APIs |
| 10 | Matrix API Freeze |
| 11 | Linear Algebra |

Beyond Sprint 11, the roadmap moves into the later stages of the [Development Philosophy](#development-philosophy):

```
Memory Optimization
      ↓
Cache Optimization
      ↓
SIMD
      ↓
Parallelism
      ↓
Low Latency
```

This roadmap is the authoritative source of what an agent should be working on. Any task that does not map to the current sprint should be treated as out of scope unless a maintainer explicitly says otherwise.

---

## AI Agent Rules

Every AI agent operating on this repository must:

- Never rewrite unrelated code.
- Never refactor outside the current sprint.
- Never introduce external libraries.
- Never optimize prematurely.
- Never skip tests.
- Never change public APIs without explanation.
- Never silently modify formatting rules.
- Never change CMake configuration unless required by the current task.
- Never modify the roadmap without explicit maintainer approval.

Every AI agent operating on this repository must always:

- Finish one sprint before starting another.
- Explain engineering decisions — a change without a stated rationale is treated as incomplete.
- Preserve backward compatibility unless explicitly instructed otherwise.

These rules exist because an agent working faster than a human reviewer can verify is a liability, not an asset, unless it is constrained to move in small, explainable, reversible steps.

---

## Design Principle

Neuroforge is being built to teach engineering, not only to produce code. Every implementation should maximize clarity, maintainability, and future extensibility over raw expedience.

The repository is intended to eventually serve as a learning resource for developers interested in numerical computing, modern C++, library design, and high-performance computing. Every agent contributing to it — human or automated — is contributing to that resource, and is held to the standard that implies: code here should be worth reading, not just worth running.