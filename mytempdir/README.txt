# first we need to create object file from our sourcecode file 
# of utility (-c option is used to created object file)
$ gcc -c mysum.c -o mysum.o

# next we need to generate a library file from the object file
$ ar rcs libmysum.a mysum.o

NOTE: here the above step creates a static library, we can also create a dynamic/shared library as
$ gcc -shared -o libmysum.so mysum.o
NOTE: ar tool is specifically used for creating static libraries (.a files), not for creating dynamic
      libraries (.so files).

# finally we compile our main file and also inform compiler where
# to find user defined header and library files
$ gcc mymain.c -o mymain -L. -l mysum

# Note that for libmysum.a we omitted the “lib” prefix and “.a” extension.
# The linker attaches these parts back to the name of the library to create
# a name of a file to look for.

# finally we exeute our runnable file
$ ./mymain