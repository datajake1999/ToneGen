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
	WaveTypes,
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
		double Angle;
		double Step;
		signed short *LookupTable;
		unsigned int LookupWaveType;
		double LookupSampleRate;
		double LookupFrequency;
		double LookupAmplitude;
		double LookupPhaseOffset;
		unsigned int LookupSize;
		unsigned int LookupPosition;
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
	void ToneGeneratorFree(ToneGenerator *tg);
	void ToneGeneratorReset(ToneGenerator *tg);
	void ToneGeneratorSetWaveType(ToneGenerator *tg, unsigned int value);
	void ToneGeneratorSetSampleRate(ToneGenerator *tg, double value);
	void ToneGeneratorSetFrequency(ToneGenerator *tg, double value);
	void ToneGeneratorSetDigit(ToneGenerator *tg, unsigned int value);
	void ToneGeneratorSetAmplitude(ToneGenerator *tg, double value);
	void ToneGeneratorSetPhaseOffset(ToneGenerator *tg, double value);
	unsigned int ToneGeneratorGetWaveType(ToneGenerator *tg);
	double ToneGeneratorGetSampleRate(ToneGenerator *tg);
	double ToneGeneratorGetFrequency(ToneGenerator *tg);
	unsigned int ToneGeneratorGetDigit(ToneGenerator *tg);
	double ToneGeneratorGetAmplitude(ToneGenerator *tg);
	double ToneGeneratorGetPhaseOffset(ToneGenerator *tg);
	void ToneGeneratorResetAngle(ToneGenerator *tg);
	void ToneGeneratorResetLookupPosition(ToneGenerator *tg);
	const char *ToneGeneratorGetCurrentWaveName(ToneGenerator *tg);
	double ToneGeneratorGenerate(ToneGenerator *tg);
	float ToneGeneratorGenerateFloat(ToneGenerator *tg);
	signed long ToneGeneratorGenerateLong(ToneGenerator *tg);
	Sample24 ToneGeneratorGenerate24(ToneGenerator *tg);
	signed short ToneGeneratorGenerateShort(ToneGenerator *tg);
	unsigned char ToneGeneratorGenerateChar(ToneGenerator *tg);
	void ToneGeneratorCalculateLookup(ToneGenerator *tg);
	void ToneGeneratorClearLookup(ToneGenerator *tg);
	void ToneGeneratorSaveLookup(ToneGenerator *tg, const char *filename);
	signed short ToneGeneratorGenerateLookup(ToneGenerator *tg);
	void ToneGeneratorFillCharBuffer(ToneGenerator *tg, unsigned char *buffer, unsigned int length);
	void ToneGeneratorFillShortBuffer(ToneGenerator *tg, signed short *buffer, unsigned int length, unsigned int lookup);
	void ToneGeneratorFill24Buffer(ToneGenerator *tg, Sample24 *buffer, unsigned int length);
	void ToneGeneratorFillLongBuffer(ToneGenerator *tg, signed long *buffer, unsigned int length);
	void ToneGeneratorFillFloatBuffer(ToneGenerator *tg, float *buffer, unsigned int length);
	void ToneGeneratorFillDoubleBuffer(ToneGenerator *tg, double *buffer, unsigned int length);
	unsigned int ToneGeneratorMillis2Samples(ToneGenerator *tg, unsigned int Millis);
	double ToneGeneratorCalculateSweepStep(ToneGenerator *tg, double Start, double End, unsigned int Millis);

#ifdef __cplusplus
}
#endif

#endif //TONEGENERATOR_H
