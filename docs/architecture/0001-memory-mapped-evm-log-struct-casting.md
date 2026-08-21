# 1. Memory-Mapped EVM Log Struct Casting

Date: 2026-07-12

## Status

Accepted

## Context

Monad executes transactions and emits Execution Events (EVM logs) at extreme throughput. Standard EVM event parsing relies on JSON-RPC or RLP decoding, which introduces massive string manipulation and serialization overhead, bottlenecking the HFT pipeline.

## Decision

We utilize **direct memory-mapped struct casting**.
- We bypass standard JSON/RLP interfaces and interface directly with the high-performance event emitter stream.
- We expect raw byte streams of packed event data.
- The incoming byte pointer is cast directly into our standardized C11 struct representing the EVM event log.

## Consequences

**Positive:**
- Eliminates serialization and deserialization overhead entirely, allowing the gateway to ingest Monad events at line rate.

**Negative (Mitigated):**
- This heavily couples our parsing logic to Monad's internal binary layout for Execution Events. 
- *Mitigation:* We shifted this fragility to compile-time generation. A build-time Python script (`generate_monad_parser.py`) automatically ingests the smart contract's ABI (`monad_abi.json`) and generates the exact C struct definitions (`abi_structs.h`) mapping the EVM log 256-bit data payloads. Any smart contract schema change now safely triggers a build pipeline update, preventing runtime failures.
