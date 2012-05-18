#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/stat.h>
#include <unistd.h>
#include "imgheaderfmt.h"
#include <string.h>
#include <fcntl.h>

int main(int argc, char *argv[]) {
	
	/* UNIMPORTANT: Open file and determine the file size */
	if (argc != 2) {
		fprintf(stderr, "Must specify only one JPEG file.\n");
		exit(1);
	}
	
	char *path = argv[1];
	int fd = open(path, 0644);
	struct stat *jpeg_info = (struct stat*) malloc(sizeof(struct stat));
	int stat_retval = stat(path, jpeg_info);
	
	if (stat_retval != 0) {
		fprintf(stderr, "stat structure not filled in properly.\n");
		exit(1);
	} else {
		printf("stat structured filled in properly.\n");
	}
	
	size_t filesize = jpeg_info->st_size;
	printf("File size: %d.\n", (int)filesize);
	
	/* imgbuf is a pointer to the binary data that represents the file */
	void *imgbuf = malloc (filesize);
	ssize_t num_bytes = read(fd, imgbuf, filesize);	
	if (num_bytes == -1) {
		fprintf(stderr, "JPEG file not read.\n");
		printf("%s\n", strerror(errno));
		exit(1);
	} else {
		printf("Number of bytes read: %d\n", (int)num_bytes);
	}
	
	/* IMPORTANT: Cast the first part of the binary data, imgbuf, into a jpeg_header */
	jpeg_header* jpegh = (jpeg_header*) imgbuf;
	
	/* If binary data actually represents a JPEG image,
		SOI must be 0xFFD8 or 0xD8FF depending on your machine's endianness.
		
		Identifier is either JFIF or Exif. If you Google for a JPEG iage, you'll probably
		get a JFIF file. If you use a JPEG image from your digital camera, it'll most likely
		be an Exif file.
	*/
	
	printf("SOI: %x\n", jpegh->soi);
	printf("Length 1st byte: %x\n", jpegh->length);
	printf("Identifier: %s\n", jpegh->identifier);
	
	/* Housekeeping routines */
	close(fd);		
	free(imgbuf);
	
	return 0;
}
