#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<string.h>
#define SIZE 5
//************************************
		// ����� ���� 1

//************************************

void ScanRec(int *arr, int size)//������� ��������� ������ ������ ���� ����
{
	static int i = 0;

	if (size == 0)//����� ����� �� ����� ���� �����
	{
		i = 0;
		return;
	}

	printf("\nenter the %d number\n", i + 1);
	scanf("%d", &arr[i++]);
	return ScanRec(arr, size - 1);

}
void ThreeDigits(int *arr, int size)//������� ������ ��� ������ ��� ������� ������ �����
{
	static int s = 0; static int i = 0;
	if (size == 0)//����� ����� �� ����� ���� �����
	{
		printf("there are %d numbers with 3 digits in arr\n", s);
		i = 0;
		s = 0;
		return;
	}
	if ((arr[i] / 100 > 0) && (arr[i] / 100 < 10))//����� �� ������� ����� ��� �������
		s++;

	i++;
	return ThreeDigits(arr, size - 1);

}
int first(int num)// ������� ������ �� ���� ��� ������
{
	static int i = 2;
	if (i == num)//����� ����� �� ����� �� �� ������� �� ����� ��� ����� ������
	{
		i = 2;
		return 1;
	}
	if (num % i == 0)//����� ����� �� ����� ����� ���� ���
	{
		return 0;
	}
	i++;
	return first(num);

}
int first_numbers_at_array(int *arr, int size)//������� ������ ��� ������ ����� �� ������ �������� 
{
	int static i = 0, count = 0; int amount_of_firsts;
	if (i == size)
	{
		amount_of_firsts = count;
		count = 0;
		i = 0;
		return amount_of_firsts;
	}
		
	count = count + first(*(arr + i));//����� �������� ������ �� ���� ��� ������, �� �� ���� �����
	i++;
	return first_numbers_at_array(arr, size);
}
int main()//������ ����� ���� ���� ���� ���� ����� ������ ����� ������ ����� �������� �����
{
	int *arr, i, size, s = 0, num, check = 0;
	char saction;
	puts("enter the size of arr");
	scanf("%d", &size);
	arr = (int*)malloc(size*sizeof(int));//����� ������ �� �����
	do
	{
		_flushall();
		system("cls");//����� ���� ������ ����
		printf("which saction do you want? \n");
		printf("\t*********************************\n");
		printf("\t  press a to insert numbers to arr --\n");
		printf("\t  press b to check how many numbers in arr with 3 digits--\n");
		printf("\t  press c to insert number and check if it is first number --\n");
		printf("\t  press d to check how many numbers in arr are first numbers--\n");
		printf("\t*********************************\n");
		printf("if you want to exit from the program press y\n");
		scanf("%c", &saction);//����� ������

		switch (saction)
		{
		case 'a'://�� ������ ��� ������ �� ������� �������
			printf("\nadd %d integers to fill arr\n", size);
			ScanRec(arr, size);
			printf("\narray : \n{");
			for (i = 0; i < size; i++)//����� �� ����� ����� ������
				printf("%d,  ", arr[i]);
			printf("}\n");
			check = 1;//��� ����� ������� �������� �� �����
			_getch();
			break;
		case 'b':
			if (check == 0)//�� ��� �� ������ �� ����� ����� ����� ����� ������
			{
				puts("***EROR!!***\nyou need to insert numbers to arr before you can use at this saction!");
				_getch();
				break;
			}
			ThreeDigits(arr, size);
			_getch();
			break;
		case 'c':
			puts("enter a number please");
			scanf("%d", &num);//������ ���� ���� ��������� ����� �� ��� ������ �� ��
			i=first(num);
			if (i==1)
				printf("the number %d is first\n", num);
			else 
				printf("the number %d is not first\n", num);
			_getch();
			break;
		case 'd':
			if (check == 0)//�� ��� �� ������ �� ����� ����� ����� ����� ������
			{
				puts("***EROR!!***\nyou need to insert numbers to arr before you can use at this saction!");
				_getch();
				break;
			}
			printf("the amount of first numbers in arr is %d\n", first_numbers_at_array(arr,size));
			_getch();
			break;
		}
	} while (saction != 'y');
	free(arr);// ����� �����
}



