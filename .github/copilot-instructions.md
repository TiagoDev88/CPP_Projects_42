# Copilot Coding Agent Instructions - CPP Projects 42

## Repository Overview

This repository contains C++ learning exercises from the 42 school curriculum. The project consists of multiple C++ modules (CPP_00, CPP_01) with individual exercises focusing on progressive C++ concepts, from basic syntax to memory management and object-oriented programming.

**Project Type**: Educational C++ exercises  
**Languages**: C++ (C++98 standard)  
**Repository Size**: Small (~13 directories, multiple exercises)  
**Build System**: GNU Make with individual Makefiles per exercise

## Repository Structure

### High-Level Layout
```
CPP_Projects_42/
├── .gitignore           # Standard C++ artifacts (*.o, executables, etc.)
├── README.md            # General project overview
├── CPP_00/              # Module 0: Basic C++ concepts
│   ├── ex00/            # Exercise 00: Megaphone (basic I/O)
│   ├── ex01/            # Exercise 01: PhoneBook (classes, members)
│   ├── ex02/            # Exercise 02: Account (output validation with log)
│   └── notas            # Notes file (Portuguese)
└── CPP_01/              # Module 1: Memory, pointers, references
    ├── ex00/            # Exercise 00: Zombie (heap vs stack)
    ├── ex01/            # Exercise 01: Zombie Horde (arrays)
    ├── ex02/            # Exercise 02: Brain (pointers/references)
    ├── ex03/            # Exercise 03: Weapon (references)
    ├── ex04/            # Exercise 04: SedIsForLosers (file manipulation)
    ├── ex05/            # Exercise 05: (notes only - not implemented)
    └── ex06/            # Exercise 06: (notes only - not implemented)
```

### Exercise Structure Pattern
Each exercise directory contains:
- **Makefile**: Build configuration with standard targets
- **Source files**: `*.cpp` implementation files
- **Header files**: `*.hpp` or `*.h` interface definitions
- **notas**: Exercise requirements (in Portuguese, optional reading)
- **Executable**: Named after the project (e.g., `megaphone`, `PhoneBook`, `Zombie`)

**Note**: `notas` files contain the original 42 exercise descriptions but are NOT required for building. They are developer notes only.

## Build Instructions

### Prerequisites
- **Compiler**: `c++` (GCC/Clang C++ compiler) - Tested with GCC 13.3.0
- **Build Tool**: GNU Make 4.3+
- **Standard**: C++98 (`-std=c++98` flag)
- **Required Flags**: `-Wall -Wextra -Werror` (most exercises; ex04 has flags commented out but still compiles)

### Building Individual Exercises

**ALWAYS** navigate to the specific exercise directory before running make commands.

```bash
cd CPP_00/ex00  # or any exercise directory with a Makefile
make            # Builds the exercise
```

### Standard Makefile Targets

All Makefiles follow this consistent pattern:

1. **`make` or `make all`**: Compiles source files and links the executable
   - Creates object files (`*.o`)
   - Links to final executable
   - Compilation time: < 5 seconds per exercise

2. **`make clean`**: Removes object files only
   - Keeps the executable
   - Use when you want to recompile but keep the binary

3. **`make fclean`**: Removes object files AND executable
   - Complete cleanup
   - **ALWAYS run before rebuilding from scratch**

4. **`make re`**: Equivalent to `make fclean && make`
   - Full rebuild from clean state
   - Use after significant changes

### Build Process Order

**IMPORTANT**: When making code changes:

1. **ALWAYS clean before building**: `make fclean`
2. Then build: `make`
3. Do NOT rely on incremental builds - they may not detect all changes

Example workflow:
```bash
cd CPP_00/ex01
make fclean && make    # Clean build
./PhoneBook            # Run the program
```

### Makefile Variable Inconsistency

