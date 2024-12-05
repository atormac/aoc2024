#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

typedef struct t_rule
{
	int first;
	int second;
} t_rule;

typedef struct t_update
{
	int numbers[1024];
	int count;
} t_update;

int result = 0;
int sorted_result = 0;

int rule_count = 0;
t_rule* rules;

int cmp(const void *a, const void *b) {
    int n1 = *(int*)a;
    int n2 = *(int*)b;
    for (int i = 0; i < rule_count; i++)
    {
        if (rules[i].first == n2 && rules[i].second == n1)
            return 1;
        if (rules[i].first == n1 && rules[i].second == n2)
            return -1;
    }
    return n2 - n1;
}

bool is_order(t_update *line, t_rule *rule)
{
	int pos1 = -1;
	int pos2 = -1;
	for (int i = 0; i < line->count; i++)
	{
		if (line->numbers[i] == rule->first)
			pos1 = i;
		else if (line->numbers[i] == rule->second)
			pos2 = i;
		if (pos1 >= 0 && pos2 >= 0 && pos1 > pos2)
				return false;
	}

	return true;
}


void test_rule(t_update *line, t_rule *rules, int rule_count)
{
	bool is_ordered = true;

	for (int j = 0; j < rule_count; j++)
	{
		if (!is_order(line, &rules[j]))
		{
			is_ordered = false;
			break;
		}
	}
	if (is_ordered) {
		result += line->numbers[line->count / 2];
	}
	else {
		qsort(line->numbers, line->count, sizeof(int), cmp);
		sorted_result += line->numbers[line->count / 2];
	}
}

int main(int argc, char **argv)
{
	if (argc != 2)
		return EXIT_FAILURE;
	FILE *file = fopen(argv[1], "r");
	if (!file)
		return EXIT_FAILURE;

	rules = calloc(1, sizeof(t_rule) * 10000);
	t_update* updates = calloc(1, sizeof(t_update) * 10000);

	while (fscanf(file, "%d|%d", &rules[rule_count].first, &rules[rule_count].second) == 2) {
		printf("%d %d\n", rules[rule_count].first, rules[rule_count].second);
		rule_count++;
	}
	char line[1024];
	int update_count = 0;
	int i = 0;

	while (fscanf(file, "%s", line) == 1) {
		if (strcmp(line, "x") == 0)
			continue;
		int j = 0;
		char *token = strtok(line, ",");	
		while (token) {
			int num = atoi(token);
			updates[i].numbers[j] = num;
			token = strtok(NULL, ",");
			j++;
		}
		updates[i].count = j;
		i++;
	}
	fclose(file);
	update_count = i;
	printf("\n");

	printf("rule_count: %d\n", rule_count);
	printf("update_count: %d\n", update_count);
	for (int i = 0; i < update_count; i++)
	{
		test_rule(&updates[i], rules, rule_count);
	}
	printf("\nresult %d\n", result);
	printf("\nsorted_result %d\n", sorted_result);
	return 0;
}
