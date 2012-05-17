#include "unifying_functions.h"

static char* data_to_hex_string(const uint8_t* data, size_t length); 

char* convert_raw_to_unified(const uint8_t* data, size_t offset, size_t length
	const char* type, const char* desc, const char* sensor) {
	/* remove the sensor headers */
	uint8_t* plain_data = data + offset; 
	
	/* convert datasteam into hex string */
	char* hex_data = data_to_hex_string(plain_data, length-offset);
	
	/* create a root cJSON object */		
	cJSON* unified_root = cJSON_CreateObject();

	/* add all elements */
	cJSON_AddStringToObject(unified_root, "type", type);
	cJSON_AddStringToObject(unified_root, "description", desc);
	//Note max size of size_t varies per machine, meaning max length can vary 
	cJSON_AddNumberToObject(unified_root, "length", length); 
	cJSON_AddStringToObject(unified_root, "sensor", sensor);
	cJSON_AddStringToObject(unified_root, "data", hex_data);

	/* TODO: calculate checksum and attach to root */
	
	return cJSON_Print(unified_root);
}

/* TODO: Convert the raw unified data back to a raw datastream */
uint8_t* convert_unified_to_raw (const char* data) {
}


/* TODO: implement this function to transform a datastream to hex string */
static char* data_to_hex_string(const uint8_t* data, size_t length) {
} 
