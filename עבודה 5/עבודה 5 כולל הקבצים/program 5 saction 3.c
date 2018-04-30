#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
//************************************
//
// ����� ���� 3
//
//************************************
#define YEAR 10// ���� ������� �������� ������� �����
#define GODEL 3// ���� ������ �����
#define GODEL2 21// ���� ������� �� �� ���� ����� ����� �������� �� �� ��
#define DATA "data.txt"//����� ������ �� �� ����� ������ �������. �� ��� ���� ������ ����� ��� ���� �� ���
typedef struct
{
	char name[GODEL2];//�� �����
	char gender;//��� �����
	int age;//��� �����
	char interests[GODEL][GODEL2];//���� ������ 3 ����� ����� �� �����
}client;// ����� ������
void create_new_file(FILE *file)//������� ������� ���� ���� ���
{
	int age, i;
	char name[GODEL2], gender, interests[GODEL][GODEL2], add_client;
	if ((file = fopen(DATA, "w")) == NULL)// ����� ����� ������ ������ �� �� ������
	{
		puts("EROR!! cant write on this file!");
		return;
	}
	puts("If you want to insert client press 'a', to end the file press else key!");
	_flushall();
	scanf("%c", &add_client);
	while (add_client == 'a')//����� ������� ����� ����� 
	{
		puts("enter Name,\tGender (m,f),\tAge\tand 3 interests");
		scanf("%s %c %d", name, &gender, &age);
		fprintf(file,"%s\t %c\t %d", name, gender, age);//����� ����� �������� ������
		for (i = 0; i < GODEL; i++)
		{
			scanf("%s", interests[i]);
			fprintf(file, "\t%s", interests[i]);
		}
		fprintf(file, "\n");
		puts("If you want to insert client press 'a', to end the file press else key!");
		_flushall();
		scanf("%c", &add_client);
	}
	fclose(file);//����� �����
}
client* scan_from_file(FILE *file, int *size)//������� ������ ������ ����� ����� ���� ������
{
	int i = 0, j;
	client *arr = (client*)calloc(*size,sizeof(client));
	if (arr == NULL)
	{
		puts("EROR!!, dont have enough memory!");
		exit(1);
	}
	while (!feof(file))// ����� �� ��� �� ����� ���� �����
	{

		fscanf(file, "%s %c %d", arr[i].name, &arr[i].gender, &arr[i].age);//��� ������ ����� ������ �� ������
		for (j = 0; j < GODEL; j++)
		{
			fscanf(file, "%s\n", arr[i].interests[j]);
			fscanf(file, " ");
		}
		fscanf(file, "\n");
		*size = *size + 1;//����� ������ �1 ��� ����� �� ����� ����� ������ �������
		arr = (client*)realloc(arr, *size*sizeof(client));//����� ������ ���� �����
		if (arr == NULL)
		{
			puts("EROR!! dont have memory!!");
			exit(1);
		}
		i++;
	}
	*size = *size - 1;
	arr = (client*)realloc(arr, *size*sizeof(client));//����� ���� ����� ����� ������ ������
	fclose(file);
	return arr;//����� ������ �� �����

}
void print_file(client *arr, int *size)//������� ������� �� ������ ������ ������ �����
{
	int i, j;
	puts("\n\t****************************************************************************");
	puts("\t*  Name:\tGender:\t   Age:\t  intersts:\t                           *");
	for (i = 0; i < *size; i++)
	{
		printf("\t*%7s\t %5c\t %5d\t", arr[i].name, arr[i].gender, arr[i].age);
		for (j = 0; j < GODEL; j++)
		{
			if (j == 2)
			{
				printf("%10s *", arr[i].interests[j]);
			}
			else printf("%10s\t", arr[i].interests[j]);
			
		}
		puts("");
	}
	puts("\t****************************************************************************");
}
client open_new_client()//������� ������ ������ ��� ����� ����� ������
{
	int i;
	client new_client;//����� ����� ���� ����� �����
	puts("enter your first Name,\tGender (press 'm' for male,'f' for female),Your age and Enter 3 interests");
	scanf("%s %c %d", new_client.name, &new_client.gender, &new_client.age);//����� ������ �� ����� ����
	for (i = 0; i < GODEL; i++)
		scanf("%s", new_client.interests[i]);
	return new_client;//����� ������� �� ����� ����
}
int interst(client *arr, char new_client[][21], int k)//������� ������ �� �� ����� ���� ������� ������� �� ������� �����. 
{
	int i, j;
	for (i = 0; i < GODEL; i++)
		for (j = 0; j < GODEL; j++)
			if (strcmp(arr[k].interests[j], new_client[i]) == 0)//����� �������� ������ ������� ���� ����� ����� ��������
				return 1;
	return 0;
}
void check_for_adjustment(client *arr, int *size)//������� ������ ����� ����� �� �� ����� �� ����� ���� �� ����� �����
{
	int i = 0, s = 0;
	client new_client = open_new_client();
	for (i = 0; i < *size; i++)//����� ����� ������ �� �� �����
	{
		if ((abs(new_client.age - arr[i].age) <= YEAR) && (new_client.gender != arr[i].gender))//����� ����� ������ ������ �� ��� ���� ������ ������ �� ���� �� 10 ����
		{
			if (interst(arr, new_client.interests, i) == 1)//����� �� �� ����� ����� ��� �����,�� �� ������ ������ ������ ����� ������ �� ����� �� ����� ������ ����� ����
			{
				puts("*****************************************************************");
				printf("your pairing is: %s\n%c,  %d,  %s,  %s,  %s\n", arr[i].name, arr[i].gender, arr[i].age, arr[i].interests[0], arr[i].interests[1], arr[i].interests[2]);
				puts("*****************************************************************");
				s = 1;
			}

		}
	}
	if (s == 0)//�� �� ����� ����� ����� ����� �����
	puts("Sorri, we cant find you any pairing!");
	_getch();
}
char clean_screen()//������� ����� �� ���� ������ �� ������ ��� ���
{
	char saction;
	_flushall();
	system("cls");//����� ���� ������ ����
	puts("***************************************************************");
	puts("\tTo open the file press 'f'");
	puts("\tFor check for adjustment press'c'");
	puts("\tif you want to print the file press 'p'");
	puts("\tFor exit press 'q'");
	puts("***************************************************************");
	scanf("%c", &saction);
	return saction;
}
void main()//������ ������ ��� ���� ������ �����
{
	int size = 1, status = 0;
	char saction;
	client *arr=NULL;
	FILE *file=NULL;
	do{
		saction = clean_screen();
		switch (saction)
		{

			//*** ���� ����� ���� ��� ����� �� ������ �� case 'a'****

		/*case 'a':
			status = 1;
			create_new_file(file);
			file = fopen(file_name, "r");
			arr = scan_from_file(file, &size);
			_getch();
			break;*/


		case 'f':
			status = 1;
			file = fopen(DATA, "r");//����� ����� ����� ������
			if (file == NULL)
			{
				puts("EROR!! The file canot be found!!");
				exit(1);
			}
			arr = scan_from_file(file, &size);//����� �������� ������ ������
			puts("\nyour file opend Correctly,you can use with the file");
			_getch();//����� ����
			break;
		case 'p'://����� ������� ������
			if (status == 0)
			{
				puts("EROR!! you need to open file before!");
				_getch();
				break;
			}
			print_file(arr, &size);
			_getch();
			break;
		case 'c'://����� ��� ����� ������ ����� ��� ����� ���� �����
			check_for_adjustment(arr, &size);
			break;
		}
	} while (saction != 'q');
	free(arr);//����� �����
}
