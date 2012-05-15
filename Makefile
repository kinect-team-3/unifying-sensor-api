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
CFLAGS = -g -Wall -O0 -std=c99 -I src

test: test/test.o
	$(CC) $(CFLAGS) test/test.o -o test/testprogram

videotest: test/videotest.o
	$(CC) $(CFLAGS) test/videotest.o -o test/videotest

videotest.o: test/videotest.c src/videoheaderfmt.h
	$(CC) $(CFLAGS) test/videotest.c
		
imgheaderfmt.o : src/imgheaderfmt.c src/imgheaderfmt.h
	$(CC) $(CFLAGS) src/imgheaderfmt.c
	
test.o : src/imgheaderfmt.h test/test.c
	$(CC) $(CFLAGS) test/test.c
	
clean:
	@rm -rf test/test.o test/testprogram test/videotest.o test/videotest