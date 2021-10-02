#include <stdio.h>
#include <stdbool.h>

#define SIZE 4

int main(void)
{
	int prices[SIZE] = { 100, 200, 300, 400 };

	bool isTrue = true;
	bool isFalse = false;

	printf("True: %d, False: %d\n", isTrue, isFalse);

	printf(" 'While' Loop:\n");

	int i = 0;

	while(i < SIZE)
	{
		printf("%d\n", prices[i]);
		i++;
	}

	printf(" 'For' Loop:\n");

	for (int i = 0; i < SIZE; i++)
	{
		printf("%d\n", prices[i]);
	}

	printf("Second 'For' Loop:\n");

	for (int i = 0; i < SIZE; i++)
	{
		printf("%d\n", prices[i]);
	}

	// Если использовать одну инструкцию в теле while, for, if, else
	// то фигурные скобки можно не писать
	printf("For Loop Short Form:\n");

	for (int i = 0; i < SIZE; i++) printf("%d\n", prices[i]);

	printf("Do-While Loop:\n");

	// Разница с while в том, что здесь тело цикла
	// выполняется как минимум один раз: сначала выполняется,
	// затем идет проверка условия
	int j = 0;
	
	do {
		printf("%d\n", prices[j]);
		j++;	
	} while(j < SIZE); // обратить внимание на точку с запятой!

	return 0;
}
