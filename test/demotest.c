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

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include "unifying_functions.h"

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
//		printf("stat structured filled in properly.\n");
	}
	
	size_t filesize = jpeg_info->st_size;
//	printf("File size: %d.\n", (int)filesize);
	
	/* imgbuf is a pointer to the binary data that represents the file */
	uint8_t *imgbuf = (uint8_t*) malloc (filesize);
	ssize_t num_bytes = read(fd, imgbuf, filesize);	
	if (num_bytes == -1) {
		fprintf(stderr, "JPEG file not read.\n");
		printf("%s\n", strerror(errno));
		exit(1);
	} else {
//		printf("Number of bytes read: %d\n", (int)num_bytes);
	}
	
	char* json_data = convert_raw_to_unified(imgbuf, 0, (size_t)jpeg_info->st_size, "JPEG", "JPEG stands for Joint Photographic Experts Group. An image processed with digital compression. See standard ISO/IEC 10918-4:1999 for more details.", "Cannon Camera");
	
	printf(json_data);
	size_t bytestreamsize;
	uint8_t *converted_imgbuf = convert_unified_to_raw(json_data, &bytestreamsize);
	FILE * jpegfile;
	jpegfile = fopen("f.jpeg","wb");
	fwrite(converted_imgbuf, 1, (size_t)jpeg_info->st_size, jpegfile);
	fclose(jpegfile); 	
	free(converted_imgbuf);
	close(fd);		
	free(imgbuf);
	free(jpeg_info);
	free(json_data);
	return 0;
}
