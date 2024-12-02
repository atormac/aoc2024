#include <stdlib.h>
#include <stdio.h>


int cmp(const void *a, const void *b)
{
	int *x = (int*)a;
	int *y = (int*)b;
	return *x - *y;
}

int main(int argc, char **argv)
{
	if (argc != 2)
		return EXIT_FAILURE;

	FILE *file = fopen(argv[1], "r");
	if (!file)
		return EXIT_FAILURE;

	int *l1 = (int *)malloc(1000 * sizeof(int));
	int *l2 = (int *)malloc(1000 * sizeof(int));

	int n1, n2, size = 0;
	while (fscanf(file, "%d   %d", &n1, &n2) == 2) {
		l1[size] = n1;
		l2[size] = n2;
		size++;
	}
	qsort(l1, size, sizeof(int), cmp);
	qsort(l2, size, sizeof(int), cmp);

	int distance = 0;
	int similarity = 0;

	for (int i = 0; i < size; i++) {
	
		distance += abs(l2[i] - l1[i]);
	
		int count = 0;
		for (int j = 0; j < size; j++) {
			if (l1[i] == l2[j]) {
				count++;
			}
		}
		similarity += l1[i] * count;
	}
	printf("distance: %d\n", distance);
	printf("similarity: %d\n", similarity);
	
	fclose(file);
	return 0;
}
