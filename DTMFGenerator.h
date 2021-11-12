#ifndef DTMFGENERATOR_H
#define DTMFGENERATOR_H

#include "ToneGenerator.h"

enum
{
	DTMF0 = 10,
	DTMF1,
	DTMF2,
	DTMF3,
	DTMF4,
	DTMF5,
	DTMF6,
	DTMF7,
	DTMF8,
	DTMF9,
	DTMFSTAR,
	DTMFHASH,
	DTMFA,
	DTMFB,
	DTMFC,
	DTMFD,
	DTMFTones
};

#ifdef __cplusplus
extern "C" {
#endif

	typedef struct
	{
		double SampleRate;
		unsigned int Digit;
		double Amplitude;
		ToneGenerator Gen1;
		ToneGenerator Gen2;
	}DTMFGenerator;

	void DTMFGeneratorInit(DTMFGenerator *dg);
	void DTMFGeneratorFree(DTMFGenerator *dg);
	void DTMFGeneratorReset(DTMFGenerator *dg);
	void DTMFGeneratorSetSampleRate(DTMFGenerator *dg, double value);
	void DTMFGeneratorSetDigit(DTMFGenerator *dg, unsigned int value);
	void DTMFGeneratorSetAmplitude(DTMFGenerator *dg, double value);
	double DTMFGeneratorGetSampleRate(DTMFGenerator *dg);
	unsigned int DTMFGeneratorGetDigit(DTMFGenerator *dg);
	double DTMFGeneratorGetAmplitude(DTMFGenerator *dg);
	double DTMFGeneratorGenerate(DTMFGenerator *dg);
	float DTMFGeneratorGenerateFloat(DTMFGenerator *dg);
	signed long DTMFGeneratorGenerateLong(DTMFGenerator *dg);
	Sample24 DTMFGeneratorGenerate24(DTMFGenerator *dg);
	signed short DTMFGeneratorGenerateShort(DTMFGenerator *dg);
	unsigned char DTMFGeneratorGenerateChar(DTMFGenerator *dg);
	void DTMFGeneratorFillCharBuffer(DTMFGenerator *dg, unsigned char *buffer, unsigned int length);
	void DTMFGeneratorFillShortBuffer(DTMFGenerator *dg, signed short *buffer, unsigned int length);
	void DTMFGeneratorFill24Buffer(DTMFGenerator *dg, Sample24 *buffer, unsigned int length);
	void DTMFGeneratorFillLongBuffer(DTMFGenerator *dg, signed long *buffer, unsigned int length);
	void DTMFGeneratorFillFloatBuffer(DTMFGenerator *dg, float *buffer, unsigned int length);
	void DTMFGeneratorFillDoubleBuffer(DTMFGenerator *dg, double *buffer, unsigned int length);
	unsigned int DTMFGeneratorMillis2Samples(DTMFGenerator *dg, unsigned int Millis);

#ifdef __cplusplus
}
#endif

#endif //DTMFGENERATOR_H
