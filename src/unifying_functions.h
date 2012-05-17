/**
* 1) Strip off the sensor header based on offset 
* 2) Create a json_object with length, checksum, type, description,
*    sensor type, datastream  
* 3) Return the object
*/
json_object convert_raw_to_unified(uint8_t* data,size_t offset);

/**
*
*/
uint8_t* convert_unified_to_raw (json_object* data);

/**
*
*/
void print_json(json_object* data); 
