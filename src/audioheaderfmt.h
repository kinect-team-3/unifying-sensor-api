#ifndef AUDIOHEADERFMT_H
#define AUDIOHEADERFMT_H

#include <stdint.h>

/**
 * Headers for audio files
 *
 */
 
// The string "WAVE"
#define WAVE 0x57415645
// The string "RIFF"
#define RIFF 0x52494646
// The string "fmt "
#define FMT 0x666d7420

/**
 * Header for WAVE file
 * BE = Big Endian, LE = Little Endian
 */


typedef struct
{
	uint32_t ChunkID; 		// Chunk ID, BE, contains "RIFF"
	uint32_t ChunkSize; 	// Chunk Size, LE
	uint32_t Format; 		// Contains "WAVE", BE
	
} __attribute((packed)) riff_header;
	
typedef struct
{
	uint32_t SubchunkID; 	// Subchunk ID, BE, Contains "fmt "
	uint32_t SubchunkSize;	// Subchunk Size, LE
	uint16_t AudioFormat;	// LE
	uint16_t NumChannels;	// LE
	uint32_t SampleRate;	// LE
	uint32_t ByteRate;		// LE
	uint16_t BlockAlign;	// LE
	uint16_t BitsPerSample;	// LE
	
} __attribute((packed)) fmt_subchunk;

// Not sure if the stuff below is needed or not
/*typedef struct
{
	uint32_t SubchunkID;
	uint32_t SubchunkSize;
	
} __attribute((packed)) data_subchunk*/

typedef struct
{	
	riff_header riff;
	fmt_subchunk fmt;
	
} __attribute((packed)) wav_header;

#endif
