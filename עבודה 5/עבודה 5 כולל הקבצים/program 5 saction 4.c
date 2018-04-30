#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
//************************************
//
// ����� ���� 4
//
//************************************
#define GODEL1 21//����� �� ����� ��������� �� ��� ����� �� �����
#define GODEL2 81//����� �� ����� �������� �� ��� �� ����� �� �����
#define DATA "data2.txt"//����� �� �� ����� ������ ��,�� ������ ������ ����� ��� ��� �� ��� ������ �������
typedef struct//����� �����
{
	char model[21];//��� �����
	char manufacturer[81];//�� �����
	int memory;//���� ������
	int year;//��� ����� �� �����
}computers;
void new_file_of_computer(FILE *file)// ������� ������� ���� ���
{
	char status, model[21], manufacturer[81];
	int memory, year;
	puts("If you want to add computer details press 'a', for exit press 'q'");
	_flushall();
	scanf("%c", &status);
	while (status == 'a')
	{
		puts("Enter the model of your coputer,his manufacturer,the size of his memory and his Year of Production");
		scanf("%s %s %d %d", &model, &manufacturer, &memory, &year);//����� ������� ������� ������� �����
		fprintf(file,"%s %s %d %d", model, manufacturer, memory, year);
		fprintf(file, "\n");
		puts("If you want to add computer details press 'a', for exit press 'q'");
		_flushall();
		scanf("%c", &status);
	}
	
	fclose(file);//����� �����
	
}
computers* scan_from_file(computers *arr, FILE *file,int *size)//������� ������ ������ ����� ����� ���� ������
{
	int  i = 0;
	while (!feof(file))// ����� �� ��� �� ����� ���� �����
	{
		*size = *size+1;//����� ����� �� ������ ��� ����� �� ��� �� ����� ���� �����
		arr = (computers*)realloc(arr, *size*sizeof(computers));//����� ������ �� ����� 
		if (arr == NULL)
		{
			puts("EROR!! dont have enough memory!!");
			exit(1);
		}
		fscanf(file, "%s %s %d %d\n", &arr[i].model, &arr[i].manufacturer, &arr[i].memory, &arr[i].year);//��� ������ ����� ������ �� ������
		i++;
	}
	*size = *size - 1;
	arr = (computers*)realloc(arr, *size*sizeof(computers));//����� ���� ����� ����� ������ ������
	fclose(file);//����� �����
	return arr;//����� ������ �� �����
}
void big_memory(computers *arr, int *size)//������� ������ ����� �� ����� �� ������ ����� �����
{
	int i, big = arr[1].memory;
	for (i = 1; i < *size; i++)//����� ������ �� �� ����� ������ �� ������� ����� �����
		if (arr[i].memory > big)
			big = arr[i].memory;			
	
	puts("The details of the computer\s with the big memory are:");
	puts("*******************************");
	for ( i = 0; i < *size; i++)//����� ������ �� ����� �� ������ ����� �����
		if (arr[i].memory == big)
		{
			printf("%s\t %s\t %dGB\t %d\n\n", arr[i].model, arr[i].manufacturer, arr[i].memory, arr[i].year);
		}
	puts("*******************************");
}
void after_2014(computers *arr, int *size)//������� ������ ���� ������ ����� ���� ��� 2014
{
	int i,status=0;
	for (i = 0; i < *size; i++)//����� ������ �� ����� ������� �� ������ �� ������� ������ ���� 2014
		if (arr[i].year>2014)
		{
			status = 1;
			puts("The details of the computer\s that produced after 2014 are:\n");
			printf("%s\t %s\t %dGB\t %d\n", arr[i].model, arr[i].manufacturer, arr[i].memory, arr[i].year);
		}
	if (status == 0)//�� ��� ������ ���� ����� ����� �����
		puts("No computer manufactured after 2014");
}
void print_the_file(computers *arr, int *size)//������� ������� �� ������ ������ ������ �����
{
	int i;
	puts("\n\t**************************************************************");
	puts("\t*  Model:    Manufacturer:      Memory:\t  Year of production:*");
	for (int i = 0; i < *size; i++)
	{
		printf("\t*%9s\t%10s\t%5dGB\t%21d*\t\n", arr[i].model, arr[i].manufacturer, arr[i].memory, arr[i].year);
	}
	puts("\t**************************************************************");
}
char clean_screen()//������� ����� �� ���� ������ �� ������ ��� ���
{
	char saction;
	_flushall();
	system("cls");//����� ���� ������ ����
	puts("***************************************************************");
	puts("\tFor use a exist file press 'f'");
	puts("For search the computer with the big memory press 'c'");
	puts("for search all the computer that produced after 2014 press 'd'");
	puts("if you want to print the file press 'p'");
	puts("\tFor exit press 'q'");
	puts("***************************************************************");
	scanf("%c", &saction);
	return saction;
}
void main()//������ ������ ��� ���� ������ �����
{
	int size=1,status=0;
	char saction;
	computers *arr = (computers*)calloc(1 , sizeof(computers));//����� ������ ������� �����
	if (arr == NULL)
	{
		puts("EROR!! dont have enough memory!!");
		exit(1);
	}
	FILE *file=NULL;
	do{
		saction = clean_screen();
		switch(saction)
		{
			//*** ���� ����� ���� ��� ����� �� ������ �� case 'a'****

		/*case 'a':
			status = 1;
			file = fopen(DATA, "w");
			new_file_of_computer(file);
			file = fopen(DATA, "r");
			if ((file = fopen(DATA, "r")) == NULL)
			{
				printf("ERROR: the file canot be opened!\n");
				_getch();
				break;
			}
			arr = scan_from_file(arr, file, &size);			
			_getch();
			break;*/


		case 'f':
			status = 1;
			if ((file = fopen(DATA, "r")) == NULL)//����� ����� ����� ������
			{
				printf("ERROR: the file canot be opened!\n"); 
				_getch();
				break; 
			}
			arr = scan_from_file(arr, file, &size);//����� �������� ������ ������ �����
			puts("\n***your file opend Correctly,you can use with the file***");
			_getch();
			break;
		case 'c':
			if (status == 0)//����� ��� ����� ������� ��� ���� ����
			{
				puts("EROR!! you need to open file before!");
				_getch();
				break;
			}
			big_memory(arr, &size);//����� �������� ������ �� ����� �� ������ ����� ����� �����
			_getch();
			break;
		case 'd':
			if (status == 0)//����� ��� ����� ������� ��� ���� ����
			{
				puts("EROR!! you need to open file before!");
				_getch();
				break;
			}
			after_2014(arr, &size);//����� �������� ������ ���� ������ ����� ���� ��� 2014
			_getch();
			break;
		case 'p':
			if (status == 0)//����� ��� ����� ������� ��� ���� ����
			{
				puts("EROR!! you need to open file before!");
				_getch();
				break;
			}
			print_the_file(arr, &size);//����� �������� �� ������
			_getch();
			break;
		}
	} while (saction != 'q');
	free(arr);//����� ����� 
}