**WARNING**: There is an inconsistency in Makefile variable names:
- **CPP_00 exercises**: Use `CXX = c++` (correct for C++)
- **CPP_01 exercises**: Use `CC = c++` (technically incorrect but works)
- Both resolve to the same compiler in practice

**When editing Makefiles**: Follow the existing convention in that module, but prefer `CXX` for new code.

### Compiler Flags Note

Most exercises use: `-Wall -Wextra -Werror -std=c++98`

**Exception**: `CPP_01/ex04/Makefile` has `-Wall -Wextra -Werror` commented out and only uses `-std=c++98`. This appears intentional and the code compiles successfully. Do NOT add the strict flags back unless fixing specific warnings.

## Testing and Validation

### No Automated Test Suite
This repository does NOT have:
- Unit tests
- Integration tests  
- Test scripts
- CI/CD pipelines

### Manual Validation

**Run each executable** after building to verify behavior:

```bash
# Example: CPP_00/ex00
cd CPP_00/ex00
make fclean && make
./megaphone "test message"    # Should output: TEST MESSAGE
./megaphone                   # Should output: * LOUD AND UNBEARABLE FEEDBACK NOISE *
```

### Special Case: CPP_00/ex02 (Account/Bank)

This exercise includes output validation:

**Reference log file**: `CPP_00/ex02/19920104_091532.log`  
This is the expected output format (with different timestamp).

**To verify**:
```bash
cd CPP_00/ex02
make fclean && make
./Bank > output.log 2>&1
# Compare structure (ignore timestamps):
diff -u <(cut -d']' -f2- 19920104_091532.log) <(cut -d']' -f2- output.log)
```

The output should match in structure but have current timestamps instead of `[19920104_091532]`.

## Code Patterns and Conventions

### Header Guards
All header files use include guards:
```cpp
#ifndef CLASSNAME_HPP
# define CLASSNAME_HPP
// content
#endif
```

### Class Naming
- PascalCase for class names: `PhoneBook`, `Zombie`, `Contact`
- Private members prefixed with underscore: `_name`, `_count_contacts`

### File Naming
- Headers: `ClassName.hpp` (preferred) or `.h`
- Implementation: `ClassName.cpp`
- Main files: `main.cpp`
- Utility functions: Named descriptively (`newZombie.cpp`, `randomChump.cpp`)

### Memory Management Patterns
- Exercises focus on understanding stack vs heap allocation
- Destructors print debug messages (e.g., "X has been destroyed")
- Constructors may print creation messages

### Standard Library Usage
- `#include <iostream>` for I/O
- `#include <string>` for std::string
- `#include <vector>` and algorithms where needed
- Prefer C++ standard library over C equivalents

## Common Build Issues and Solutions

### Issue: "No such file or directory" when building
**Cause**: Running make from wrong directory  
**Solution**: ALWAYS `cd` into the exercise directory (e.g., `cd CPP_00/ex00`) before running `make`

### Issue: Object files not updating after code changes
**Cause**: Make's dependency tracking may miss changes  
**Solution**: ALWAYS run `make fclean` before `make` when you've modified source code

### Issue: Executable already exists but won't rebuild
**Cause**: Make thinks target is up-to-date  
**Solution**: Use `make re` or `make fclean && make`

### Issue: Compiler not found
**Cause**: No C++ compiler installed  
**Solution**: Install GCC (`g++`) or Clang (`clang++`). The `c++` command should symlink to one of these.

## Git Workflow

### Tracked Files
- Source files: `*.cpp`, `*.hpp`, `*.h`
- Build files: `Makefile`
- Documentation: `README.md`, `notas` files
- Reference files: `*.log` (in ex02), `teste.txt` (in ex04)

### Ignored Files (per .gitignore)
- Object files: `*.o`, `*.obj`, `*.lo`, `*.slo`
- Executables: `*.exe`, `*.out`, `*.app`
- Libraries: `*.a`, `*.so`, `*.dylib`, `*.dll`
- Dependency files: `*.d`
- Precompiled headers: `*.gch`, `*.pch`
- Debug info: `*.pdb`, `*.dwo`

