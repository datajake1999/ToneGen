#include <stdlib.h>
#include <string.h>

//#define lookup
#ifdef lookup
#include "sinetab.h"
const double pi = TableSize / 2;
const double twopi = TableSize;
#else
#include <math.h>
#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif
const double pi = M_PI;
const double twopi = 2 * M_PI;
#endif

#include "ToneGenerator.h"

void ToneGeneratorInit(ToneGenerator *tg)
{
	if (!tg)
	{
		return;
	}
	ToneGeneratorSetWaveType(tg, WaveTypeSine);
	ToneGeneratorSetSampleRate(tg, 44100);
	ToneGeneratorSetFrequency(tg, 440);
	ToneGeneratorSetDigit(tg, DTMF0);
	ToneGeneratorSetAmplitude(tg, 1);
	ToneGeneratorSetPhaseOffset(tg, 0);
	ToneGeneratorSetPulseWidth(tg, 0.5);
	ToneGeneratorResetAngle(tg);
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
	if (tg->Frequency > tg->SampleRate / 2)
	{
		tg->Frequency = tg->SampleRate / 2;
	}
	else if (tg->Frequency < 0)
	{
		tg->Frequency = 0;
	}
	tg->Step = twopi * tg->Frequency / tg->SampleRate;
	if (tg->DTMFFrequency1 > tg->SampleRate / 2)
	{
		tg->DTMFFrequency1 = tg->SampleRate / 2;
	}
	else if (tg->DTMFFrequency1 < 0)
	{
		tg->DTMFFrequency1 = 0;
	}
	tg->DTMFStep1 = twopi * tg->DTMFFrequency1 / tg->SampleRate;
	if (tg->DTMFFrequency2 > tg->SampleRate / 2)
	{
		tg->DTMFFrequency2 = tg->SampleRate / 2;
	}
	else if (tg->DTMFFrequency2 < 0)
	{
		tg->DTMFFrequency2 = 0;
	}
	tg->DTMFStep2 = twopi * tg->DTMFFrequency2 / tg->SampleRate;
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

void ToneGeneratorSetDigit(ToneGenerator *tg, unsigned int value)
{
	if (!tg)
	{
		return;
	}
	tg->Digit = value%DTMFTones;
	switch(tg->Digit)
	{
	default:
		tg->DTMFFrequency1 = 0;
		tg->DTMFFrequency2 = 0;
		break;
	case DTMF1:
		tg->DTMFFrequency1 = 1209;
		tg->DTMFFrequency2 = 697;
		break;
	case DTMF2:
		tg->DTMFFrequency1 = 1336;
		tg->DTMFFrequency2 = 697;
		break;
	case DTMF3:
		tg->DTMFFrequency1 = 1477;
		tg->DTMFFrequency2 = 697;
		break;
	case DTMF4:
		tg->DTMFFrequency1 = 1209;
		tg->DTMFFrequency2 = 770;
		break;
	case DTMF5:
		tg->DTMFFrequency1 = 1336;
		tg->DTMFFrequency2 = 770;
		break;
	case DTMF6:
		tg->DTMFFrequency1 = 1477;
		tg->DTMFFrequency2 = 770;
		break;
	case DTMF7:
		tg->DTMFFrequency1 = 1209;
		tg->DTMFFrequency2 = 852;
		break;
	case DTMF8:
		tg->DTMFFrequency1 = 1336;
		tg->DTMFFrequency2 = 852;
		break;
	case DTMF9:
		tg->DTMFFrequency1 = 1477;
		tg->DTMFFrequency2 = 852;
		break;
	case DTMFSTAR:
		tg->DTMFFrequency1 = 1209;
		tg->DTMFFrequency2 = 941;
		break;
	case DTMF0:
		tg->DTMFFrequency1 = 1336;
		tg->DTMFFrequency2 = 941;
		break;
	case DTMFHASH:
		tg->DTMFFrequency1 = 1477;
		tg->DTMFFrequency2 = 941;
		break;
	case DTMFA:
		tg->DTMFFrequency1 = 1633;
		tg->DTMFFrequency2 = 697;
		break;
	case DTMFB:
		tg->DTMFFrequency1 = 1633;
		tg->DTMFFrequency2 = 770;
		break;
	case DTMFC:
		tg->DTMFFrequency1 = 1633;
		tg->DTMFFrequency2 = 852;
		break;
	case DTMFD:
		tg->DTMFFrequency1 = 1633;
		tg->DTMFFrequency2 = 941;
		break;
	}
	if (tg->DTMFFrequency1 > tg->SampleRate / 2)
	{
		tg->DTMFFrequency1 = tg->SampleRate / 2;
	}
	else if (tg->DTMFFrequency1 < 0)
	{
		tg->DTMFFrequency1 = 0;
	}
	tg->DTMFStep1 = twopi * tg->DTMFFrequency1 / tg->SampleRate;
	if (tg->DTMFFrequency2 > tg->SampleRate / 2)
	{
		tg->DTMFFrequency2 = tg->SampleRate / 2;
	}
	else if (tg->DTMFFrequency2 < 0)
	{
		tg->DTMFFrequency2 = 0;
	}
	tg->DTMFStep2 = twopi * tg->DTMFFrequency2 / tg->SampleRate;
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

void ToneGeneratorSetPulseWidth(ToneGenerator *tg, double value)
{
	if (!tg)
	{
		return;
	}
	tg->PulseWidth = (value * twopi) - pi;
	if (tg->PulseWidth > pi)
	{
		tg->PulseWidth = pi;
	}
	else if (tg->PulseWidth < pi * -1)
	{
		tg->PulseWidth = pi * -1;
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

unsigned int ToneGeneratorGetDigit(ToneGenerator *tg)
{
	if (!tg)
	{
		return 0;
	}
	return tg->Digit;
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

double ToneGeneratorGetPulseWidth(ToneGenerator *tg)
{
	if (!tg)
	{
		return 0;
	}
	return (tg->PulseWidth + pi) / twopi;
}

void ToneGeneratorResetAngle(ToneGenerator *tg)
{
	if (!tg)
	{
		return;
	}
	tg->Angle = 0;
	tg->DTMFAngle1 = 0;
	tg->DTMFAngle2 = 0;
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
	case WaveTypeDTMF:
		return "DTMF";
	default:
		return NULL;
	}
}

const char *ToneGeneratorGetCurrentDigitName(ToneGenerator *tg)
{
	if (!tg)
	{
		return NULL;
	}
	switch(tg->Digit)
	{
	case DTMF1:
		return "1";
	case DTMF2:
		return "2";
	case DTMF3:
		return "3";
	case DTMF4:
		return "4";
	case DTMF5:
		return "5";
	case DTMF6:
		return "6";
	case DTMF7:
		return "7";
	case DTMF8:
		return "8";
	case DTMF9:
		return "9";
	case DTMFSTAR:
		return "*";
	case DTMF0:
		return "0";
	case DTMFHASH:
		return "#";
	case DTMFA:
		return "A";
	case DTMFB:
		return "B";
	case DTMFC:
		return "C";
	case DTMFD:
		return "D";
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
#ifdef lookup
		Waveform = SineTable[(unsigned int)(tg->Angle + tg->PhaseOffset)%(unsigned int)TableSize];
#else
		Waveform = sin(tg->Angle + tg->PhaseOffset);
#endif
		break;
	case WaveTypeSquare:
		if ((tg->Angle + tg->PulseWidth) >= pi)
		{
			Waveform = -1;
		}
		else
		{
			Waveform = 1;
		}
		break;
	case WaveTypeTriangle:
		Waveform = 2.0 * tg->Angle / pi - 1.0;
		if (Waveform > 1.0)
		{
			Waveform = 2.0 - Waveform;
		}
		break;
	case WaveTypeSawtooth:
		Waveform = tg->Angle / pi - 1.0;
		break;
	case WaveTypeNoise:
		Waveform = rand() / (double)RAND_MAX;
		break;
	case WaveTypeDTMF:
#ifdef lookup
		Waveform = (SineTable[(unsigned int)tg->DTMFAngle1] + SineTable[(unsigned int)tg->DTMFAngle2]) / 2;
#else
		Waveform = (sin(tg->DTMFAngle1) + sin(tg->DTMFAngle2)) / 2;
#endif
		tg->DTMFAngle1 += tg->DTMFStep1;
		if (tg->DTMFAngle1 >= twopi)
		{
			tg->DTMFAngle1 -= twopi;
		}
		tg->DTMFAngle2 += tg->DTMFStep2;
		if (tg->DTMFAngle2 >= twopi)
		{
			tg->DTMFAngle2 -= twopi;
		}
		break;
	}
	if (tg->WaveType >= WaveTypeSine && tg->WaveType <= WaveTypeSawtooth)
	{
		tg->Angle += tg->Step;
		if (tg->Angle >= twopi)
		{
			tg->Angle -= twopi;
		}
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
		Sample += 0.5;
	}
	else
	{
		Sample -= 0.5;
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
		Sample += 0.5;
	}
	else
	{
		Sample -= 0.5;
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
		Sample += 0.5;
	}
	else
	{
		Sample -= 0.5;
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
		Sample += 0.5;
	}
	else
	{
		Sample -= 0.5;
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

void ToneGeneratorFillCharBuffer(ToneGenerator *tg, unsigned char *buffer, unsigned int length)
{
	unsigned int i;
	if (!tg || !buffer)
	{
		return;
	}
	for (i = 0; i < length; i++)
	{
		buffer[i] = ToneGeneratorGenerateChar(tg);
	}
}

void ToneGeneratorFillShortBuffer(ToneGenerator *tg, signed short *buffer, unsigned int length)
{
	unsigned int i;
	if (!tg || !buffer)
	{
		return;
	}
	for (i = 0; i < length; i++)
	{
		buffer[i] = ToneGeneratorGenerateShort(tg);
	}
}

void ToneGeneratorFill24Buffer(ToneGenerator *tg, Sample24 *buffer, unsigned int length)
{
	unsigned int i;
	if (!tg || !buffer)
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
	if (!tg || !buffer)
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
	if (!tg || !buffer)
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
	if (!tg || !buffer)
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
	return (unsigned int)((Millis/1000.0)*tg->SampleRate);
}
