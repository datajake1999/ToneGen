#include <stdio.h>
#include <stdlib.h>
#include <time.h>
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
	clock_t begin;
	clock_t end;
	double time_spent;
	printf("Enter waveform type.\n");
	printf("0 = silence.\n");
	printf("1 = sine.\n");
	printf("2 = square.\n");
	printf("3 = triangle.\n");
	printf("4 = sawtooth.\n");
	printf("5 = noise.\n");
	scanf("%d", &wavetype);
	printf("Enter sample rate in hZ.\n");
	scanf("%d", &samplerate);
	printf("Enter frequency in hZ.\n");
	scanf("%f", &frequency);
	printf("Enter volume from 0 to 1.\n");
	scanf("%f", &volume);
	printf("Enter phase offset in degrees.\n");
	scanf("%f", &phaseoffset);
	printf("Enter duration in mS.\n");
	scanf("%d", &milliseconds);
	printf("Enter audio format.\n");
	printf("0 = 8 bit PCM.\n");
	printf("1 = 16 bit PCM.\n");
	printf("2 = 24 bit PCM.\n");
	printf("3 = 32 bit PCM.\n");
	printf("4 = 32 bit float.\n");
	printf("5 = 64 bit float.\n");
	scanf("%d", &format);
	if (format == 1)
	{
		printf("Type 1 to use a single cycle lookup table, or 0 to calculate the entire waveform.\n");
		scanf("%d", &lookup);
	}
	printf("Creating waveform.\n");
	begin = clock();
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
		ToneGeneratorFillLongBuffer(&tonegen, samples, numsamples);
	}
	else if (format == 4)
	{
		samples = malloc(numsamples*4);
		ToneGeneratorFillFloatBuffer(&tonegen, samples, numsamples);
	}
	else if (format == 5)
	{
		samples = malloc(numsamples*8);
		ToneGeneratorFillDoubleBuffer(&tonegen, samples, numsamples);
	}
	else
	{
		samples = malloc(numsamples);
		ToneGeneratorFillCharBuffer(&tonegen, samples, numsamples);
	}
	end = clock();
	time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
	printf("Execution time: %lf seconds.\n", time_spent);
	printf("Enter WAV file name.\n");
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
		WavFileOpen(filename, samplerate, 32, 1, 1);
	}
	else if (format == 4)
	{
		WavFileOpen(filename, samplerate, 32, 1, 3);
	}
	else if (format == 5)
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
