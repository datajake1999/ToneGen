#include <math.h>
#include <string.h>
#include "DTMFGenerator.h"

void DTMFGeneratorInit(DTMFGenerator *dg)
{
	if (!dg)
	{
		return;
	}
	ToneGeneratorInit(&dg->Gen1);
	ToneGeneratorInit(&dg->Gen2);
	DTMFGeneratorSetDigit(dg, DTMF0);
	DTMFGeneratorSetAmplitude(dg, 0.5);
}

void DTMFGeneratorFree(DTMFGenerator *dg)
{
	if (!dg)
	{
		return;
	}
	ToneGeneratorFree(&dg->Gen1);
	ToneGeneratorFree(&dg->Gen2);
	memset(dg, 0, sizeof(dg));
}

void DTMFGeneratorReset(DTMFGenerator *dg)
{
	if (!dg)
	{
		return;
	}
	DTMFGeneratorFree(dg);
	DTMFGeneratorInit(dg);
}

void DTMFGeneratorSetSampleRate(DTMFGenerator *dg, double value)
{
	if (!dg)
	{
		return;
	}
	dg->SampleRate = value;
	ToneGeneratorSetSampleRate(&dg->Gen1, value);
	ToneGeneratorSetSampleRate(&dg->Gen2, value);
}

void DTMFGeneratorSetDigit(DTMFGenerator *dg, unsigned int value)
{
	double Frequency1;
	double Frequency2;
	if (!dg)
	{
		return;
	}
	Frequency1 = 0;
	Frequency2 = 0;
	switch(value)
	{
	case DTMF1:
		Frequency1 = 1209;
		Frequency2 = 697;
		break;
	case DTMF2:
		Frequency1 = 1336;
		Frequency2 = 697;
		break;
	case DTMF3:
		Frequency1 = 1477;
		Frequency2 = 697;
		break;
	case DTMF4:
		Frequency1 = 1209;
		Frequency2 = 770;
		break;
	case DTMF5:
		Frequency1 = 1336;
		Frequency2 = 770;
		break;
	case DTMF6:
		Frequency1 = 1477;
		Frequency2 = 770;
		break;
	case DTMF7:
		Frequency1 = 1209;
		Frequency2 = 852;
		break;
	case DTMF8:
		Frequency1 = 1336;
		Frequency2 = 852;
		break;
	case DTMF9:
		Frequency1 = 1477;
		Frequency2 = 852;
		break;
	case DTMFSTAR:
		Frequency1 = 1209;
		Frequency2 = 941;
		break;
	case DTMF0:
		Frequency1 = 1336;
		Frequency2 = 941;
		break;
	case DTMFHASH:
		Frequency1 = 1477;
		Frequency2 = 941;
		break;
	case DTMFA:
		Frequency1 = 1633;
		Frequency2 = 697;
		break;
	case DTMFB:
		Frequency1 = 1633;
		Frequency2 = 770;
		break;
	case DTMFC:
		Frequency1 = 1633;
		Frequency2 = 852;
		break;
	case DTMFD:
		Frequency1 = 1633;
		Frequency2 = 941;
		break;
	}
	dg->Digit = value;
	ToneGeneratorSetFrequency(&dg->Gen1, Frequency1);
	ToneGeneratorSetFrequency(&dg->Gen2, Frequency2);
}

void DTMFGeneratorSetAmplitude(DTMFGenerator *dg, double value)
{
	if (!dg)
	{
		return;
	}
	dg->Amplitude = value;
	ToneGeneratorSetAmplitude(&dg->Gen1, value);
	ToneGeneratorSetAmplitude(&dg->Gen2, value);
}

double DTMFGeneratorGetSampleRate(DTMFGenerator *dg)
{
	if (!dg)
	{
		return 0;
	}
	return dg->SampleRate;
}

unsigned int DTMFGeneratorGetDigit(DTMFGenerator *dg)
{
	if (!dg)
	{
		return 0;
	}
	return dg->Digit;
}

double DTMFGeneratorGetAmplitude(DTMFGenerator *dg)
{
	if (!dg)
	{
		return 0;
	}
	return dg->Amplitude;
}

