#include "imgheaderfmt.h"
#include <stdio.h>

int process_jpeg_image(void* buf) {
	/* Extract the JPEG header. */
	jpeg_header * jpegh = (jpeg_header*) buf; 

	/* Determine if file in buffer is actually a JPEG file. */
	if (jpegh->soi == JPEG_SOI) {
		fprintf(stderr, "File is not of type JPEG.");
		return -1;
	}

	/* Check if jfif or exif */
	if ((jpegh->appn)& 0x0100) {
		/* EXIF header */
		fprintf(stderr, "JPEG is of type EXIF");
	}
	else {
		/* JFIF header */
		fprintf(stderr, "JPEG is of type JFIF");
	}
	
	/* TO-DO: Return JPEG image as JSON object, change return type of function */
	return -1;
}
