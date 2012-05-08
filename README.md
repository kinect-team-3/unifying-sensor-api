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
