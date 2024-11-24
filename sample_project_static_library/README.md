$ cd /Users/towfeeq.fayaz/towfeeq/LearnC/sample_project_static_library

# create object file
$ gcc -c src/math_multiply.c -I include -o lib/math_multiply.o
    => -c: Compile without linking (generate object file)
    => src/math_multiply.c: source file to compile
    => -I include: Add `include` folder to the list of directories to search for header files
    => -o lib/math_multiply.o: Output object file name in target directory

# create static library
$ ar rcs lib/libmathmul.a lib/math_multiply.o
NOTE: ar tool is specifically used for creating static libraries (.a files), not for creating dynamic
      libraries (.so files).


# compile and generate final executable
$ gcc src/main.c src/math_add.c -I include -L lib -lmathmul -o src/main
    => src/main.c src/math_add.c : compile both of them together as final executable
    => -I include: tells GCC to look for header files in the include/ directory relative to the current directory
    => -L lib: specifies the directory where libmathmul.a is located (relative to the current directory).
    => -lmathmul links libmathmul.a with executable generate from "src/main.c src/math_add.c"

    NOTE: Note for libmathmul.a, we omitted the “lib” prefix and “.a” extension. The linker attaches
          these parts back to the name of the library to create a name of a file to look for.

$ ./src/main

============================================================================