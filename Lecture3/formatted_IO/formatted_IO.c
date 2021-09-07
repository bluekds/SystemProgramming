#include <stdio.h>
#include <stdlib.h>

typedef struct {
	int ID;
	char name[8];
	float score;
} Student;

int fileOpen(FILE** _fp, char* _fileName, char* _mode) {
	*_fp = fopen(_fileName, _mode);
	if (!*_fp) {
		printf("Fail to open - %s\n", _fileName);
		return -1;
	}
	return 0;
}

int main(void) {
	Student info = { 0 };
	char* fileName = "StudentList.txt";
	FILE* fp = NULL;

	if (fileOpen(&fp, fileName, "a") < 0)
		exit(1);	

	while(1) {	// Get and store the student info
		printf("Enter ID Name Score (Exit: -1): ");
		scanf("%d", &info.ID);
		if (info.ID < 0)
			break;
		scanf("%s %f", (char*)&info.name, &info.score); getchar();
		fprintf(fp, "%d %s %.1f\n", info.ID, info.name, info.score);
	}

	fclose(fp);

	if (fileOpen(&fp, fileName, "r") < 0)
		exit(1);

	int numStudent = 0;
	float sum = 0;
	while (!feof(fp)) {
		fscanf(fp, "%d %s %f\n", &info.ID, (char*)&info.name, &info.score);
		sum += info.score;
		numStudent++;
	}

	printf("%d students, Average = %.2f\n", numStudent, sum / numStudent);

	fclose(fp);
}
