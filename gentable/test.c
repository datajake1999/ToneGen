#include <stdio.h>
#include "sinetab.h"

int main()
{
	FILE *tabfile;
	tabfile = fopen("sinetab", "wb");
	fwrite(SineTable, 1, sizeof(SineTable), tabfile);
	fclose(tabfile);
	return 0;
}
