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

#ifndef VIDEOHEADERFMT_H
#define VIDEOHEADERFMT_H

typedef struct {
	uint32_t microSecPerFrame;
	uint32_t maxBytesPerSec;
	uint32_t reserved1;
	uint32_t flags;
	uint32_t totalFrames;
	uint32_t initialFrames;
	uint32_t streams;
	uint32_t suggestedBufferSize;
	uint32_t width;
	uint32_t height;
	uint32_t reserved[4];
} __attribute((packed)) avi_header;

#endif