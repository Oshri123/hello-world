#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<string.h>
#define SIZE 81
//************************************
//
// ����� ���� 2
//
//************************************
int length_of_str(char *str1, char *str2)//������� ������ ��� ������� ������ �� �� ����
{
	if ((*str1 == '\0') && (*str2 == '\0'))
		return 0;
	if (*str1 == '\0')
		return 2;
	if (*str2 == '\0')
		return 1;
	
	return length_of_str((str1+1), (str2+1));
}
int if_even_plcaes_with_sifra(char str[SIZE])//������� ������ ������ ������ �� ��� ������� ������� ��� �� �����
{
	static int i = 0; static int sifra = 0; static int even_places = 0;
	if (str[i] == '\0')//���� ����� �� ����� ���� �������
	{
		if ((even_places == sifra) && (even_places != 0))//����� �� �� ������� ������� �� �����
		{
			i = 0; even_places = 0; sifra = 0;
			return 1;
		}
		else {
			i = 0; even_places = 0; sifra = 0;
			return 0;
		}
	}
	if (i % 2 == 0)//����� �� ����� ������ ������� �������
	{
		even_places++;
		if ((str[i] > 47) && (str[i] < 58))//����� �� ����� ��� �����
			sifra++;
	}

	i++;
	return if_even_plcaes_with_sifra(str);


}
int smallLater(char str[SIZE])//������� ������ ������ ������ �� ��� ������ ���� ������� �����
{
	static int i = 0;
	if ((str[i] == '\0') && (i > 0))//>���� ����� �� ����� ���� ������� ��� ������� ������ �����
	{
		i = 0;
		return 1;
	}

	if ((str[i] < 97) || (str[i] > 122))//���� ����� �� �� ����� ���� ��� ���� �� ��� ����
	{
		i = 0;
		return 0;
	}

	i++;
	return smallLater(str);


}
int size_of_str(char str[SIZE])//������� ������ ������ ������ �� ����� ���
{
	static int length = 0; static int i = 0;
	if (str[i] == '\0')//���� ����� �� ����� ���� �������
	{
		length = i;
		i = 0;
		return length;
	}
	i++;//�� ��� �� ����� ���� ������� ������ ��� ����
	return	size_of_str(str);

}
int length_of_big_later(char str[SIZE])//������� ������ ������ ������ ��� ������ ������ �� ��
{
	static int big_later = 0; static int i = 0; static int count = 0;
	if (str[i] == '\0')//���� ����� �� ����� ���� �������
	{
		big_later = count;
		count = 0; i = 0;
		return big_later;
	}
	if ((str[i] > 64) && (str[i] < 91))//����� �� ��� �����
		count++;
	i++;
	return length_of_big_later(str);
}
int if_str1_at_str2(char str1[SIZE], char str2[SIZE])//������� ������ 2 ������� ������ �� ������� ����� �����
{
	static int location_at_str1 = 0, s = 0, location_at_str2 = 0;
	if ((str1[location_at_str1] == '\0') || (str2[location_at_str2] == '\0'))//���� ����� �� ����� ���� �� ��� ��������
	{
		if (s == strlen(str1))//�� ����� ���� ����� �� ������� �� ���� �������� �����
		{
			location_at_str1 = 0; s = 0; location_at_str2 = 0;
			return 1;
		}

		else//�� ����� �� ���� ����� �� �� ������� �� ������� �� �� ������ �� �����
		{
			location_at_str1 = 0; s = 0; location_at_str2 = 0;
			return 0;
		}

	}

	if (str1[location_at_str1] == str2[location_at_str2])//�� ������� ����� ����� ��� �1
	{

		location_at_str1++;
		s++;
	}
	else if (str1[location_at_str1 - 1] == str2[location_at_str2])//�� ����� ��� ������ ���� ������ ������� ������ ��� ��� ���� ����� ����� ��� ������� ����� ����1
	{
		s = 1;
		location_at_str1 = 1;
	}
	else 
	{
		s = 0;
		location_at_str1 = 0;
	}
	location_at_str2++;
	return	if_str1_at_str2(str1, str2);
}
int main()//������ ������ ����� ��� ������� ��� ����� ����� ������ ������ ����� 6 ��������
{
	int i, check = 0;
	char saction, str1[SIZE], str2[SIZE], str3[SIZE], str4[SIZE];
	puts("enter string number 1");
	gets(str1);
	puts("enter string number 2");
	gets(str2);

	do
	{
		_flushall();
		system("cls");//����� ���� ������ ����
		printf("which saction do you want? \n");
		printf("\t*********************************\n");
		printf("\t  press a check witch string are bigger --\n");
		printf("\t  press b to insert string and check if all the even places at the string are digits--\n");
		printf("\t  press c to insert string and check if all is small letters---\n");
		printf("\t  press d to insert string and check the size of string--\n");
		printf("\t  press e to insert string and check how many big later at string--\n");
		printf("\t  press f to insert 2 strings and to check if string1 Contained at string2--\n");

		printf("\t*********************************\n");
		printf("if you want to exit from the program press y\n");
		scanf("%c", &saction);//����� ������

		switch (saction)
		{
		case 'a':

			i = length_of_str(str1, str2);
			if (i==1)
				puts("the length of str 1 is bigger");
			else if (i==2)
				puts("the length of str 2 is bigger");
			else 	
				puts("the srtings are same");

			_getch();
			break;
		case 'b':
			puts("enter a string");
			_flushall();
			gets(str3);
			i = if_even_plcaes_with_sifra(str3);
			if (i==1)
				puts("all the even place is digits");
			else
				puts("not all the even places digits");
			_getch();
			break;
		case 'c':
			puts("enter string number 3");
			_flushall();
			gets(str3);
			i = smallLater(str3);
			if (i == 1)
				puts("all is small later");
			else
				puts("not all is small latter");
			_getch();
			break;
		case 'd':
			puts("enter string number 3");
			_flushall();
			gets(str3);
			i = size_of_str(str3);
			printf("the size of your string is\t:%d\n", i);
			_getch();
			break;
		case 'e':
			puts("enter string number 3");
			_flushall();
			gets(str3);
			i = length_of_big_later(str3);
			printf("the size of big later at your string is\t:%d\n", i);
			_getch();
			break;
		case 'f':
			puts("enter str 1 that will be the sub string");
			_flushall();
			gets(str3);
			puts("enter string number 2");
			gets(str4);
			i = if_str1_at_str2(str3, str4);
			if (i == 1)
				puts("str1 contained at str 2");
			else puts("str1 not contained at str 2");
			_getch();
			break;
		}
	} while (saction != 'y');
}
