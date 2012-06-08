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
#include "cJSON.h"

#ifndef UNIFYING_FUNCTIONS_H
#define UNIFYING_FUNCTIONS_H

/**
* 1) Strip off the sensor header based on offset 
* 2) Create a json_object with length, checksum, type, description,
*    sensor type, datastream  
* 3) Return the object
*/
char* convert_raw_to_unified (const uint8_t* data, size_t offset, size_t size,
	const char* type, const char* desc, const char* sensor);

/**
*
*/
uint8_t* convert_unified_to_raw (const char* jsondata, size_t* size);


char* process_unified (const char* jsondata, int(*process)(uint8_t *, size_t *));  

#endif
