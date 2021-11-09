#include <stdio.h>
#include <stdlib.h>
#include "ToneGenerator.h"
#include "wav_writer.h"

int main(int argc, char *argv[])
{
	unsigned int wavetype;
	unsigned int samplerate;
	float frequency;
	float volume;
	float phaseoffset;
	unsigned int milliseconds;
	unsigned int format;
	unsigned int lookup;
	char filename[100];
	ToneGenerator tonegen;
	unsigned int numsamples;
	void *samples;
	printf("Enter the wave type.\n");
	scanf("%d", &wavetype);
	printf("Enter the sample rate.\n");
	scanf("%d", &samplerate);
	printf("Enter the frequency.\n");
	scanf("%f", &frequency);
	printf("Enter the volume.\n");
	scanf("%f", &volume);
	printf("Enter the phase offset.\n");
	scanf("%f", &phaseoffset);
	printf("Enter the number of milliseconds.\n");
	scanf("%d", &milliseconds);
	printf("Enter the audio format.\n");
	scanf("%d", &format);
	if (format == 1)
	{
		printf("Type 1 to use a single cycle lookup table, or 0 to calculate the entire waveform.\n");
		scanf("%d", &lookup);
	}
	printf("Creating waveform.\n");
	ToneGeneratorInit(&tonegen);
	ToneGeneratorSetWaveType(&tonegen, wavetype);
	ToneGeneratorSetSampleRate(&tonegen, samplerate);
	ToneGeneratorSetFrequency(&tonegen, frequency);
	ToneGeneratorSetAmplitude(&tonegen, volume);
	ToneGeneratorSetPhaseOffset(&tonegen, phaseoffset);
	numsamples = ToneGeneratorMillis2Samples(&tonegen, milliseconds);
	if (format == 1)
	{
		samples = malloc(numsamples*2);
		if (lookup)
		{
			ToneGeneratorCalculateLookup(&tonegen);
		}
		ToneGeneratorFillShortBuffer(&tonegen, samples, numsamples, lookup);
	}
	else if (format == 2)
	{
		samples = malloc(numsamples*3);
		ToneGeneratorFill24Buffer(&tonegen, samples, numsamples);
	}
	else if (format == 3)
	{
		samples = malloc(numsamples*4);
		ToneGeneratorFillFloatBuffer(&tonegen, samples, numsamples);
	}
	else if (format == 4)
	{
		samples = malloc(numsamples*8);
		ToneGeneratorFillDoubleBuffer(&tonegen, samples, numsamples);
	}
	else
	{
		samples = malloc(numsamples);
		ToneGeneratorFillCharBuffer(&tonegen, samples, numsamples);
	}
	printf("Enter the file name.\n");
	scanf("%s", filename);
	printf("Writing output to %s.\n", filename);
	if (format == 1)
	{
		WavFileOpen(filename, samplerate, 16, 1, 1);
	}
	else if (format == 2)
	{
		WavFileOpen(filename, samplerate, 24, 1, 1);
	}
	else if (format == 3)
	{
		WavFileOpen(filename, samplerate, 32, 1, 3);
	}
	else if (format == 4)
	{
		WavFileOpen(filename, samplerate, 64, 1, 3);
	}
	else
	{
		WavFileOpen(filename, samplerate, 8, 1, 1);
	}
	WavFileWrite(samples, numsamples);
	WavFileClose();
	free(samples);
	ToneGeneratorFree(&tonegen);
	printf("Done.\n");
	return 0;
}
