# `dynamic library` is also called `shared library`

$ cd /Users/towfeeq.fayaz/towfeeq/LearnC/sample_project_dynamic_linking

# create object file
$ gcc -c src/math_multiply.c -I include -o lib/math_multiply.o
    => -c: Compile without linking (generate object file)
    => src/math_multiply.c: source file to compile
    => -I include: Add `include` folder to the list of directories to search for header files
    => -o lib/math_multiply.o: Output object file name in target directory
    
    # you can also using  -fPIC while creating object file
    $ gcc -fPIC -c src/math_multiply.c -I include -o lib/math_multiply.o
    # What is -fPIC?
      => -fPIC stands for "Position-Independent Code".
      => It instructs the compiler to generate code that does not depend on fixed memory addresses.
      => This is critical for shared libraries because they can be loaded at different memory locations
         in different programs (or even at different times within the same program).    
    
    Why is -fPIC Needed for Dynamic Libraries?
      => Dynamic Loading:
            - Shared libraries (.so files) are loaded at runtime.
            - The operating system may load the shared library into a memory address that is different
              from the one expected at compile time.
            - Without -fPIC, the library code would contain fixed addresses, making it incompatible
              with being relocated.
      
      => Code Reusability Across Processes:
            - Shared libraries are designed to be used by multiple processes.
            - -fPIC ensures the code can be mapped to the address space of different processes
              without modification, reducing memory overhead.

# create Dynamic/Shared Library libmathmul.so
$ gcc -shared lib/math_multiply.o -o lib/libmathmul.so

NOTE: insted of creating dynamic library from object file, you can directly create it from
      source file as well (thus skipping the step of creating obejct file)
      
      $ gcc -shared src/math_multiply.c -I include -o lib/libmathmul.so

NOTE: ar tool is specifically used for creating static libraries (.a files), not for creating dynamic
      libraries (.so files).


# Now since we are using shared library, we need to set env variable for compiler/linker
# for macOS
$ export DYLD_LIBRARY_PATH=/Users/towfeeq.fayaz/towfeeq/LearnC/sample_project_dynamic_linking/lib:$DYLD_LIBRARY_PATH
# for unix OS
$ export LD_LIBRARY_PATH=/Users/towfeeq.fayaz/towfeeq/LearnC/sample_project_dynamic_linking/lib:$LD_LIBRARY_PATH


$ gcc src/main.c src/math_add.c -I include -L lib -lmathmul -o src/main