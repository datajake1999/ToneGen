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
	WaveTypes
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
	}ToneGenerator;

	void ToneGeneratorInit(ToneGenerator *tg);
	void ToneGeneratorFree(ToneGenerator *tg);
	void ToneGeneratorReset(ToneGenerator *tg);
	void ToneGeneratorSetWaveType(ToneGenerator *tg, unsigned int value);
	void ToneGeneratorSetSampleRate(ToneGenerator *tg, double value);
	void ToneGeneratorSetFrequency(ToneGenerator *tg, double value);
	void ToneGeneratorSetAmplitude(ToneGenerator *tg, double value);
	void ToneGeneratorSetPhaseOffset(ToneGenerator *tg, double value);
	unsigned int ToneGeneratorGetWaveType(ToneGenerator *tg);
	double ToneGeneratorGetSampleRate(ToneGenerator *tg);
	double ToneGeneratorGetFrequency(ToneGenerator *tg);
	double ToneGeneratorGetAmplitude(ToneGenerator *tg);
	double ToneGeneratorGetPhaseOffset(ToneGenerator *tg);
	void ToneGeneratorResetAngle(ToneGenerator *tg);
	const char *ToneGeneratorGetCurrentWaveName(ToneGenerator *tg);
	double ToneGeneratorGenerate(ToneGenerator *tg);
	signed short ToneGeneratorGenerateShort(ToneGenerator *tg);
	void ToneGeneratorCalculateLookup(ToneGenerator *tg);
	void ToneGeneratorClearLookup(ToneGenerator *tg);
	signed short ToneGeneratorGenerateLookup(ToneGenerator *tg);
	unsigned int ToneGeneratorMillis2Samples(ToneGenerator *tg, unsigned int Millis);
	void ToneGeneratorFillBuffer(ToneGenerator *tg, signed short *buffer, unsigned int length, unsigned int lookup);
	void ToneGeneratorFillFloatBuffer(ToneGenerator *tg, float *buffer, unsigned int length);

#ifdef __cplusplus
}
#endif

#endif
