# Monad EVM Gateway


Direct memory-mapped struct casting adapter for Monad Execution Events.

## Overview

This adapter parses raw Monad EVM log events (swap notifications) into the unified `event_t` struct used by the core execution engine. Price is calculated as `amount_out / amount_in` using pure integer fixed-point division — no floating-point arithmetic on the hot path.

## Compiler Requirements
- **GCC**: >= 4.9 with C11 support.
- **Extensions**: `__int128` extension required (supported by GCC/Clang on x86-64 or aarch64).

## Features

- **Pure integer pricing**: `fixed_div()` with `__int128` intermediates, no `double` conversion
- **Zero-copy log parsing**: Direct struct cast from memory-mapped EVM log buffer
- **Division-by-zero guard**: Rejects events with `amount_in == 0`

## API Updates
Note: The adapter parser API has been updated. Calling the parsing methods now requires passing both the `buffer_len` and `seq_id` parameters to strictly enforce memory bounds and track exchange sequences. 

*Important Fix (CRIT-01): The previous double-scaling bug where price was scaled by SCALE² (10^16) instead of SCALE (10^8) has been resolved.*

## Integration

This module is consumed as a Git submodule by `hft_orchestrator`. All shared headers live in `hft_core/include`.

## Build & Test

```bash
make test
```

## Governance & Architecture

* **Code of Conduct:** Please review our [Code of Conduct](CODE_OF_CONDUCT.md).
* **Architecture Decision Records (ADRs):** 
  * [ADR-0001: Memory-Mapped EVM Log Struct Casting](docs/architecture/0001-memory-mapped-evm-log-struct-casting.md)
  * [ADR-0002: Use C11 for Gateway Performance](docs/architecture/0002-use-c11-for-gateway-performance.md)

## License

This project is licensed under the Apache License 2.0.
