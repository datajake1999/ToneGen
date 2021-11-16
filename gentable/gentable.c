#include <stdio.h>
#include <math.h>
#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif
const double twopi = 2 * M_PI;

enum {tabsize = 1024};
static double table[tabsize];

static void FillTable()
{
	unsigned int i;
	for (i = 0; i < tabsize; i++)
	{
		table[i] = sin(twopi * i / tabsize);
	}
}

int main()
{
	FILE *tabfile;
	unsigned int i;
	FillTable();
	tabfile = fopen("sinetab.h", "w");
	fprintf(tabfile, "//Sine wave lookup table\n\n");
	fprintf(tabfile, "#ifndef SINETAB_H\n");
	fprintf(tabfile, "#define SINETAB_H\n\n");
	fprintf(tabfile, "#define TableSize %d.0\n", tabsize);
	fprintf(tabfile, "#define HalfTableSize %d.0\n\n", tabsize/2);
	fprintf(tabfile, "static const double SineTable[%d] = \n", tabsize);
	fprintf(tabfile, "{\n");
	for (i = 0; i < tabsize; i++)
	{
		if (i == tabsize-1)
		{
			fprintf(tabfile, "\t%f\n", table[i]);
			break;
		}
		fprintf(tabfile, "\t%f,\n", table[i]);
	}
	fprintf(tabfile, "};\n\n");
	fprintf(tabfile, "#endif //SINETAB_H");
	fclose(tabfile);
	return 0;
}
