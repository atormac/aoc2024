#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>

int main(int argc, char **argv)
{
	if (argc != 2)
		return EXIT_FAILURE;
	FILE *file = fopen(argv[1], "r");
	if (!file)
		return EXIT_FAILURE;

	char *buf = calloc(1, 100000);

	int i = 0;
	char ch;
	while ((ch = fgetc(file)) != EOF) {
		buf[i++] = ch;
	}

	long long result = 0;
	bool enabled = true;

	while (*buf)
	{
		if (strncmp(buf, "do()", 4) == 0) {
			enabled = true;
			buf += 4;
			continue;
		}
		if (strncmp(buf, "don't()", 7) == 0) {
			enabled = false;
			buf += 7;
			continue;
		}
		if (strncmp(buf, "mul(", 4) != 0) {
			buf++;
			continue;
		}
		buf += 4;

		int nlen = 0;
		int n1 = atoi(buf);
		while (isdigit(*buf)) {
			nlen++;
			buf++;
		}
		if (*buf != ',' || !(nlen >= 1 && nlen <= 3))
			continue;
		buf++;

		nlen = 0;
		int n2 = atoi(buf);
		while (isdigit(*buf)) {
			nlen++;
			buf++;
		}
		if (*buf != ')' || !(nlen >= 1 && nlen <= 3))
			continue;

		if (enabled)
			result += n1 * n2;
		buf++;
	}

	printf("result: %lld\n", result);
	
	fclose(file);
	return 0;
}
