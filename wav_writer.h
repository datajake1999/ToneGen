#ifndef WAV_WRITER_H
#define WAV_WRITER_H

#include "wav_header.h"
#ifdef __cplusplus
extern "C" {
#endif
	void WavFileOpen(const char *filename, unsigned int rate, unsigned int bits, unsigned int channels, unsigned int format);
	void WavFileWrite(void *buffer, unsigned int length);
	void WavFileClose();
#ifdef __cplusplus
}
#endif

#endif //WAV_WRITER_H