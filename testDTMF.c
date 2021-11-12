#include <stdio.h>
#include <stdlib.h>
#include "ToneGenerator.h"
#include "wav_writer.h"

int main(int argc, char *argv[])
{
	unsigned int samplerate;
	float volume;
	unsigned int milliseconds;
	unsigned int format;
	char filename[100];
	ToneGenerator tonegen;
	unsigned int numsamples;
	void *samples;
	unsigned int i;
	printf("Enter sample rate in hZ.\n");
	scanf("%d", &samplerate);
	printf("Enter volume from 0 to 1.\n");
	scanf("%f", &volume);
	printf("Enter duration of each tone in mS.\n");
	scanf("%d", &milliseconds);
	printf("Enter audio format.\n");
	printf("0 = 8 bit PCM.\n");
	printf("1 = 16 bit PCM.\n");
	printf("2 = 24 bit PCM.\n");
	printf("3 = 32 bit PCM.\n");
	printf("4 = 32 bit float.\n");
	printf("5 = 64 bit float.\n");
	scanf("%d", &format);
	printf("Enter WAV file name.\n");
	scanf("%s", filename);
	printf("Creating waveform.\n");
	ToneGeneratorInit(&tonegen);
	ToneGeneratorSetWaveType(&tonegen, WaveTypeDTMF);
	ToneGeneratorSetSampleRate(&tonegen, samplerate);
	ToneGeneratorSetAmplitude(&tonegen, volume);
	numsamples = ToneGeneratorMillis2Samples(&tonegen, milliseconds);
	if (format == 1)
	{
		samples = malloc(numsamples*2);
		WavFileOpen(filename, samplerate, 16, 1, 1);
		for (i = DTMF0; i < DTMFTones; i++)
		{
			ToneGeneratorSetDigit(&tonegen, i);
			ToneGeneratorFillShortBuffer(&tonegen, samples, numsamples, 0);
			WavFileWrite(samples, numsamples);
		}
	}
	else if (format == 2)
	{
		samples = malloc(numsamples*3);
		WavFileOpen(filename, samplerate, 24, 1, 1);
		for (i = DTMF0; i < DTMFTones; i++)
		{
			ToneGeneratorSetDigit(&tonegen, i);
			ToneGeneratorFill24Buffer(&tonegen, samples, numsamples);
			WavFileWrite(samples, numsamples);
		}
	}
	else if (format == 3)
	{
		samples = malloc(numsamples*4);
		WavFileOpen(filename, samplerate, 32, 1, 1);
		for (i = DTMF0; i < DTMFTones; i++)
		{
			ToneGeneratorSetDigit(&tonegen, i);
			ToneGeneratorFillLongBuffer(&tonegen, samples, numsamples);
			WavFileWrite(samples, numsamples);
		}
	}
	else if (format == 4)
	{
		samples = malloc(numsamples*4);
		WavFileOpen(filename, samplerate, 32, 1, 3);
		for (i = DTMF0; i < DTMFTones; i++)
		{
			ToneGeneratorSetDigit(&tonegen, i);
			ToneGeneratorFillFloatBuffer(&tonegen, samples, numsamples);
			WavFileWrite(samples, numsamples);
		}
	}
	else if (format == 5)
	{
		samples = malloc(numsamples*8);
		WavFileOpen(filename, samplerate, 64, 1, 3);
		for (i = DTMF0; i < DTMFTones; i++)
		{
			ToneGeneratorSetDigit(&tonegen, i);
			ToneGeneratorFillDoubleBuffer(&tonegen, samples, numsamples);
			WavFileWrite(samples, numsamples);
		}
	}
	else
	{
		samples = malloc(numsamples);
		WavFileOpen(filename, samplerate, 8, 1, 1);
		for (i = DTMF0; i < DTMFTones; i++)
		{
			ToneGeneratorSetDigit(&tonegen, i);
			ToneGeneratorFillCharBuffer(&tonegen, samples, numsamples);
			WavFileWrite(samples, numsamples);
		}
	}
	printf("Writing output to %s.\n", filename);
	WavFileClose();
	free(samples);
	ToneGeneratorFree(&tonegen);
	printf("Done.\n");
	return 0;
}
