Create the Header File mysum.h:

Place mysum.h in the include/ directory.
Example content of mysum.h:

#ifndef MYSUM_H
#define MYSUM_H

int sum(int a, int b);

#endif


Create the Source File mysum.c:

Place mysum.c in the src/ directory.
Example content of mysum.c:

#include "mysum.h"

int sum(int a, int b) {
    return a + b;
}


Compile mysum.c into Object File:

Open a terminal and navigate to the src/ directory.
Compile mysum.c into an object file (mysum.o):

gcc -c mysum.c -o mysum.o -I../include 

-c: Compile without linking (generate object file).
mysum.c: Source file to compile.
-o mysum.o: Output object file name.
-I../include: Add ../include to the list of directories to search for header files. 
This tells the compiler to look for mysum.h in the include/ directory located one 
level above the current directory (src/).



Create Dynamic/Shared Library libmysum.so:

Still in the src/ directory, use ar to create the shared/dynamic library:
gcc -shared -o libmysum.so mysum.o

NOTE: insted of creating dynamic library from object file, you can directly
create it from source file as well (thus skipping the step of creating obejct file)
gcc -shared -o libmysum.so mysum.c -I../include

NOTE: ar tool is specifically used for creating static libraries (.a files), not for creating dynamic
      libraries (.so files).

Now Since we are using shared library, we need to set env variable for compiler/linker
export DYLD_LIBRARY_PATH=/Users/towfeeq.fayaz/towfeeq/LearnC/myprojectso/src:$DYLD_LIBRARY_PATH  # for macOS
export LD_LIBRARY_PATH=/Users/towfeeq.fayaz/towfeeq/LearnC/myprojectso/src:$LD_LIBRARY_PATH      # for unix OS

Compile mymain.c with libmysum.so:
Move to the main/ directory where mymain.c is located.
Compile mymain.c and link it with libmysum.so:

gcc mymain.c -o mymain -I../include -L../src -lmysum
-I../include tells GCC to look for header files in the include/ directory relative to the current directory.
-L../src specifies the directory where libmysum.so is located (relative to the current directory).
-lmysum links mymain.c with libmysum.so.

NOTE: Note for libmysum.so, we omitted the “lib” prefix and “.a” extension. The linker attaches these parts
back to the name of the library to create a name of a file to look for.

Run the Compiled Program:

After successful compilation, you can run your program:

./mymain



In summary, you organize your header and source files in separate directories (include/ and src/),
compile mysum.c into an object file, create a static library from the object file, and then compile 
mymain.c by specifying the appropriate include and library directories. Adjust the paths and commands
as needed based on your actual directory structure.


