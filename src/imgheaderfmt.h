#include <stdint.h>

#ifndef IMGHEADERFMT_H
#define IMGHEADERFMT_H

#define JPEG_SOI 	0xffd8
/**
 * Headers in the jpeg format
 */
typedef struct {
	uint16_t	soi;		//start of image 
	uint16_t	appn;		//application specific
	uint16_t	length;		//length of appn field
	uint8_t		identifier[5];	//format identifier
} __attribute((packed)) jpeg_header;

/**
 * Header for the png format
 */
typedef struct {
	uint64_t	signature;	//8-byte png signature
} __attribute((packed)) png_header;

/**
 * Header for the bmp format
 */
typedef struct {
	uint16_t	identifier;	//2-byte bit-map identifier
	uint32_t	size;		//size of bmp file in bytes
	uint16_t	creator1;	//reserved field for creator of image
	uint16_t	creator2;	//reserved field for creator of image
	uint32_t	offset;		//offset to start of image data
} __attribute((packed)) bmp_header;

/**
 * Header for the tiff format
 */
typedef struct {
	uint16_t	byte_order;	//byte ordering for interpretation 
	uint16_t	version;	//tiff version number
	uint32_t	offset;		//offset to first tiff image directory
} __attribute((packed)) tiff_header;

/**
 * Header for the gif format
 */
typedef struct {
	uint8_t		signature[3];	//header signature "GIF"
	uint8_t		version[3];	//gif format version 
} __attribute((packed)) gif_header;

int process_image(void* buf);
#endif
