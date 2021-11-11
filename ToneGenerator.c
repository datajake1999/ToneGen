#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif
const double twopi = 2 * M_PI;
#include "ToneGenerator.h"

void ToneGeneratorInit(ToneGenerator *tg)
{
	if (!tg)
	{
		return;
	}
	tg->WaveType = WaveTypeSine;
	tg->SampleRate = 44100;
	tg->Frequency = 440;
	tg->Amplitude = 0.5;
	tg->PhaseOffset = 0;
	tg->Angle = 0;
	tg->Step = twopi * tg->Frequency / tg->SampleRate;
	tg->LookupTable = NULL;
	tg->LookupWaveType = 0;
	tg->LookupSampleRate = 0;
	tg->LookupFrequency = 0;
	tg->LookupAmplitude = 0;
	tg->LookupPhaseOffset = 0;
	tg->LookupSize = 0;
	tg->LookupPosition = 0;
}

void ToneGeneratorFree(ToneGenerator *tg)
{
	if (!tg)
	{
		return;
	}
	ToneGeneratorClearLookup(tg);
	memset(tg, 0, sizeof(tg));
}

void ToneGeneratorReset(ToneGenerator *tg)
{
	if (!tg)
	{
		return;
	}
	ToneGeneratorFree(tg);
	ToneGeneratorInit(tg);
}

void ToneGeneratorSetWaveType(ToneGenerator *tg, unsigned int value)
{
	if (!tg)
	{
		return;
	}
	tg->WaveType = value%WaveTypes;
}

void ToneGeneratorSetSampleRate(ToneGenerator *tg, double value)
{
	if (!tg)
	{
		return;
	}
	tg->SampleRate = value;
	tg->Step = twopi * tg->Frequency / tg->SampleRate;
}

void ToneGeneratorSetFrequency(ToneGenerator *tg, double value)
{
	if (!tg)
	{
		return;
	}
	tg->Frequency = value;
	if (tg->Frequency > tg->SampleRate / 2)
	{
		tg->Frequency = tg->SampleRate / 2;
	}
	else if (tg->Frequency < 0)
	{
		tg->Frequency = 0;
	}
	tg->Step = twopi * tg->Frequency / tg->SampleRate;
}

void ToneGeneratorSetAmplitude(ToneGenerator *tg, double value)
{
	if (!tg)
	{
		return;
	}
	tg->Amplitude = value;
	if (tg->Amplitude > 1)
	{
		tg->Amplitude = 1;
	}
	else if (tg->Amplitude < 0)
	{
		tg->Amplitude = 0;
	}
}

void ToneGeneratorSetPhaseOffset(ToneGenerator *tg, double value)
{
	if (!tg)
	{
		return;
	}
	tg->PhaseOffset = value * (twopi / 360);
	if (tg->PhaseOffset > twopi)
	{
		tg->PhaseOffset = twopi;
	}
	else if (tg->PhaseOffset < 0)
	{
		tg->PhaseOffset = 0;
	}
}

unsigned int ToneGeneratorGetWaveType(ToneGenerator *tg)
{
	if (!tg)
	{
		return 0;
	}
	return tg->WaveType;
}

double ToneGeneratorGetSampleRate(ToneGenerator *tg)
{
	if (!tg)
	{
		return 0;
	}
	return tg->SampleRate;
}

double ToneGeneratorGetFrequency(ToneGenerator *tg)
{
	if (!tg)
	{
		return 0;
	}
	return tg->Frequency;
}

double ToneGeneratorGetAmplitude(ToneGenerator *tg)
{
	if (!tg)
	{
		return 0;
	}
	return tg->Amplitude;
}

double ToneGeneratorGetPhaseOffset(ToneGenerator *tg)
{
	if (!tg)
	{
		return 0;
	}
	return (tg->PhaseOffset * 360) / twopi;
}

void ToneGeneratorResetAngle(ToneGenerator *tg)
{
	if (!tg)
	{
		return;
	}
	tg->Angle = 0;
}

const char *ToneGeneratorGetCurrentWaveName(ToneGenerator *tg)
{
	if (!tg)
	{
		return NULL;
	}
	switch(tg->WaveType)
	{
	case WaveTypeSilence:
		return "Silence";
	case WaveTypeSine:
		return "Sine";
	case WaveTypeSquare:
		return "Square";
	case WaveTypeTriangle:
		return "Triangle";
	case WaveTypeSawtooth:
		return "Sawtooth";
	case WaveTypeNoise:
		return "Noise";
	default:
		return NULL;
	}
}

