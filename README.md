# C- Compiler Project

This project is a compiler for a simple language called C Minus (`C-`). The compiler is able to generate the intermediate code, the assembly code, and the binary code for the language. 

The project was developed using C. The lexical and syntax analysis was implemented using Flex and Bison, respectively. 

The assembly and binary code correspond to a simplified version of the MIPS architecture that was made by me for another project. You can find it in the [MIPS project repository](https://github.com/EduardoVeri/MIPS-Processor).

The analysis part was developed as a final project for the Compilers course at the Federal University of São Paulo (UNIFESP) in 2022, taught by Professor Dr. Luis Augusto Martins Pereira.

The synthesis part was developed as a final project for the Compilers Laboratory course at the Federal University of São Paulo (UNIFESP) in 2023, taught by Dra. Thaina Aparecida Azevedo Tosta.

## Compilation Steps

The project was developed using CMake. To compile the project, follow these steps:

0. Install the required dependencies. For Ubuntu, you can run the following command to install the required dependencies:

    ```sh
    sudo apt-get install cmake
    ```

1. Create a build directory:

    ```sh
    mkdir -p build
    cmake -B ./build [-DSHOW_WARNINGS=ON]
    ```

3. Compile the project:

    ```sh
    cmake --build ./build
    ```

To enable warnings, add the `-DSHOW_WARNINGS=ON` flag to the `cmake` configuration command.

After these steps, the executable will be located in the `./bin` directory named by default `compilador`.

If you don't want to use CMake, you can compile the project using gcc with the following command:

```sh
gcc src/*.c -o bin/compilador -lfl -Iinclude 
```

## Generating Lexer and Parser .c files

The project uses Flex and Bison to generate the lexer and parser files. **They are already generated and included in the project.** However, if you want to generate them again, you can use the following commands:

Install the required dependencies. For Ubuntu, you can run the following command to install the required dependencies:

```sh
sudo apt-get install bison flex
```

Generate the files using the Makefile:

```sh
make generate
```

Using command line:

```sh
cd ./src
bison -d -oparser.c parser.y
flex -olexer.c lexer.l
mv parser.h ../include
```


## Usage

To use the compiler, run the executable with the following commands:

```sh
./bin/compilador <input_file.cm> [-o <binary_output_file.txt>] [-ni] [-ci] [-v] [-ca]
```

### Parameters

- `<input_file.cm>`  
  **Description:** Specifies the input file. The program will read the code from this file.


- `-o <binary_output_file.txt>` (Optional)  
  **Description:** Specifies the output file. If not provided, the program writes the binary output to a file named `binaryCode.txt`.


- `-ni` (Optional)  
  **Description:** Indicates that there is no input file. The program will read from the standard input.


- `-v` (Optional)  
  **Description:** Enables verbose mode. The program will print the tokens and the syntax tree to a file named `output.txt`.


- `-ca` (Optional)  
  **Description:** Creates an assembly file. The program will generate a file named `output.asm`.


- `-ci` (Optional)  
  **Description:** Creates an intermediate code file. The program will generate a file named `output.ic`.



