#include <stdio.h>
#include <stdlib.h>
#include "DTMFGenerator.h"
#include "wav_writer.h"

int main(int argc, char *argv[])
{
	unsigned int samplerate;
	float volume;
	unsigned int milliseconds;
	unsigned int format;
	char filename[100];
	DTMFGenerator dtmfgen;
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
	DTMFGeneratorInit(&dtmfgen);
	DTMFGeneratorSetSampleRate(&dtmfgen, samplerate);
	DTMFGeneratorSetAmplitude(&dtmfgen, volume);
	numsamples = DTMFGeneratorMillis2Samples(&dtmfgen, milliseconds);
	if (format == 1)
	{
		samples = malloc(numsamples*2);
		WavFileOpen(filename, samplerate, 16, 1, 1);
		for (i = DTMF0; i < DTMFTones; i++)
		{
			DTMFGeneratorSetDigit(&dtmfgen, i);
			DTMFGeneratorFillShortBuffer(&dtmfgen, samples, numsamples);
			WavFileWrite(samples, numsamples);
		}
	}
	else if (format == 2)
	{
		samples = malloc(numsamples*3);
		WavFileOpen(filename, samplerate, 24, 1, 1);
		for (i = DTMF0; i < DTMFTones; i++)
		{
			DTMFGeneratorSetDigit(&dtmfgen, i);
			DTMFGeneratorFill24Buffer(&dtmfgen, samples, numsamples);
			WavFileWrite(samples, numsamples);
		}
	}
	else if (format == 3)
	{
		samples = malloc(numsamples*4);
		WavFileOpen(filename, samplerate, 32, 1, 1);
		for (i = DTMF0; i < DTMFTones; i++)
		{
			DTMFGeneratorSetDigit(&dtmfgen, i);
			DTMFGeneratorFillLongBuffer(&dtmfgen, samples, numsamples);
			WavFileWrite(samples, numsamples);
		}
	}
	else if (format == 4)
	{
		samples = malloc(numsamples*4);
		WavFileOpen(filename, samplerate, 32, 1, 3);
		for (i = DTMF0; i < DTMFTones; i++)
		{
			DTMFGeneratorSetDigit(&dtmfgen, i);
			DTMFGeneratorFillFloatBuffer(&dtmfgen, samples, numsamples);
			WavFileWrite(samples, numsamples);
		}
	}
	else if (format == 5)
	{
		samples = malloc(numsamples*8);
		WavFileOpen(filename, samplerate, 64, 1, 3);
		for (i = DTMF0; i < DTMFTones; i++)
		{
			DTMFGeneratorSetDigit(&dtmfgen, i);
			DTMFGeneratorFillDoubleBuffer(&dtmfgen, samples, numsamples);
			WavFileWrite(samples, numsamples);
		}
	}
	else
	{
		samples = malloc(numsamples);
		WavFileOpen(filename, samplerate, 8, 1, 1);
		for (i = DTMF0; i < DTMFTones; i++)
		{
			DTMFGeneratorSetDigit(&dtmfgen, i);
			DTMFGeneratorFillCharBuffer(&dtmfgen, samples, numsamples);
			WavFileWrite(samples, numsamples);
		}
	}
	printf("Writing output to %s.\n", filename);
	WavFileClose();
	free(samples);
	DTMFGeneratorFree(&dtmfgen);
	printf("Done.\n");
	return 0;
}
