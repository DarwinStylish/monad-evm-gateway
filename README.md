# Monad EVM Gateway

Direct memory-mapped struct casting adapter for Monad Execution Events.

## Overview

This adapter parses raw Monad EVM log events (swap notifications) into the unified `event_t` struct used by the core execution engine. Price is calculated as `amount_out / amount_in` using pure integer fixed-point division — no floating-point arithmetic on the hot path.

## Features

- **Pure integer pricing**: `fixed_div()` with `__int128` intermediates, no `double` conversion
- **Zero-copy log parsing**: Direct struct cast from memory-mapped EVM log buffer
- **Division-by-zero guard**: Rejects events with `amount_in == 0`

## Integration

This module is consumed as a Git submodule by `hft_orchestrator`. All shared headers live in `hft_core/include`.

## Build & Test

```bash
make test
```

## License

Apache 2.0 — see the root [hft_orchestrator LICENSE](https://github.com/DarwinStylish/hft_orchestrator/blob/main/LICENSE).
