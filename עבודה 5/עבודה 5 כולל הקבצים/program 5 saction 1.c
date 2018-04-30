#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<string.h>
#define SIZE 5
//************************************
		// תרגיל מספר 1

//************************************

void ScanRec(int *arr, int size)//פונקציה רקורסיבית שקולטת מספרים לתוך מערך
{
	static int i = 0;

	if (size == 0)//בדיקת יציאה אם הגענו לסוף המערך
	{
		i = 0;
		return;
	}

	printf("\nenter the %d number\n", i + 1);
	scanf("%d", &arr[i++]);
	return ScanRec(arr, size - 1);

}
void ThreeDigits(int *arr, int size)//פונקציה שבודקת כמה מספרים תחת ספרתיים קיימים במערך
{
	static int s = 0; static int i = 0;
	if (size == 0)//בדיקת יציאה אם הגענו לסוף המערך
	{
		printf("there are %d numbers with 3 digits in arr\n", s);
		i = 0;
		s = 0;
		return;
	}
	if ((arr[i] / 100 > 0) && (arr[i] / 100 < 10))//בדיקה אם האיברים במערך תלת ספרתיים
		s++;

	i++;
	return ThreeDigits(arr, size - 1);

}
int first(int num)// פונקציה שבודקת אם מספר הוא ראשוני
{
	static int i = 2;
	if (i == num)//בדיקת יציאה אם בדקנו את כל המחלקים של המספר ולא נמצאו מחלקים
	{
		i = 2;
		return 1;
	}
	if (num % i == 0)//בדיקת יציאה אם מצאנו לפחות מחלק אחד
	{
		return 0;
	}
	i++;
	return first(num);

}
int first_numbers_at_array(int *arr, int size)//פונקציה שבודקת כמה איברים במערך הם מספרים ראשוניים 
{
	int static i = 0, count = 0; int amount_of_firsts;
	if (i == size)
	{
		amount_of_firsts = count;
		count = 0;
		i = 0;
		return amount_of_firsts;
	}
		
	count = count + first(*(arr + i));//קריאה לפנוצקיה שבודקת אם מספר הוא ראשוני, על כל איבר במערך
	i++;
	return first_numbers_at_array(arr, size);
}
int main()//התכנית קולטת מספר שהוא יהיה גודל המערך ומציגה תפריט למשתמש באיזה פונקציות לבחור
{
	int *arr, i, size, s = 0, num, check = 0;
	char saction;
	puts("enter the size of arr");
	scanf("%d", &size);
	arr = (int*)malloc(size*sizeof(int));//הקצאה דינמית של המערך
	do
	{
		_flushall();
		system("cls");//ניקוי המסך בהפעלה חדשה
		printf("which saction do you want? \n");
		printf("\t*********************************\n");
		printf("\t  press a to insert numbers to arr --\n");
		printf("\t  press b to check how many numbers in arr with 3 digits--\n");
		printf("\t  press c to insert number and check if it is first number --\n");
		printf("\t  press d to check how many numbers in arr are first numbers--\n");
		printf("\t*********************************\n");
		printf("if you want to exit from the program press y\n");
		scanf("%c", &saction);//בחירת המשתמש

		switch (saction)
		{
		case 'a'://אם המשתמש בחר להפעיל את האפשרות הראשונה
			printf("\nadd %d integers to fill arr\n", size);
			ScanRec(arr, size);
			printf("\narray : \n{");
			for (i = 0; i < size; i++)//הדפסה של המערך שנקלט למשתמש
				printf("%d,  ", arr[i]);
			printf("}\n");
			check = 1;//מצב בדיקה שמתעדכן כשממלאים את המערך
			_getch();
			break;
		case 'b':
			if (check == 0)//אם עוד לא מילאנו את המערך תודפס הודעת שגיאה למשתמש
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
			scanf("%d", &num);//המשתמש מזין מספר והפונקציה בודקת אם הוא ראשוני או לא
			i=first(num);
			if (i==1)
				printf("the number %d is first\n", num);
			else 
				printf("the number %d is not first\n", num);
			_getch();
			break;
		case 'd':
			if (check == 0)//אם עוד לא מילאנו את המערך תודפס הודעת שגיאה למשתמש
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
	free(arr);// שחרור המערך
}