**Important**: Built executables (without extensions) ARE tracked by git in this repo. This is intentional for the project structure but unusual. When cleaning, `make fclean` removes them.

## Key Files Reference

### Root Level
- `.gitignore`: Standard C++ artifact exclusions
- `README.md`: Basic module overview and usage instructions

### CPP_00 (Namespaces, classes, member functions, streams)
- `ex00/megaphone.cpp`: Single-file program, string manipulation
- `ex01/PhoneBook.{hpp,cpp}`: Main class with contact array, menu system
- `ex01/Contact.{hpp,cpp}`: Contact data class
- `ex01/Utils.{hpp,cpp}`: Helper functions
- `ex02/Account.{hpp,cpp}`: Banking account class with timestamp logging
- `ex02/tests.cpp`: Test driver using STL containers and algorithms
- `ex02/19920104_091532.log`: **Expected output format** for validation

### CPP_01 (Memory allocation, pointers, references)
- `ex00/Zombie.{hpp,cpp}`: Basic class with heap/stack allocation comparison
- `ex00/newZombie.cpp`, `randomChump.cpp`: Allocation demonstration functions
- `ex01/zombieHorde.cpp`: Dynamic array allocation
- `ex02/main.cpp`: Pointer and reference demonstration
- `ex03/Weapon.{hpp,cpp}`, `HumanA.{hpp,cpp}`, `HumanB.{hpp,cpp}`: Reference semantics
- `ex04/Replace.{hpp,cpp}`: String replacement (sed alternative)
- `ex04/teste.txt`: Sample input file for testing

## Executables Generated

After building, each exercise produces one executable:

| Exercise | Executable Name | Purpose |
|----------|----------------|---------|
| CPP_00/ex00 | `megaphone` | String to uppercase |
| CPP_00/ex01 | `PhoneBook` | Interactive phonebook |
| CPP_00/ex02 | `Bank` | Account operations with logging |
| CPP_01/ex00 | `Zombie` | Stack vs heap allocation |
| CPP_01/ex01 | `ZombieHorde` | Dynamic array demo |
| CPP_01/ex02 | `Brain` | Pointer/reference demo |
| CPP_01/ex03 | `Weapon` | Reference semantics |
| CPP_01/ex04 | `SedIsForLosers` | File string replacement |

## Development Workflow Summary

1. **Navigate to exercise directory**: `cd CPP_XX/exYY`
2. **Clean previous build**: `make fclean`
3. **Build**: `make`
4. **Test**: `./ExecutableName [arguments]`
5. **Iterate**: Make code changes, repeat from step 2

## Important Notes for Coding Agents

1. **Trust these build instructions**: The commands listed here have been validated. Only search for additional information if these instructions are incomplete or incorrect.

2. **No global build**: There is no top-level Makefile. Each exercise is independent and must be built separately.

3. **No test automation**: Validation is manual. Run executables and verify output matches expected behavior.

4. **C++98 compliance required**: Do NOT use C++11 or later features (no `auto`, range-based for loops, lambdas, `nullptr`, etc.).

5. **Compiler warnings are errors**: The `-Werror` flag treats warnings as errors. Code must compile cleanly (except ex04 which intentionally has relaxed flags).

6. **Exercise independence**: Exercises don't depend on each other. You can work on any exercise without building others.

7. **Notas files**: Can be ignored for building purposes. They contain Portuguese exercise descriptions from 42 school.

8. **Module progression**: CPP_00 is more basic than CPP_01. When making changes, respect the educational progression (don't add advanced features to early exercises).

9. **File preservation**: Do NOT delete or significantly alter `tests.cpp` files or reference logs - these are provided as-is by the curriculum.

10. **Quick validation**: After any change, run `make fclean && make` in the affected exercise directory to ensure it still compiles.
