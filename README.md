# Enigma

Parallel Enigma machine decryption — High Performance Computing university project.

Two implementations of the same brute-force Enigma rotor key search, benchmarked
against each other: a sequential/OpenMP baseline and a distributed MPI master-slave
version.

---

## What this is

The **Enigma machine** encrypts text by passing characters through a series of rotors.
This project **decrypts** an unknown ciphertext by exhaustively testing all possible
rotor key combinations until the deciphered output is recognisable.

Two versions are compared:

| Version | Directory | Parallelism |
|---|---|---|
| Sequential | `Version_Sequential/` | OpenMP (shared memory) |
| Master-Slave | `Version_Master-Slave/` | MPI (distributed memory) |

A helper program (`Stats.cpp`) reads the timing files written by both versions and
prints a summary of the average execution time across repeated runs.

---

## Repository Structure

```
Enigma/
├── Version_Sequential/
│   ├── Enigma.cpp      # Sequential/OpenMP brute-force decryption
│   ├── Makefile
│   ├── Times.txt       # Benchmark timing output
│   └── mulExec.sh      # Run multiple timed executions
├── Version_Master-Slave/
│   ├── Master.cpp      # MPI master process — distributes lines to workers
│   ├── Slave.cpp       # MPI slave process — tests rotor keys for one line
│   ├── Makefile
│   ├── Times.txt       # Benchmark timing output
│   └── mulExec.sh      # Run multiple timed executions via mpirun
├── Stats.cpp           # Reads both Times.txt files and prints averages
└── Makefile            # Builds and runs both versions, then prints summary
```

---

## Building and Running

### Prerequisites

- GCC with OpenMP support (`g++ -fopenmp`)
- MPI implementation (e.g. OpenMPI): `mpicc`, `mpirun`

### Run everything

```bash
make
```

This will:
1. Compile `Stats.cpp` → `stats_exec`
2. Build and run `Version_Sequential/` (5 timed executions via `mulExec.sh`)
3. Build and run `Version_Master-Slave/` (5 timed executions via `mpirun`)
4. Print timing averages from both `Times.txt` files

### Run a version individually

```bash
# Sequential
cd Version_Sequential && make

# Master-Slave (adjust -np to match your core count)
cd Version_Master-Slave && make
```

### Run multiple times for benchmarking

```bash
cd Version_Sequential && bash mulExec.sh
cd Version_Master-Slave && bash mulExec.sh
```

---

## How the decryption works

Each ciphertext line is an array of integers. The algorithm:

1. Iterates over all possible starting rotor key values.
2. For each candidate key, applies the inverse Enigma transformation to every
   character in the line.
3. Checks whether the deciphered output falls within the printable ASCII range.
4. When a valid decryption is found, records the key and outputs the plaintext.

### Test cases

Four pre-defined ciphertext configurations are available in the source (`CASE 1`–`CASE 4`),
varying the number of lines, characters per line, and number of rotors:

| Case | Lines | Chars/line | Rotors | Status |
|------|-------|-----------|--------|--------|
| 1 | 9 | 33 | 2 | commented out |
| 2 | 8 | 93 | 5 | commented out |
| **3** | **23** | **138** | **5** | **active** |
| 4 | 51 | 155 | 8 | commented out |

Switch the active case by commenting/uncommenting the corresponding `#define` blocks
at the top of `Enigma.cpp` / `Master.cpp`.

### MPI Master-Slave distribution

The master process (PID 0):
- Broadcasts configuration arguments (chars per line, rotor count) to all slaves.
- Assigns one ciphertext line per slave in a work-queue loop.
- Collects deciphered results and writes them back to the output array.
- Sends a `TAG_STOP` signal once all lines are processed.

Each slave process:
- Receives its assigned line index and ciphertext data.
- Runs the brute-force key search independently.
- Returns the deciphered line and its index to the master.

---

## Tech stack

| Technology | Role |
|---|---|
| C++ | Implementation language |
| MPI (OpenMPI) | Distributed memory parallelism (Master-Slave version) |
| OpenMP | Shared memory parallelism (Sequential version) |
| `omp_get_wtime()` | Wall-clock benchmarking |

---

## Course context

Built for the *High Performance Computing* (Computación de Altas Prestaciones) course.
The goal was to compare distributed-memory (MPI) parallelism against shared-memory (OpenMP)
on a real algorithm, measure wall-clock speedup, and reason about communication overhead.
