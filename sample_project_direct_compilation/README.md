$ cd /Users/towfeeq.fayaz/towfeeq/LearnC/sample_project
# below are the two options to compile and run the code:

# method1:
$ gcc src/* -I include -o src/main
$ ./src/main

# method2:
# "Compile Each File into Object Files"
$ gcc -c src/main.c -I include -o src/main.o
$ gcc -c src/math_add.c -I include -o src/math_add.o
# "Link the Object Files"
$ gcc src/main.o src/math_add.o -o src/main
$ ./src/main
==============================================================