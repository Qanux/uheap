#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

char *arr[4];
void *record;
int chance = 1;

void banner() {
	printf("         __\n");
	printf("  __  __/ /_  ___  ____ _____\n");
	printf(" / / / / __ \\/ _ \\/ __ `/ __ \\\n");
	printf("/ /_/ / / / /  __/ /_/ / /_/ /\n");
	printf("\\__,_/_/ /_/\\___/\\__,_/ .___/\n");
	printf("                     /_/\n");
}

void menu() {
	printf("1. add\n");
	printf("2. delete\n");
	printf("3. ???\n");
}

void readline(char *buf, int size)
{
	int i;
	for(i = 0; i < size; i++) {
		read(1, &buf[i], 1);
		if(buf[i] == '\x0a'){
			buf[i] = '\x00';
			break;
		}
	}
}

void add() {
	int size;
	printf("size: ");
	scanf("%d", &size);
	if (size < 0 || size > 0x50)
		return;

	int idx;
	for (idx = 0; idx < 4; idx++)
		if (arr[idx] == 0)
			break;
	if (idx == 4)
		return;

	arr[idx] = malloc(size);
	printf("content: ");
	readline(arr[idx], size);
}

void delete() {
	int idx;
	printf("index: ");
	scanf("%d", &idx);

	if (idx >= 0 && idx < 4) {
		if (arr[idx]) {
			free(arr[idx]);
			if (chance)
				record = arr[idx];
			arr[idx] = 0;
		}
	}
}

void backdoor() {
	char *argv[] = {"sh", 0};
	exec("sh", argv);
}

void gift() {
	if (chance) {
		if (record)
			free(record);
		record = 0;
		chance = 0;
	}
}

int main() {
	banner();

	int choice;
	while (1) {
		menu();
		scanf("%d", &choice);
		switch (choice) {
			case 1:
				add();
				break;
			case 2:
				delete();
				break;
			case 3:
				gift();
				break;
		}
	}
}