double DTMFGeneratorGenerate(DTMFGenerator *dg)
{
	double Waveform;
	if (!dg)
	{
		return 0;
	}
	Waveform = (ToneGeneratorGenerate(&dg->Gen1) + ToneGeneratorGenerate(&dg->Gen2)) / 2;
	return Waveform;
}

float DTMFGeneratorGenerateFloat(DTMFGenerator *dg)
{
	if (!dg)
	{
		return 0;
	}
	return (float)DTMFGeneratorGenerate(dg);
}

signed long DTMFGeneratorGenerateLong(DTMFGenerator *dg)
{
	double Sample;
	if (!dg)
	{
		return 0;
	}
	Sample = DTMFGeneratorGenerate(dg) * 2147483648;
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

Sample24 DTMFGeneratorGenerate24(DTMFGenerator *dg)
{
	Sample24 S24;
	signed long Intermediate;
	double Sample;
	if (!dg)
	{
		memset(&S24, 0, sizeof(S24));
		return S24;
	}
	Sample = DTMFGeneratorGenerate(dg) * 8388608;
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

signed short DTMFGeneratorGenerateShort(DTMFGenerator *dg)
{
	double Sample;
	if (!dg)
	{
		return 0;
	}
	Sample = DTMFGeneratorGenerate(dg) * 32768;
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

unsigned char DTMFGeneratorGenerateChar(DTMFGenerator *dg)
{
	double Sample;
	if (!dg)
	{
		return 128;
	}
	Sample = DTMFGeneratorGenerate(dg) * 128;
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

void DTMFGeneratorFillCharBuffer(DTMFGenerator *dg, unsigned char *buffer, unsigned int length)
{
	unsigned int i;
	if (!dg)
	{
		return;
	}
	if (!buffer)
	{
		return;
	}
	for (i = 0; i < length; i++)
	{
		buffer[i] = DTMFGeneratorGenerateChar(dg);
	}
}

void DTMFGeneratorFillShortBuffer(DTMFGenerator *dg, signed short *buffer, unsigned int length)
{
	unsigned int i;
	if (!dg)
	{
		return;
	}
	if (!buffer)
	{
		return;
	}
	for (i = 0; i < length; i++)
	{
		buffer[i] = DTMFGeneratorGenerateShort(dg);
	}
}

void DTMFGeneratorFill24Buffer(DTMFGenerator *dg, Sample24 *buffer, unsigned int length)
{
	unsigned int i;
	if (!dg)
	{
		return;
	}
	if (!buffer)
	{
		return;
	}
	for (i = 0; i < length; i++)
	{
		buffer[i] = DTMFGeneratorGenerate24(dg);
	}
}

void DTMFGeneratorFillLongBuffer(DTMFGenerator *dg, signed long *buffer, unsigned int length)
{
	unsigned int i;
	if (!dg)
	{
		return;
	}
	if (!buffer)
	{
		return;
	}
	for (i = 0; i < length; i++)
	{
		buffer[i] = DTMFGeneratorGenerateLong(dg);
	}
}

void DTMFGeneratorFillFloatBuffer(DTMFGenerator *dg, float *buffer, unsigned int length)
{
	unsigned int i;
	if (!dg)
	{
		return;
	}
	if (!buffer)
	{
		return;
	}
	for (i = 0; i < length; i++)
	{
		buffer[i] = DTMFGeneratorGenerateFloat(dg);
	}
}

void DTMFGeneratorFillDoubleBuffer(DTMFGenerator *dg, double *buffer, unsigned int length)
{
	unsigned int i;
	if (!dg)
	{
		return;
	}
	if (!buffer)
	{
		return;
	}
	for (i = 0; i < length; i++)
	{
		buffer[i] = DTMFGeneratorGenerate(dg);
	}
}

unsigned int DTMFGeneratorMillis2Samples(DTMFGenerator *dg, unsigned int Millis)
{
	if (!dg)
	{
		return 0;
	}
	return (unsigned int)floor((Millis/1000.0)*dg->SampleRate);
}
