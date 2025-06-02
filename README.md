# C- Compiler Project

This repository contains a compiler implementation for a simplified programming language named **C Minus (`C-`)**. The compiler is capable of generating intermediate code, assembly code, and binary code from C- source code.

The project is a part of a broader initiative at the **Federal University of São Paulo (UNIFESP)** aiming to create a comprehensive computational system, encompassing:

1. [MIPS Processor](https://github.com/EduardoVeri/MIPS-Processor)
2. [Assembler](https://github.com/EduardoVeri/Assembler-Mips)
3. [Compiler (Current Project)](https://github.com/EduardoVeri/Compilador)
4. [Operating System](https://github.com/EduardoVeri/Assembler-Mips/tree/main/OS_project)

---

## About This Project

The compiler was developed using the **C programming language**, with:

- **Flex** for lexical analysis (lexer).
- **Bison** for syntax analysis (parser).

The generated assembly and binary code follow a simplified MIPS architecture, also developed in the context of this initiative. Refer to the [MIPS project repository](https://github.com/EduardoVeri/MIPS-Processor) for details.

- **Analysis Phase**: Completed as a final project for the **Compilers course (2022)**, supervised by Prof. Dr. Luis Augusto Martins Pereira.
- **Synthesis Phase**: Developed as the final project for the **Compilers Laboratory course (2023)**, supervised by Prof. Dra. Thaina Aparecida Azevedo Tosta.

---

## Project Report

A detailed project report is available in the `docs` folder. This report includes comprehensive documentation about the compiler's architecture, the methodologies employed, experimental results, and analysis of the implementation process. Available in Portuguese (PT-BR) only.

📖 Click [here](./docs/report-LabComp.pdf) to access the report.

---

## Compilation Steps

The project uses **CMake** by default. Follow the instructions below to compile the compiler:

### 1. Install Dependencies

On Ubuntu, install CMake with:

```sh
sudo apt-get install cmake
```

> [!TIP]
> You can enable compiler warnings with `-DSHOW_WARNINGS=ON` for additional diagnostic messages.

### 2. Compile with CMake

```sh
mkdir -p build
cmake -B ./build [-DSHOW_WARNINGS=ON]
cmake --build ./build
```

After compilation, the executable (`compilador`) will be available in the `./bin` directory.

### Alternative: Compile with GCC (Without CMake)

```sh
gcc src/*.c -o bin/compilador -Iinclude
```

---

## Generating Lexer and Parser Files (Optional)

The lexer (`lexer.c`) and parser (`parser.c`, `parser.h`) files are pre-generated. If needed, you can regenerate them as follows:

### Install Flex and Bison

```sh
sudo apt-get install bison flex
```

### Generate via Makefile

```sh
make generate
```

### Generate via Command Line

```sh
cd ./src
bison -d -o parser.c parser.y
flex -o lexer.c lexer.l
mv parser.h ../include
```

> [!NOTE]
> Regenerating these files is not necessary unless changes are made to `lexer.l` or `parser.y`.

---

## Usage

Execute the compiler with:

```sh
./bin/compilador <input_file.cm> [-o <binary_output_file.txt>] [-ni] [-ci] [-v] [-ca]
```

### Parameters

| Parameter                     | Description                                                                                 |
| ----------------------------- | ------------------------------------------------------------------------------------------- |
| `<input_file.cm>`             | Input source file to compile.                                                               |
| `-o <binary_output_file.txt>` | Specify output file for binary code (default: `binaryCode.txt`).                            |
| `-ni`                         | Read source code from standard input instead of a file.                                     |
| `-v`                          | Verbose mode; outputs tokens, syntax tree, and symbol table to `lexerAndParserResults.txt`. |
| `-ca`                         | Generate assembly code in `assemblyCode.txt`.                                               |
| `-ci`                         | Generate intermediate code in `intermediateCode.txt`.                                       |

### Especial functions

Inside the C- language, you can use some special functions that are used to interact directly with MIPS instructions. These functions are:
| Function Name   | Description                                                                                       | Usage Example          |
| --------------- | ------------------------------------------------------------------------------------------------- | ---------------------- |
| `input`         | Get an integer value from the FPGA switch keys (Stop the CPU until the input is given)            | `x = input(); `        |
| `output`        | Output an integer value to the FPGA 7-segment                                                     | `output(x);`           |
| `keyboardinput` | Get an integer value from the FPGA keyboard (Doesn't stop the CPU, return 0 if no input is given) | `x = keyboardinput();` |

---

## Automated Testing

> [!WARNING]
> Automated tests are under construction. Currently, you can manually test the compiler using sample files in the `test_files` directory.

