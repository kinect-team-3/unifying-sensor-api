#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

/* included here for unit tests since its a static function */
static char* data_to_hex_string(const uint8_t* data, size_t length) {
        char* hex_string = (char*) malloc(2*sizeof(char)*length+1);
        size_t i;
        /* print data one byte at a time as a set of two hex chars */
        for(i = 0; i < length; i++) {
                sprintf(hex_string+(2*i),"%02x", data[i]);
        }       
        /* null byte */
        hex_string[2*length] = '\0'; 
        return hex_string;
} 


int main() {
	uint8_t dummy_data[10] = {0, 12, 13, 14, 25, 26, 27, 33, 200, 255};
	char* dummy_str = data_to_hex_string(dummy_data, 10);
	printf(dummy_str);
	printf("\n");
	free(dummy_str);
	return 0; 			
}
