Unifying Sensor API Project
===========================

Git workflow
------------

1) Modify the code.

2) Tell Git to start tracking new/modified source code.
  
    $ git add .

3) Commit code. Add useful comments.

    $ git commit -m "Updated test.c to include tests on JPEG image."

4) Push the code to Github.

    $ git push



How to compile and run test.c
-----------------------------
    $ cd unifying-sensor-api
    $ make clean
    $ make
    $ test/testprogram <PATH_TO_JPEG>

Before pushing code to Github
-----------------------------
    $ make clean
    
    

Notes on building the shared library for CJavaInterface
-------------------------------------------------------
Compile the C files (change the path to jni.h accordingly)

    $ gcc -c -I/usr/lib/jvm/java-1.7.0-openjdk-i386/include -I/usr/lib/jvm/java-1.7.0-openjdk-i386/include/linux -I../lib unifying_functions.c UnifyingAPI.c ../lib/cJSON.c
    
Using the object files, build a shared library named "libCJavaInterface.so"

    $ ld -G UnifyingAPI.o unifying_functions.o cJSON.o -o libCJavaInterface.so -lm -lc -lpthread
    
Compile the java program

    $ javac HelloWorld.java
    
Run the Java program, make sure to include path to the shared lib

    $ java -Djava.library.path=./ HelloWorld
