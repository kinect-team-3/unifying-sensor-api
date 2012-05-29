#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

/** 
 * An equals check for two byte arrays 
 * Returns: 0 on failure, 1 on success;
 */
int bytes_equal (const uint8_t* a1, const uint8_t* a2, size_t n) {
	size_t i;
	for (i = 0; i < n; i++) {
		if (a1[i] != a2[i])
			return 0;
	}
	return 1;
}

/* included here for unit tests since its a static function */
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

static int test_data_to_hex(const uint8_t* dummy_data, size_t size, 
		const char* expected) {
	char* dummy_str = data_to_hex_string(dummy_data, size);
	if (strcmp(dummy_str, expected) != 0) {
		printf("Expected and str do not match in test_data_to_hex. \n");
		return -1;
	}
	free(dummy_str);
	return 0;
}

/* included here for unit test since static */ 
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
				return NULL;
		}		
		if (odd) {
			*byteptr = val;		
			printf("%u\n", *byteptr);
			byteptr++;
		}
	}
	return bytestream;
}

static int test_hex_to_data (const char* hexstr, size_t length, 
		const uint8_t* expected) {
	uint8_t* bytestream = hex_string_to_data(hexstr, length);	
	if (!bytes_equal(expected, bytestream, length/2)) {
		printf("Expected and data do not match in test_hex_to_data\n");	
		return -1;
	}
	free(bytestream);
	return 0;
}




int main() {
	size_t size = 10;
	size_t length = 20; 
	uint8_t dummy_data[10] = {0, 12, 13, 14, 25, 26, 27, 33, 200, 255};
	char* hexstr = "000c0d0e191a1b21c8ff";
	int retval = test_data_to_hex(dummy_data, size, hexstr); 
	printf("Return value for test_data_to_hex: %d\n", retval);
	retval = test_hex_to_data(hexstr, length, dummy_data); 
	printf("Return value for test_hex_to_data: %d\n", retval);
	/* TODO: Add more test cases */
	return 0; 			
}
