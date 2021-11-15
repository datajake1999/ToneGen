#include <stdio.h>
#include <stdlib.h>
#include "ToneGenerator.h"
#include "wav_writer.h"

int main(int argc, char *argv[])
{
	unsigned int samplerate;
	float volume;
	unsigned int milliseconds;
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
	printf("Enter WAV file name.\n");
	scanf("%s", filename);
	printf("Creating waveform.\n");
	ToneGeneratorInit(&tonegen);
	ToneGeneratorSetWaveType(&tonegen, WaveTypeDTMF);
	ToneGeneratorSetSampleRate(&tonegen, samplerate);
	ToneGeneratorSetAmplitude(&tonegen, volume);
	numsamples = ToneGeneratorMillis2Samples(&tonegen, milliseconds);
	samples = malloc(numsamples*2);
	WavFileOpen(filename, samplerate, 16, 1, 1);
	for (i = DTMF0; i < DTMFTones; i++)
	{
		ToneGeneratorSetDigit(&tonegen, i);
		ToneGeneratorFillShortBuffer(&tonegen, samples, numsamples);
		WavFileWrite(samples, numsamples);
	}
	WavFileClose();
	free(samples);
	ToneGeneratorFree(&tonegen);
	printf("Done.\n");
	return 0;
}
