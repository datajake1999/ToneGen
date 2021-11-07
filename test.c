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
	unsigned int lookup;
	char filename[100];
	ToneGenerator tonegen;
	unsigned int numsamples;
	signed short *samples;
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
	printf("Type 1 to use a single cycle lookup table, or 0 to calculate the entire waveform.\n");
	scanf("%d", &lookup);
	printf("Creating waveform.\n");
	ToneGeneratorInit(&tonegen);
	ToneGeneratorSetWaveType(&tonegen, wavetype);
	ToneGeneratorSetSampleRate(&tonegen, samplerate);
	ToneGeneratorSetFrequency(&tonegen, frequency);
	ToneGeneratorSetAmplitude(&tonegen, volume);
	ToneGeneratorSetPhaseOffset(&tonegen, phaseoffset);
	numsamples = ToneGeneratorMillis2Samples(&tonegen, milliseconds);
	samples = (signed short*)malloc(numsamples*2);
	if (lookup)
	{
		ToneGeneratorCalculateLookup(&tonegen);
	}
	ToneGeneratorFillBuffer(&tonegen, samples, numsamples, lookup);
	printf("Enter the file name.\n");
	scanf("%s", filename);
	printf("Writing output to %s.\n", filename);
	WavFileOpen(filename, samplerate, 16, 1, 1);
	WavFileWrite(samples, numsamples);
	WavFileClose();
	free(samples);
	ToneGeneratorFree(&tonegen);
	printf("Done.\n");
	return 0;
}
