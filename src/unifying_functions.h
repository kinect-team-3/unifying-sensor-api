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
char* convert_raw_to_unified(const uint8_t* data, size_t offset, size_t length,
	const char* type, const char* desc, const char* sensor);

/**
*
*/
uint8_t* convert_unified_to_raw (const char* data);

#endif
