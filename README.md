# Awesome Math-inator

**Awesome Math-inator** is a command-line calculator written in C. It provides basic arithmetic, powers, logarithms, square roots, factorials, trigonometric functions, and basic statistical operations through a simple command-based interface.

> "It's not evil; it's just misunderstood math!" — Dr. Doofenshmirtz

## Features

* Basic arithmetic: addition, subtraction, multiplication, division, and remainder
* Exponent and logarithm calculations
* Square root and factorial
* Trigonometric functions:
  * Sine
  * Cosine
  * Tangent
  * Cotangent
  * Secant
  * Cosecant
* Statistical calculations:
  * Mean
  * Median
  * Mode
  * Variance
  * Standard deviation
* Command-line argument parsing with input validation
* Trigonometric calculations support both degrees and radians
* Informative error messages for invalid or mathematically undefined operations
* Cross-platform Makefile for Linux and Windows/MinGW builds

## Usage

Math-inator uses a **command-based CLI**. Instead of navigating numbered menus, provide the operation and its operands directly as command-line arguments.

### General Syntax

```text
mathinator <command> <arguments>
```

For example:

```bash
mathinator add 10 20
```

Output:

```text
mathinator: 30
```

If no command is provided, Math-inator displays the general usage format.

---

## Command Reference

### Arithmetic

| Command     | Syntax                           | Example                     |
| ----------- | -------------------------------- | --------------------------- |
| `add`       | `mathinator add <n1> <n2>`       | `mathinator add 10 5`       |
| `subtract`  | `mathinator subtract <n1> <n2>`  | `mathinator subtract 10 5`  |
| `multiply`  | `mathinator multiply <n1> <n2>`  | `mathinator multiply 10 5`  |
| `divide`    | `mathinator divide <n1> <n2>`    | `mathinator divide 10 5`    |
| `remainder` | `mathinator remainder <n1> <n2>` | `mathinator remainder 10 3` |

### Advanced Mathematical Operations

| Command     | Syntax                               | Example                  |
| ----------- | ------------------------------------ | ------------------------ |
| `power`     | `mathinator power <base> <exponent>` | `mathinator power 2 8`   |
| `log`       | `mathinator log <number> <base>`     | `mathinator log 8 2`     |
| `sqroot`    | `mathinator sqroot <number>`         | `mathinator sqroot 25`   |
| `factorial` | `mathinator factorial <number>`      | `mathinator factorial 5` |

### Trigonometry

The available trigonometric commands are:
* `sin`
* `cos`
* `tan`
* `cot`
* `sec`
* `cosec`

Syntax:

```text
mathinator <function> <angle> [--deg|--rad]
```

Examples:

```bash
mathinator sin 90
mathinator sin 90 --deg
mathinator sin 1.57079632679 --rad
```

**Angle behavior:**
* If no flag is supplied, the angle is interpreted as **degrees**.
* `--deg` explicitly specifies degrees.
* `--rad` specifies radians.

For example:

```bash
mathinator cos 60
```
is equivalent to:
```bash
mathinator cos 60 --deg
```

while:
```bash
mathinator cos 1.0471975512 --rad
```
interprets the input directly as radians.

---

## Statistics

Statistical operations accept a dataset directly through command-line arguments.

Available commands:
* `mean`
* `median`
* `mode`
* `variance`
* `stddev`

Syntax:

```text
mathinator <operation> <n1> <n2> ... <n20>
```

Examples:

```bash
mathinator mean 10 20 30 40 50
```

```bash
mathinator median 5 2 9 4 7
```

```bash
mathinator mode 1 2 2 3 4 2 5
```

```bash
mathinator variance 10 12 15 13 20
```

```bash
mathinator stddev 10 12 15 13 20
```

The current CLI accepts a maximum of **20 dataset elements per statistical operation**.

---

## Input and Error Handling

Math-inator parses numeric arguments as `double` values and rejects arguments that cannot be completely converted to valid numbers.

For example:

```bash
mathinator add 10 abc
```
results in an invalid-input error rather than attempting to perform the calculation.

Math-inator also distinguishes between:
* **Invalid input** — incorrect command syntax, operand count, or non-numeric input
* **Undefined results** — mathematically undefined operations
* **Out-of-range results** — results exceeding the representable `double` range

Successful calculations are printed using the following format:

```text
mathinator: <result>
```

---

## Building

Math-inator uses a Makefile and GCC-compatible C compilation.

### Release Build

The default target produces an optimized release build:

```bash
make
```

or:

```bash
make release
```

The executable is placed in:

```text
build/release/
```

### Debug Build

To build with debugging symbols and no optimization:

```bash
make debug
```

The executable is placed in:

```text
build/debug/
```

### Clean Build Artifacts

```bash
make clean
```

### Show Available Make Targets

```bash
make help
```

### Windows

The Makefile supports Windows builds using **MinGW/mingw32-make**:

```bash
mingw32-make
```

```bash
mingw32-make debug
```

The resulting executable uses the `.exe` extension.

---

## Project Structure

```text
Math-inator/
├── build/
│   ├── debug/            # Debug build output
│   └── release/          # Release build output
├── include/
│   ├── core/
│   │   ├── types.h
│   │   └── math_constants.h
│   ├── cli/
│   │   ├── parser.h
│   │   └── history.h
│   └── math/
│       ├── arithmetic.h
│       ├── trigo.h
│       └── stats.h
├── src/
│   ├── main.c
│   ├── core/
│   │   └── types.c
│   ├── cli/
│   │   ├── parser.c
│   │   └── history.c
│   └── math/
│       ├── arithmetic.c
│       ├── trigo.c
│       └── stats.c
├── .gitignore
├── Makefile
└── README.md
```

The CLI entry point is intentionally kept thin: `main.c` delegates command parsing and dispatch to the CLI parser, while the mathematical operations are organized separately under `src/math/`.

---

## Development Status

This project is under active development — see [Issues](https://github.com/PriyanshAgrl/Math-inator/issues) for known limitations and planned features.

---

Thank you for using the **Awesome Math-inator**!
