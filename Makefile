# A makefile for managing build of Unifying Sensor API
#
# Author: Carson Tang
# Date: 05/08/2012

CC = gcc

# CFLAGS
# -g				compile with debug information
# -Wall			give verbose compiler warnings
# -O0				do not optimize generated code
# -std=c99	use the C99 standard language definition
CFLAGS = -g -Wall -O0 -std=c99 -I lib -I src
MATH = -lm
NOLINK = -c

all: demotest

demotest: unifying_functions.o demotest.o cJSON.o
	$(CC) $(CFLAGS) $(MATH) test/demotest.o src/unifying_functions.o lib/cJSON.o -o demotest

cJSON.o: lib/cJSON.c lib/cJSON.h
	$(CC) $(CFLAGS) $(MATH) $(NOLINK) lib/cJSON.c -o lib/cJSON.o


demotest.o: test/demotest.c
	$(CC) $(CFLAGS) $(NOLINK) test/demotest.c -o test/demotest.o 

unifying_functions.o: src/unifying_functions.c src/unifying_functions.h  
	$(CC) $(CFLAGS) $(NOLINK) src/unifying_functions.c -o src/unifying_functions.o  

### I don't think these cases were written correctly

#imagetest: test/imagetest.o src/imgheaderfmt.o 
#	$(CC) $(CFLAGS) test/imagetest.o -o test/imagetestprogram

#imgheaderfmt.o : src/imgheaderfmt.c src/imgheaderfmt.h
#	$(CC) $(CFLAGS) src/imgheaderfmt.c

#videotest: test/videotest.o
#	$(CC) $(CFLAGS) test/videotest.o -o test/videotestprogram

#videotest.o: test/videotest.c src/videoheaderfmt.h
#	$(CC) $(CFLAGS) test/videotest.c
		

clean:
#	@rm -rf test/imagetest.o test/imagetestprogram test/videotest.o test/videotestprogram src/imgheaderfmt.o src/unifying_functions.o lib/cJSON.o test/demotest.o
	@rm -rf test/demotest.o src/unifying_functions.o lib/cJSON.o demotest
