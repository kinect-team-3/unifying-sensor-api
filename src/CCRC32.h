#ifndef _CCRC32_H
#define _CCRC32_H

#include <stdint.h>
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class CCRC32{

	public:
		CCRC32(void);
		~CCRC32(void);

		void Initialize(void);

		bool FileCRC(const char *FileName, uint32_t *OutCRC, uint32_t BufferSize);

		uint32_t FullCRC(const char *Data, uint32_t DataLength);

		void PartialCRC(uint32_t *CRC, const char *Data, uint32_t DataLength);

	private:
		uint32_t Reflect(uint32_t Reflect, const char Char);
		uint32_t Table[256]; // CRC lookup table array.
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#endif