double ToneGeneratorGenerate(ToneGenerator *tg)
{
	double Waveform;
	if (!tg)
	{
		return 0;
	}
	Waveform = 0;
	switch(tg->WaveType)
	{
	default:
	case WaveTypeSilence:
		break;
	case WaveTypeSine:
		Waveform = sin(tg->Angle + tg->PhaseOffset);
		break;
	case WaveTypeSquare:
		if (tg->Angle >= M_PI)
		{
			Waveform = -1;
		}
		else
		{
			Waveform = 1;
		}
		break;
	case WaveTypeTriangle:
		Waveform = 2.0 * tg->Angle / M_PI - 1.0;
		if (Waveform > 1.0)
		{
			Waveform = 2.0 - Waveform;
		}
		break;
	case WaveTypeSawtooth:
		Waveform = tg->Angle / M_PI - 1.0;
		break;
	case WaveTypeNoise:
		Waveform = rand() / (double)RAND_MAX;
		break;
	}
	tg->Angle += tg->Step;
	if (tg->Angle >= twopi)
	{
		tg->Angle -= twopi;
	}
	return tg->Amplitude * Waveform;
}

float ToneGeneratorGenerateFloat(ToneGenerator *tg)
{
	if (!tg)
	{
		return 0;
	}
	return (float)ToneGeneratorGenerate(tg);
}

signed long ToneGeneratorGenerateLong(ToneGenerator *tg)
{
	double Sample;
	if (!tg)
	{
		return 0;
	}
	Sample = ToneGeneratorGenerate(tg) * 2147483648;
	if (Sample >= 0)
	{
		Sample = floor(Sample + 0.5);
	}
	else
	{
		Sample = ceil(Sample - 0.5);
	}
	if (Sample > 2147483647)
	{
		Sample = 2147483647;
	}
	else if (Sample < -2147483648)
	{
		Sample = -2147483648;
	}
	return (signed long)Sample;
}

Sample24 ToneGeneratorGenerate24(ToneGenerator *tg)
{
	Sample24 S24;
	signed long Intermediate;
	double Sample;
	if (!tg)
	{
		memset(&S24, 0, sizeof(S24));
		return S24;
	}
	Sample = ToneGeneratorGenerate(tg) * 8388608;
	if (Sample >= 0)
	{
		Sample = floor(Sample + 0.5);
	}
	else
	{
		Sample = ceil(Sample - 0.5);
	}
	if (Sample > 8388607)
	{
		Sample = 8388607;
	}
	else if (Sample < -8388608)
	{
		Sample = -8388608;
	}
	Intermediate = (signed long)Sample;
	S24.Data[0] = Intermediate & 0xFF;
	S24.Data[1] = (Intermediate >> 8) & 0xFF;
	S24.Data[2] = (Intermediate >> 16) & 0xFF;
	return S24;
}

signed short ToneGeneratorGenerateShort(ToneGenerator *tg)
{
	double Sample;
	if (!tg)
	{
		return 0;
	}
	Sample = ToneGeneratorGenerate(tg) * 32768;
	if (Sample >= 0)
	{
		Sample = floor(Sample + 0.5);
	}
	else
	{
		Sample = ceil(Sample - 0.5);
	}
	if (Sample > 32767)
	{
		Sample = 32767;
	}
	else if (Sample < -32768)
	{
		Sample = -32768;
	}
	return (signed short)Sample;
}

unsigned char ToneGeneratorGenerateChar(ToneGenerator *tg)
{
	double Sample;
	if (!tg)
	{
		return 128;
	}
	Sample = ToneGeneratorGenerate(tg) * 128;
	if (Sample >= 0)
	{
		Sample = floor(Sample + 0.5);
	}
	else
	{
		Sample = ceil(Sample - 0.5);
	}
	if (Sample > 127)
	{
		Sample = 127;
	}
	else if (Sample < -128)
	{
		Sample = -128;
	}
	return (unsigned char)Sample + 128;
}

void ToneGeneratorCalculateLookup(ToneGenerator *tg)
{
	unsigned int i;
	if (!tg)
	{
		return;
	}
	if (tg->WaveType == tg->LookupWaveType && tg->SampleRate == tg->LookupSampleRate && tg->Frequency == tg->LookupFrequency && tg->Amplitude == tg->LookupAmplitude && tg->PhaseOffset == tg->LookupPhaseOffset)
	{
		return;
	}
	ToneGeneratorClearLookup(tg);
	tg->LookupWaveType = tg->WaveType;
	tg->LookupSampleRate = tg->SampleRate;
	tg->LookupFrequency = tg->Frequency;
	tg->LookupAmplitude = tg->Amplitude;
	tg->LookupPhaseOffset = tg->PhaseOffset;
	tg->LookupSize = (unsigned int)floor((tg->LookupSampleRate/tg->LookupFrequency)+0.5);
	if (tg->LookupSize < 2)
	{
		tg->LookupSize = 2;
	}
	tg->LookupTable = (signed short*)malloc(tg->LookupSize*2);
	if (!tg->LookupTable)
	{
		return;
	}
	ToneGeneratorResetAngle(tg);
	for (i = 0; i < tg->LookupSize; i++)
	{
		tg->LookupTable[i] = ToneGeneratorGenerateShort(tg);
	}
	ToneGeneratorResetAngle(tg);
	tg->LookupPosition = 0;
}

