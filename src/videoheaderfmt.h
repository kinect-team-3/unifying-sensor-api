#include <stdint.h>

#ifndef VIDEOHEADERFMT_H
#define VIDEOHEADERFMT_H

typedef struct {
	uint32_t microSecPerFrame;
	uint32_t maxBytesPerSec;
	uint32_t reserved1;
	uint32_t flags;
	uint32_t totalFrames;
	uint32_t initialFrames;
	uint32_t streams;
	uint32_t suggestedBufferSize;
	uint32_t width;
	uint32_t height;
	uint32_t reserved[4];
} __attribute((packed)) avi_header;

#endif