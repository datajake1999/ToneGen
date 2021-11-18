#ifndef TONEGENERATOR_H
#define TONEGENERATOR_H

enum
{
	WaveTypeSilence = 0,
	WaveTypeSine,
	WaveTypeSquare,
	WaveTypeTriangle,
	WaveTypeSawtooth,
	WaveTypeNoise,
	WaveTypeDTMF,
	WaveTypes
};

enum
{
	DTMF0 = 0,
	DTMF1,
	DTMF2,
	DTMF3,
	DTMF4,
	DTMF5,
	DTMF6,
	DTMF7,
	DTMF8,
	DTMF9,
	DTMFA,
	DTMFB,
	DTMFC,
	DTMFD,
	DTMFSTAR,
	DTMFHASH,
	DTMFTones
};

#ifdef __cplusplus
extern "C" {
#endif

	typedef struct
	{
		unsigned int WaveType;
		double SampleRate;
		double Frequency;
		double Amplitude;
		double PhaseOffset;
		double PulseWidth;
		double Angle;
		double Step;
		unsigned int Digit;
		double DTMFFrequency1;
		double DTMFAngle1;
		double DTMFStep1;
		double DTMFFrequency2;
		double DTMFAngle2;
		double DTMFStep2;
	}ToneGenerator;

	typedef struct
	{
		signed char Data[3];
	}Sample24;

	void ToneGeneratorInit(ToneGenerator *tg);
	void ToneGeneratorSetWaveType(ToneGenerator *tg, unsigned int value);
	void ToneGeneratorSetSampleRate(ToneGenerator *tg, double value);
	void ToneGeneratorSetFrequency(ToneGenerator *tg, double value);
	void ToneGeneratorSetDigit(ToneGenerator *tg, unsigned int value);
	void ToneGeneratorSetAmplitude(ToneGenerator *tg, double value);
	void ToneGeneratorSetPhaseOffset(ToneGenerator *tg, double value);
	void ToneGeneratorSetPulseWidth(ToneGenerator *tg, double value);
	unsigned int ToneGeneratorGetWaveType(ToneGenerator *tg);
	double ToneGeneratorGetSampleRate(ToneGenerator *tg);
	double ToneGeneratorGetFrequency(ToneGenerator *tg);
	unsigned int ToneGeneratorGetDigit(ToneGenerator *tg);
	double ToneGeneratorGetAmplitude(ToneGenerator *tg);
	double ToneGeneratorGetPhaseOffset(ToneGenerator *tg);
	double ToneGeneratorGetPulseWidth(ToneGenerator *tg);
	void ToneGeneratorResetAngle(ToneGenerator *tg);
	const char *ToneGeneratorGetCurrentWaveName(ToneGenerator *tg);
	const char *ToneGeneratorGetCurrentDigitName(ToneGenerator *tg);
	double ToneGeneratorGenerate(ToneGenerator *tg);
	float ToneGeneratorGenerateFloat(ToneGenerator *tg);
	signed long ToneGeneratorGenerateLong(ToneGenerator *tg);
	Sample24 ToneGeneratorGenerate24(ToneGenerator *tg);
	signed short ToneGeneratorGenerateShort(ToneGenerator *tg);
	unsigned char ToneGeneratorGenerateChar(ToneGenerator *tg);
	void ToneGeneratorFillCharBuffer(ToneGenerator *tg, unsigned char *buffer, unsigned int length);
	void ToneGeneratorFillShortBuffer(ToneGenerator *tg, signed short *buffer, unsigned int length);
	void ToneGeneratorFill24Buffer(ToneGenerator *tg, Sample24 *buffer, unsigned int length);
	void ToneGeneratorFillLongBuffer(ToneGenerator *tg, signed long *buffer, unsigned int length);
	void ToneGeneratorFillFloatBuffer(ToneGenerator *tg, float *buffer, unsigned int length);
	void ToneGeneratorFillDoubleBuffer(ToneGenerator *tg, double *buffer, unsigned int length);
	unsigned int ToneGeneratorMillis2Samples(ToneGenerator *tg, unsigned int Millis);

#ifdef __cplusplus
}
#endif

#endif //TONEGENERATOR_H