void ToneGeneratorClearLookup(ToneGenerator *tg)
{
	if (!tg)
	{
		return;
	}
	if (tg->LookupTable)
	{
		memset(tg->LookupTable, 0, 2*tg->LookupSize);
		free(tg->LookupTable);
		tg->LookupTable = NULL;
	}
	tg->LookupWaveType = 0;
	tg->LookupSampleRate = 0;
	tg->LookupFrequency = 0;
	tg->LookupAmplitude = 0;
	tg->LookupPhaseOffset = 0;
	tg->LookupSize = 0;
	tg->LookupPosition = 0;
}

void ToneGeneratorSaveLookup(ToneGenerator *tg, const char *filename)
{
	FILE *out;
	if (!tg)
	{
		return;
	}
	if (!tg->LookupTable)
	{
		return;
	}
	out = fopen(filename, "wb");
	if (!out)
	{
		return;
	}
	fwrite(tg->LookupTable, 2, tg->LookupSize, out);
	fclose(out);
}

signed short ToneGeneratorGenerateLookup(ToneGenerator *tg)
{
	signed short Sample;
	if (!tg)
	{
		return 0;
	}
	if (!tg->LookupTable)
	{
		return 0;
	}
	Sample = tg->LookupTable[tg->LookupPosition];
	tg->LookupPosition++;
	if (tg->LookupPosition >= tg->LookupSize)
	{
		tg->LookupPosition -= tg->LookupSize;
	}
	return Sample;
}

void ToneGeneratorFillCharBuffer(ToneGenerator *tg, unsigned char *buffer, unsigned int length)
{
	unsigned int i;
	if (!tg)
	{
		return;
	}
	if (!buffer)
	{
		return;
	}
	for (i = 0; i < length; i++)
	{
		buffer[i] = ToneGeneratorGenerateChar(tg);
	}
}

void ToneGeneratorFillShortBuffer(ToneGenerator *tg, signed short *buffer, unsigned int length, unsigned int lookup)
{
	unsigned int i;
	if (!tg)
	{
		return;
	}
	if (!buffer)
	{
		return;
	}
	for (i = 0; i < length; i++)
	{
		if (lookup)
		{
			buffer[i] = ToneGeneratorGenerateLookup(tg);
		}
		else
		{
			buffer[i] = ToneGeneratorGenerateShort(tg);
		}
	}
}

void ToneGeneratorFill24Buffer(ToneGenerator *tg, Sample24 *buffer, unsigned int length)
{
	unsigned int i;
	if (!tg)
	{
		return;
	}
	if (!buffer)
	{
		return;
	}
	for (i = 0; i < length; i++)
	{
		buffer[i] = ToneGeneratorGenerate24(tg);
	}
}

void ToneGeneratorFillLongBuffer(ToneGenerator *tg, signed long *buffer, unsigned int length)
{
	unsigned int i;
	if (!tg)
	{
		return;
	}
	if (!buffer)
	{
		return;
	}
	for (i = 0; i < length; i++)
	{
		buffer[i] = ToneGeneratorGenerateLong(tg);
	}
}

void ToneGeneratorFillFloatBuffer(ToneGenerator *tg, float *buffer, unsigned int length)
{
	unsigned int i;
	if (!tg)
	{
		return;
	}
	if (!buffer)
	{
		return;
	}
	for (i = 0; i < length; i++)
	{
		buffer[i] = ToneGeneratorGenerateFloat(tg);
	}
}

void ToneGeneratorFillDoubleBuffer(ToneGenerator *tg, double *buffer, unsigned int length)
{
	unsigned int i;
	if (!tg)
	{
		return;
	}
	if (!buffer)
	{
		return;
	}
	for (i = 0; i < length; i++)
	{
		buffer[i] = ToneGeneratorGenerate(tg);
	}
}

unsigned int ToneGeneratorMillis2Samples(ToneGenerator *tg, unsigned int Millis)
{
	if (!tg)
	{
		return 0;
	}
	return (unsigned int)floor((Millis/1000.0)*tg->SampleRate);
}
