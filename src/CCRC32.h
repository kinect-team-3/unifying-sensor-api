#ifndef CCRC32_H
#define CCRC32_H

#include <stdint.h>
#include <stdio.h>

uint32_t Reflect(uint32_t Reflect, const char Char);
/*
	Reflection is a requirement for the official CRC-32 standard.
	You can create CRCs without it, but they won't conform to the standard.
*/

uint32_t checksum(char* data, size_t length);
/*	
	Given the data buffer and the size of the buffer, the function
	calculates the checksum
*/

#endif

