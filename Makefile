# /**************************************************************
# This file is part of Kinect Sensor Architecture Development Project.
#
#   Kinect Sensor Architecture Development Project is free software:
# you can redistribute it and/or modify
#   it under the terms of the GNU General Public License as published by
#   the Free Software Foundation, either version 3 of the License, or
#   (at your option) any later version.

#   Kinect Sensor Architecture Development Project is distributed in
# the hope that it will be useful,
#  but WITHOUT ANY WARRANTY; without even the implied warranty of
#  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#  GNU General Public License for more details.

#   You should have received a copy of the GNU General Public License
#  along with Kinect Sensor Architecture Development Project.  If
# not, see <http://www.gnu.org/licenses/>.
# **************************************************************/
# /**************************************************************
# The work was done in joint collaboration with Cisco Systems Inc.
# Copyright © 2012, Cisco Systems, Inc. and UCLA
# *************************************************************/

# A makefile for managing build of Unifying Sensor API

CC = gcc

# CFLAGS
# -g				compile with debug information
# -Wall			give verbose compiler warnings
# -O0				do not optimize generated code
# -std=c99	use the C99 standard language definition
CFLAGS = -g -Wall -O0 -std=c99 -I lib -I src -arch i386
MATH = -lm
NOLINK = -c

all: demotest translatetest

demotest: unifying_functions.o demotest.o cJSON.o
	$(CC) $(CFLAGS) $(MATH) test/demotest.o src/unifying_functions.o lib/cJSON.o -o demotest

cJSON.o: lib/cJSON.c lib/cJSON.h
	$(CC) $(CFLAGS) $(MATH) $(NOLINK) lib/cJSON.c -o lib/cJSON.o


demotest.o: test/demotest.c
	$(CC) $(CFLAGS) $(NOLINK) test/demotest.c -o test/demotest.o 

unifying_functions.o: src/unifying_functions.c src/unifying_functions.h  
	$(CC) $(CFLAGS) $(NOLINK) src/unifying_functions.c -o src/unifying_functions.o  

translatetest: test/translatetest.c
	$(CC) $(CFLAGS) test/translatetest.c -o test/translatetest
		

clean:
	@rm -rf test/demotest.o src/unifying_functions.o lib/cJSON.o demotest test/translatetest
