#ifndef _CCRC32_CPP
#define _CCRC32_CPP
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#define _CRT_SECURE_NO_WARNINGS 	//Disables fopen() security warning on Microsoft compilers.
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>
#include "CCRC32.h"

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

CCRC32::CCRC32(void)
{
	this->Initialize();
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

CCRC32::~CCRC32(void)
{
	//No destructor code.
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	This function initializes "CRC Lookup Table". You only need to call it once to
		initalize the table before using any of the other CRC32 calculation functions.
*/

void CCRC32::Initialize(void)
{
	//0x04C11DB7 is the official polynomial used by PKZip, WinZip and Ethernet.
	uint32_t Polynomial = 0x04C11DB7;

	//memset(&this->ulTable, 0, sizeof(this->ulTable));

	// 256 values representing ASCII character codes.
	for(int Codes = 0; Codes <= 0xFF; Codes++)
	{
		this->Table[Codes] = this->Reflect(Codes, 8) << 24;

		for(int Pos = 0; Pos < 8; Pos++)
		{
			this->Table[Codes] = (this->Table[Codes] << 1)
				^ ((this->Table[Codes] & (1 << 31)) ? Polynomial : 0);
		}

		this->Table[Codes] = this->Reflect(this->Table[Codes], 32);
	}
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	Reflection is a requirement for the official CRC-32 standard.
	You can create CRCs without it, but they won't conform to the standard.
*/

uint32_t CCRC32::Reflect(uint32_t Reflect, const char Char)
{
	uint32_t Value = 0;

	// Swap bit 0 for bit 7, bit 1 For bit 6, etc....
	for(int Pos = 1; Pos < (Char + 1); Pos++)
	{
		if(Reflect & 1)
		{
			Value |= (1 << (Char - Pos));
		}
		Reflect >>= 1;
	}

	return Value;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	Calculates the CRC32 by looping through each of the bytes in sData.

	Note: For Example usage example, see FileCRC().
*/

void CCRC32::PartialCRC(uint32_t *CRC, const char *Data, uint32_t DataLength)
{
	while(DataLength--)
	{
		//If your compiler complains about the following line, try changing each
		//	occurrence of *ulCRC with "((uint32_t)*ulCRC)" or "*(uint32_t *)ulCRC".

		 *(uint32_t *)CRC =
			((*(uint32_t *)CRC) >> 8) ^ this->Table[((*(uint32_t *)CRC) & 0xFF) ^ *Data++];
	}
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	Returns the calculated CRC23 for the given string.
*/

uint32_t CCRC32::FullCRC(const char *Data, uint32_t DataLength)
{
	uint32_t CRC = 0xffffffff; //Initilaize the CRC.
	this->PartialCRC(&CRC, Data, DataLength);
	return(CRC ^ 0xffffffff); //Finalize the CRC and return.
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	Calculates the CRC32 of a file using the a user defined buffer.

	Note: The buffer size DOES NOT affect the resulting CRC,
			it has been provided for performance purposes only.
*/

bool CCRC32::FileCRC(const char *FileName, uint32_t *OutCRC, uint32_t BufferSize)
{
	*(uint32_t *)OutCRC = 0xffffffff; //Initilaize the CRC.

	FILE *Source = NULL;
	char *Buf = NULL;
	int BytesRead = 0;

	if((Source = fopen(FileName, "rb")) == NULL)
	{
		return false; //Failed to open file for read access.
	}

	if(!(Buf = (char *)malloc(BufferSize))) //Allocate memory for file buffering.
	{
		fclose(Source);
		return false; //Out of memory.
	}

	while((BytesRead = fread(Buf, sizeof(char), BufferSize, Source)))
	{
		this->PartialCRC(OutCRC, Buf, BytesRead);
	}

	free(Buf);
	fclose(Source);

	*(uint32_t *)OutCRC ^= 0xffffffff; //Finalize the CRC.

	return true;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#endif
