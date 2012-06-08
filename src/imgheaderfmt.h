/**************************************************************
 This file is part of Kinect Sensor Architecture Development Project.

   Kinect Sensor Architecture Development Project is free software:
you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   Kinect Sensor Architecture Development Project is distributed in
the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with Kinect Sensor Architecture Development Project.  If
not, see <http://www.gnu.org/licenses/>.
**************************************************************/
/**************************************************************
The work was done in joint collaboration with Cisco Systems Inc.
Copyright © 2012, Cisco Systems, Inc. and UCLA
*************************************************************/

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
