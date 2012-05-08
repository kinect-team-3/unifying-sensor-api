#include <stdint.h>

#ifndef IMGHEADERFMT_H
#define IMGHEADERFMT_H

#define JPEG_SOI 	0xffd8
/**
 * Headers in the jpeg format
 * jfif header lies underneath jpeg header
 * exif header not implemented yet
 * NOTE: LITTLE ENDIAN ASSUMED
 */
typedef struct {
	uint16_t	soi;		//start of image 
	uint16_t	appn;		//application specific
	uint16_t	length;		//length of appn field
	uint8_t		identifier[5];	//format identifier
} __attribute((packed)) jpeg_header;

typedef struct {
	uint16_t	version;	//version, 1st byte major, 2nd minor
	uint8_t		dunits;		//units for pixel density field
	uint16_t	xdensity;	//horizontal pixel density
	uint16_t	ydensity;	//vertical pixel density
	uint8_t		xthumbnail;	//horizontal size (thumbnail)
	uint8_t		ythumbnail;	//vertical size (thumbnail)
} __attribute((packed)) jfif_header;


int process_image(void* buf);
static int process_jpeg_image(void* buf);
static int process_jfif_image(void* buf);
static int process_exif_image(void* buf);

#endif
