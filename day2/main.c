#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>


int **alloc_matrix(int width, int height)
{
	int **arr = (int **)calloc(1, (height * sizeof(int *)));

	for (int i = 0; i < height; i++) {
		arr[i] = calloc(1, (width * sizeof(int)));
	}
	return arr;

}

bool is_safe(int **arr, int x, int y, int skip)
{
	int decreasing = 0;
	int increasing = 0;
	int maxdiff = 1;

	for (int j = 0; j < x - 1; j++)
	{
		if (j == skip)
			continue;
		int next = j + 1;
		if (skip >= 0 && j + 1 == skip)
		{
			if (j + 2 >= x)
				break;
			next = j + 2;
		}
		int diff = abs(arr[y][j] - arr[y][next]);
		if (diff > maxdiff)
			maxdiff = diff;
		if (arr[y][j] > arr[y][next])
			decreasing++;
		if (arr[y][j] < arr[y][next])
			increasing++;
	}
	if (skip >= 0)
		x--;
	if (decreasing == x - 1 && maxdiff <= 3)
		return true;
	if (increasing == x - 1 && maxdiff <= 3)
		return true;

	return false;
}

int main(int argc, char **argv)
{
	if (argc != 2)
		return EXIT_FAILURE;
	FILE *file = fopen(argv[1], "r");
	if (!file)
		return EXIT_FAILURE;

	int safe = 0;
	int unsafe = 0;
	int single = 0;

	int **arr = alloc_matrix(1000, 1000);
	int width = 0;
	int height = 0;
	char line[1024];

	while (fgets(line, sizeof(line), file)) {
		char *token = strtok(line, " ");	
		width = 0;
		while (token) {
			int num = atoi(token);
			arr[height][width] = num;
			width++;
			token = strtok(NULL, " ");
		}
		if (is_safe(arr, width, height, -1))
		{
			safe++;
			height++;
			continue;
		}
		unsafe++;
		for (int skip = 0; skip < width; skip++)
		{
			if (is_safe(arr, width, height, skip)) {
				single++;
				break;
			}

		}
		height++;
	}

	printf("safe records: %d\n", safe);
	printf("unsafe records: %d\n", unsafe);
	printf("removed safe records: %d\n", single);
	printf("safe + removed safe: %d\n", safe + single);
	
	fclose(file);
	return 0;
}
