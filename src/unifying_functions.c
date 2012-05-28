#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include "unifying_functions.h"

static char* data_to_hex_string(const uint8_t* data, size_t size); 
static uint8_t* hex_string_to_data(const char* hexstr, size_t length);

char* convert_raw_to_unified(const uint8_t* data, size_t offset, size_t size,
	const char* type, const char* desc, const char* sensor) {
	/* remove the sensor headers */
	uint8_t* plain_data = data + offset; 
	
	/* convert datasteam into hex string */
	char* hexstr = data_to_hex_string(plain_data, size-offset);
	
	/* create a root cJSON object */		
	cJSON* unified_root = cJSON_CreateObject();

	/* add all elements */
	cJSON_AddStringToObject(unified_root, "type", type);
	cJSON_AddStringToObject(unified_root, "description", desc);
	/*Note max size of size_t varies per machine, 
		meaning max size can vary */ 
	cJSON_AddNumberToObject(unified_root, "size", size); 
	cJSON_AddStringToObject(unified_root, "sensor", sensor);
	int checksum = 0xdeadbeef; 
	cJSON_AddNumberToObject(unified_root, "checksum", checksum);
	cJSON_AddStringToObject(unified_root, "data", hexstr);
	
	/* TODO: calculate checksum and attach to root */
	/* dummy checksum */
	char* unified_str = cJSON_Print(unified_root);
	cJSON_Delete(unified_root);
	unified_root = NULL;
	free(hexstr);
	hexstr = NULL;
	return unified_str; 
}

uint8_t* convert_unified_to_raw (const char* jsondata) {
	uint8_t* bytestream = NULL;
	char* hexstr = NULL;
	/* Parse the JSON string */
	cJSON *unified_root = cJSON_Parse(jsondata); 	
	if (unified_root == NULL) {
		return NULL;
	}
	/* Get the relevant JSON elements */
	cJSON *datasize = cJSON_GetObjectItem(unified_root, "size");
	cJSON *datastr = cJSON_GetObjectItem(unified_root, "data");
	if (datastr == NULL || datasize == NULL) {
		goto done;
	} 
	/* assume conversion from json int to size_t works */
	size_t size = (size_t) cJSON_GetObjectItem(unified_root, "size")->valueint;
	hexstr = cJSON_GetObjectItem(unified_root, "data")->valuestring;
	if (hexstr == NULL) {
		goto done;
	}
	bytestream =  hex_string_to_data(hexstr, size*2);

/* clean up */
done:
	/* hexstr is cleaned up by cJSON_Delete */
	cJSON_Delete(unified_root);
	unified_root = NULL;
	return bytestream;
}


static char* data_to_hex_string(const uint8_t* data, size_t size) {
	char* hex_string = (char*) malloc(2*sizeof(char)*size+1);
	size_t i;
	/* print data one byte at a time as a set of two hex chars */
	for(i = 0; i < size; i++) {
		sprintf(hex_string+(2*i),"%02x", data[i]);
	}	
	/* null byte */
	hex_string[2*size] = '\0';
	return hex_string;
} 

static uint8_t* hex_string_to_data(const char* hexstr, size_t length) {
	/*Note we expect length to be even given that the hex string
	is twice as long as the bytestream */
	uint8_t* bytestream = (uint8_t*) malloc(length/2*sizeof(uint8_t));
	uint8_t* byteptr = bytestream;
	uint8_t val;
	char c;
	size_t i;
	for(i = 0; i < length; i++) {
		int odd = (i & 1);
		val = odd ? (val << 4) : 0;	
		c = tolower(hexstr[i]);
		switch(c) {
			case '0':
				val |= 0x0;
				break;
			case '1':
				val |= 0x1;
				break;
			case '2':
				val |= 0x2;
				break;
			case '3':
				val |= 0x3;
				break;
			case '4':
				val |= 0x4;
				break;
			case '5':
				val |= 0x5;
				break;
			case '6':
				val |= 0x6;
				break;
			case '7':
				val |= 0x7;
				break;
			case '8':
				val |= 0x8;
				break;
			case '9':
				val |= 0x9;
				break;
			case 'a':
				val |= 0xa;
				break;
			case 'b':
				val |= 0xb;
				break;
			case 'c':
				val |= 0xc;
				break;
			case 'd':
				val |= 0xd;
				break;
			case 'e':
				val |= 0xe;
				break;
			case 'f':
				val |= 0xf;
				break;
			/* did not find a hex letter */
			default: 
				free(bytestream);
				bytestream = NULL;
				return NULL;
		}		
		if (odd) {
			*byteptr = val;		
			byteptr++;
		}
	}
	return bytestream;
}
