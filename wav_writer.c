#include "wav_writer.h"
#include <stdio.h>
#include <string.h>

static FILE *out;

static wav_header head;

static int fileexists(const char * filename)
{
	FILE *check;
	if (check = fopen(filename, "r"))
	{
		fclose(check);
		return 1;
	}
	return 0;
}

void WavFileOpen(const char *filename, unsigned int rate, unsigned int bits, unsigned int channels, unsigned int format)
{
	if (out == NULL)
	{
		if (fileexists(filename) == 1)
		{
			printf("%s already exists.\n", filename);
			return;
		}
		out = fopen(filename, "wb");
		if (out == NULL)
		{
			printf("Failed to open %s.\n", filename);
			return;
		}
	}
	else
	{
		rewind(out);
	}
	strncpy(head.riff_header,"RIFF",4);
	head.wav_size = sizeof(head)-8;
	strncpy(head.wave_header,"WAVE",4);
	strncpy(head.fmt_header,"fmt ",4);
	head.fmt_chunk_size = 16;
	head.audio_format = format;
	head.num_channels = channels;
	head.sample_rate = rate;
	head.byte_rate = bits / 8 * channels * rate;
	head.sample_alignment = bits / 8 * channels;
	head.bit_depth = bits;
	strncpy(head.data_header,"data",4);
	head.data_bytes = 0;
	fwrite(&head, sizeof(head), 1, out);
}

void WavFileWrite(void *buffer, unsigned int length)
{
	if (out == NULL)
	{
		return;
	}
	fwrite(buffer, head.sample_alignment, length, out);
}

void WavFileClose()
{
	unsigned int size;
	if (out == NULL)
	{
		return;
	}
	size = ftell(out);
	head.wav_size = size-8;
	head.data_bytes = size-sizeof(head);
	fseek(out, 0, SEEK_SET);
	fwrite(&head, sizeof(head), 1, out);
	fclose(out);
	out = NULL;
}
