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
