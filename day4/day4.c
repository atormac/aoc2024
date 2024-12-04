#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

int **alloc_matrix(int width, int height)
{
	int **arr = (int **)calloc(1, (height * sizeof(int *)));

	for (int i = 0; i < height; i++) {
		arr[i] = calloc(1, (width * sizeof(int)));
	}
	return arr;

}

int grids = 0;
int words = 0;

int x_pos[] = { 1, 0, -1, 0, 1, -1, -1, 1 };
int y_pos[] = { 0, 1, 0, -1, 1, -1, 1, -1 };

void test_word(int **arr, int width, int height, int x, int y, const char *chars, int dir)
{
	if (x < 0 || x >= width || y < 0 || y >= height || arr[y][x] != chars[0])
		return;
	chars++;
	if (*chars == '\0')
	{
		words++;
		return;
	}
	test_word(arr, width, height, x + x_pos[dir], y + y_pos[dir], chars, dir);
}

void test_grid(int **arr, int width, int height, int x, int y, int dir)
{
	if (arr[y][x] != 'A' || x < 1 || x >= width - 1|| y < 1 || y >= height - 1 )
		return;

	char corners[5] = { 0 };
	char c1 = arr[y + 1][x - 1];
	char c2 = arr[y + 1][x + 1];
	char c3 = arr[y - 1][x - 1];
	char c4 = arr[y - 1][x + 1];
	corners[0] = c1;
	corners[1] = c2;
	corners[2] = c3;
	corners[3] = c4;

	char *valid[] = { "MMSS", "SSMM", "MSMS", "SMSM" };
	for (int i = 0; i < 4; i++)
	{
		if (strcmp(valid[i], corners) == 0)
			break;
		if (i == 3)
			return;
	}
	printf("y: %d, %s\n", y, corners);
	printf("%c %c\n", c1, c2);
	printf(" %c \n", arr[y][x]);
	printf("%c %c\n", c3, c4);
	grids++;
}

int solve(int **arr, int width, int height)
{
	const char *chars = "XMAS";

	for (int y = 0; y < height; y++) {
		for (int x = 0; x < width; x++) {
			for (int d = 0; d <= 7; d++)
				test_word(arr, width, height, x, y, chars, d);
			test_grid(arr, width, height, x, y, 0);
		}	
	}
	printf("words: %d\n", words);
	printf("grids: %d\n", grids);
	return 0;
}

int main(int argc, char **argv)
{
	if (argc != 2)
		return EXIT_FAILURE;
	FILE *file = fopen(argv[1], "r");
	if (!file)
		return EXIT_FAILURE;

	int **arr = alloc_matrix(10000, 10000);

	char line[1024];
	int width = 0;
	int height = 0;
	while (fgets(line, sizeof(line), file)) {
		char *l = line;
		width = 0;
		while (*l && *l != '\n') {
			arr[height][width] = *l;
			width++;
			l++;
		}
		height++;
	}

	solve(arr, width, height);

	return 0;
}
