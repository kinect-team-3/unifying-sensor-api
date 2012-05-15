#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/stat.h>
#include <unistd.h>
#include "videoheaderfmt.h"
#include <string.h>

int main(int argc, char *argv[]) {
	
	/* UNIMPORTANT: Open file and determine the file size */
	if (argc != 3) {
		fprintf(stderr, "Usage: test/videotest <VIDEO_FORMAT> <PATH_TO_VIDEO>\n");
		exit(1);
	}

	char *video_format = argv[1];
	char *path_to_video = argv[2];
	int fd = open(path_to_video, 0644);
	struct stat *video_info = (struct stat*) malloc(sizeof(struct stat));
	int stat_retval = stat(path_to_video, video_info);
	
	if (stat_retval != 0) {
		fprintf(stderr, "stat structure not filled in properly.\n");
		exit(1);
	} else {
		printf("stat structured filled in properly.\n");
	}
	
	off_t filesize = video_info->st_size;
	printf("File size: %d.\n", (int)filesize);
	
	if (strcmp("AVI", video_format) == 0) {
		// process video as AVI
		printf("Processing AVI video...");
	}
	
	/* videobuf is a pointer to the binary data that represents the file */
	void *videobuf = malloc (filesize);
	ssize_t num_bytes = read(fd, videobuf, filesize);	
	if (num_bytes == -1) {
		fprintf(stderr, "Video file not read.\n");
		printf("%s\n", strerror(errno));
		exit(1);
	} else {
		printf("Number of bytes read: %d\n", (int)num_bytes);
	}
	
	/* IMPORTANT: Cast the first part of the binary data, videobuf, into a avi_header */
	avi_header* avih = (avi_header*) videobuf;
	printf("reserved1: %x\n", avih->reserved1);
	
	return 0;
	// ./videotest AVI breakingbad.avi
}