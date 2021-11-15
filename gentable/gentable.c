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
	FillTable();
	tabfile = fopen("sinetab", "wb");
	fwrite(table, 1, sizeof(table), tabfile);
	fclose(tabfile);
	return 0;
}
