#include <stdio.h>
#include <stdlib.h>
#include "ToneGenerator.h"
#include "wav_writer.h"

int main(int argc, char *argv[])
{
	unsigned int wavetype;
	unsigned int samplerate;
	float freqstart;
	float freqend;
	float freqstep;
	float currfreq;
	float volstart;
	float volend;
	float volstep;
	float currvol;
	float phaseoffset;
	unsigned int milliseconds;
	unsigned int i;
	char filename[100];
	ToneGenerator tonegen;
	unsigned int numsamples;
	signed short *samples;
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
	printf("Enter starting frequency in hZ.\n");
	scanf("%f", &freqstart);
	printf("Enter ending frequency in hZ.\n");
	scanf("%f", &freqend);
	printf("Enter starting volume from 0 to 1.\n");
	scanf("%f", &volstart);
	printf("Enter ending volume from 0 to 1.\n");
	scanf("%f", &volend);
	printf("Enter phase offset in degrees.\n");
	scanf("%f", &phaseoffset);
	printf("Enter duration in mS.\n");
	scanf("%d", &milliseconds);
	printf("Creating waveform.\n");
	ToneGeneratorInit(&tonegen);
	ToneGeneratorSetWaveType(&tonegen, wavetype);
	ToneGeneratorSetSampleRate(&tonegen, samplerate);
	ToneGeneratorSetPhaseOffset(&tonegen, phaseoffset);
	numsamples = ToneGeneratorMillis2Samples(&tonegen, milliseconds);
	samples = malloc(numsamples*2);
	freqstep = (freqend - freqstart) / numsamples;
	currfreq = freqstart;
	ToneGeneratorSetFrequency(&tonegen, currfreq);
	volstep = (volend - volstart) / numsamples;
	currvol = volstart;
	ToneGeneratorSetAmplitude(&tonegen, currvol);
	for (i = 0; i < numsamples; i++)
	{
		samples[i] = ToneGeneratorGenerateShort(&tonegen);
		currfreq += freqstep;
		ToneGeneratorSetFrequency(&tonegen, currfreq);
		currvol += volstep;
		ToneGeneratorSetAmplitude(&tonegen, currvol);
	}
	printf("Enter WAV file name.\n");
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
