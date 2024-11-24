$ cd /Users/towfeeq.fayaz/towfeeq/LearnC/calculator_project

## Create the Static Library (for multiplication)
# Compile math_multiplication.c into an object file
$ gcc -c src/math/math_multiplication.c -I include/math -o lib/objects/math_multiplication.o
# Create a static library from the object file
$ ar rcs lib//static/libmathmultiply.a lib/objects/math_multiplication.o

## Create the Static Library (for division)
# Compile math_division.c into an object file
$ gcc -c src/math/math_division.c -I include/math -o lib/objects/math_division.o
# Create a static library from the object file
$ ar rcs lib/static/libmathdivide.a lib/objects/math_division.o


## Create the Dynamic Library (for addition)
# Compile math_addition.c into a position-independent object file
$ gcc -fPIC -c src/math/math_addition.c -I include/math -o lib/objects/math_addition.o
# Create a shared library (dynamic library) from the object file
$ gcc -shared lib/objects/math_addition.o -o lib/dynamic/libmathadd.so

## Create the Dynamic Library (for subtraction)
# Compile math_subtraction.c into a position-independent object file
$ gcc -fPIC -c src/math/math_subtraction.c -I include/math -o lib/objects/math_subtraction.o
# Create a shared library (dynamic library) from the object file
$ gcc -shared lib/objects/math_subtraction.o -o lib/dynamic/libmathsubtract.so


# Compile and Link the Final Executable
# Export the dynamic library path
$ export LD_LIBRARY_PATH=/Users/towfeeq.fayaz/towfeeq/LearnC/calculator_project/lib:$LD_LIBRARY_PATH

# Compile and link the executable with both libraries
$ gcc src/main.c src/math/math_remainder.c -I include/math -L lib/static -L lib/dynamic -lmathmultiply -lmathadd -lmathsubtract -lmathdivide  -o src/main
--------------------------------------------------------