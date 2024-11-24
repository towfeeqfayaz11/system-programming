$ cd /Users/towfeeq.fayaz/towfeeq/LearnC/sample_project_library

## Create the Static Library (for Multiply)
# Compile math_multiply.c into an object file
$ gcc -c src/math_multiply.c -I include -o lib/math_multiply.o
# Create a static library from the object file
$ ar rcs lib/libmathmul.a lib/math_multiply.o


## Create the Dynamic Library (for Divide)
# Compile math_divide.c into a position-independent object file
$ gcc -fPIC -c src/math_divide.c -I include -o lib/math_divide.o
# Create a shared library (dynamic library) from the object file
$ gcc -shared lib/math_divide.o -o lib/libmathdiv.so


# Compile and Link the Final Executable
# Export the dynamic library path
$ export LD_LIBRARY_PATH=/Users/towfeeq.fayaz/towfeeq/LearnC/sample_project_library/lib:$LD_LIBRARY_PATH

# Compile and link the executable with both libraries
$ gcc src/main.c src/math_add.c -I include -L lib -lmathmul -lmathdiv -o src/main
--------------------------------------------------------