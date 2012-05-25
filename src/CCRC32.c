#include <stdlib.h>
#include "CRC32.h"

uint32_t Reflect(uint32_t Reflect, const char Char)
{
	/*
	Reflection is a requirement for the official CRC-32 standard.
	You can create CRCs without it, but they won't conform to the standard.
	*/
	uint32_t Value = 0;

	// Swap bit 0 for bit 7, bit 1 For bit 6, etc....
	int Pos;
	for(Pos = 1; Pos < (Char + 1); Pos++)
	{
		if(Reflect & 1)
		{
			Value |= (1 << (Char - Pos));
		}
		Reflect >>= 1;
	}

	return Value;
}


uint32_t checksum(char* data, size_t length)
{
//Creates the CRC look up table
	uint32_t Table[256];
	uint32_t Polynomial = 0x04C11DB7;
	
	int Codes;
	for(Codes = 0; Codes <= 0xFF; Codes++)
	{
		Table[Codes] = Reflect(Codes, 8) << 24;
		
		int Pos;
		for(Pos = 0; Pos < 8; Pos++)
		{
			Table[Codes] = (Table[Codes] << 1)
				^ ((Table[Codes] & (1 << 31)) ? Polynomial : 0);
		}

		Table[Codes] = Reflect(Table[Codes], 32);
	}
	
//goes through each byte in data and creates the checksum
	uint32_t CRC = 0xffffffff; //Initilaize the CRC.

	uint32_t count=length;	
	while(count--)
	{
		 CRC =((CRC) >> 8) ^ Table[(CRC & 0xFF) ^ *data++];
	}
	
	return(CRC ^ 0xffffffff); //Finalize the CRC and return.
	
}

