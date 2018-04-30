#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
//************************************
//
// תרגיל מספר 4
//
//************************************
#define GODEL1 21//מציין את הגודל המקסימילי של סוג המודל של המחשב
#define GODEL2 81//מציין את הגודל המקסימלי של שמו של היצרן של המחשב
#define DATA "data2.txt"//מציין את שם הקובץ שנשתמש בו,אם ברצונך להשתמש בקובץ אחר שנה את השם במשתנה הגלובלי
typedef struct//הגדרת המבנה
{
	char model[21];//סוג המודל
	char manufacturer[81];//שם היצרן
	int memory;//גודל הזכרון
	int year;//שנת היצור של המחשב
}computers;
void new_file_of_computer(FILE *file)// פונקציה שמייצרת קובץ חדש
{
	char status, model[21], manufacturer[81];
	int memory, year;
	puts("If you want to add computer details press 'a', for exit press 'q'");
	_flushall();
	scanf("%c", &status);
	while (status == 'a')
	{
		puts("Enter the model of your coputer,his manufacturer,the size of his memory and his Year of Production");
		scanf("%s %s %d %d", &model, &manufacturer, &memory, &year);//קליטת הנתונים מהמשתמש והדפסתם בקובץ
		fprintf(file,"%s %s %d %d", model, manufacturer, memory, year);
		fprintf(file, "\n");
		puts("If you want to add computer details press 'a', for exit press 'q'");
		_flushall();
		scanf("%c", &status);
	}
	
	fclose(file);//סגירת הקובץ
	
}
computers* scan_from_file(computers *arr, FILE *file,int *size)//פונקציה שקולטת מהקובץ למערך ומקצה אותו דינמית
{
	int  i = 0;
	while (!feof(file))// בדיקה כל עוד לא הגענו לסוף הקובץ
	{
		*size = *size+1;//הגדלת הגודל של המשתנה בכל סיבוב כל עוד לא הגענו לסוף הקובץ
		arr = (computers*)realloc(arr, *size*sizeof(computers));//הקצאה דינמית של המערך 
		if (arr == NULL)
		{
			puts("EROR!! dont have enough memory!!");
			exit(1);
		}
		fscanf(file, "%s %s %d %d\n", &arr[i].model, &arr[i].manufacturer, &arr[i].memory, &arr[i].year);//קלט מהקובץ למערך הדינמי של המבנים
		i++;
	}
	*size = *size - 1;
	arr = (computers*)realloc(arr, *size*sizeof(computers));//עדכון סופי לגודל המערך הדינמי המדויק
	fclose(file);//סגירת הקובץ
	return arr;//החזרת הכתובת של המערך
}
void big_memory(computers *arr, int *size)//פונקציה שבודקת במאגר מי המחשב עם הזכרון הגדול ביותר
{
	int i, big = arr[1].memory;
	for (i = 1; i < *size; i++)//לולאת שעוברת על כל המערך ומוצאת את הזיכרון הגדול ביותר
		if (arr[i].memory > big)
			big = arr[i].memory;			
	
	puts("The details of the computer\s with the big memory are:");
	puts("*******************************");
	for ( i = 0; i < *size; i++)//הדפסת הפרטים של המחשב עם הזכרון הגדול ביותר
		if (arr[i].memory == big)
		{
			printf("%s\t %s\t %dGB\t %d\n\n", arr[i].model, arr[i].manufacturer, arr[i].memory, arr[i].year);
		}
	puts("*******************************");
}
void after_2014(computers *arr, int *size)//פונקציה שבודקת אילו מחשבים יוצרו אחרי שנת 2014
{
	int i,status=0;
	for (i = 0; i < *size; i++)//לולאת שעוברת על המערך ומדפיסה את הפרטים של המחשבים שיוצרו אחרי 2014
		if (arr[i].year>2014)
		{
			status = 1;
			puts("The details of the computer\s that produced after 2014 are:\n");
			printf("%s\t %s\t %dGB\t %d\n", arr[i].model, arr[i].manufacturer, arr[i].memory, arr[i].year);
		}
	if (status == 0)//אם אין מחשבים כאלה תודפס הודעה בהתאם
		puts("No computer manufactured after 2014");
}
void print_the_file(computers *arr, int *size)//פונקציה שמדפיסה את הערכים שנקלטו מהקובץ למערך
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
char clean_screen()//פונקציה שמנקה את המסך ומציגה את התפריט בכל פעם
{
	char saction;
	_flushall();
	system("cls");//ניקוי המסך בהפעלה חדשה
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
void main()//התכנית הראשית שבה מוצג למשתמש תפריט
{
	int size=1,status=0;
	char saction;
	computers *arr = (computers*)calloc(1 , sizeof(computers));//הקצאה דינמית ראשונית למערך
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
			//*** כדיי לפתוח קובץ חדש תשחרר את הסימון של case 'a'****

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
			if ((file = fopen(DATA, "r")) == NULL)//פתיחת הקובץ הקיים לקריאה
			{
				printf("ERROR: the file canot be opened!\n"); 
				_getch();
				break; 
			}
			arr = scan_from_file(arr, file, &size);//הפעלת הפונקציה שקולטת מהקובץ למערך
			puts("\n***your file opend Correctly,you can use with the file***");
			_getch();
			break;
		case 'c':
			if (status == 0)//סטטוס מצב לבדוק שהמשתמש פתח קודם קובץ
			{
				puts("EROR!! you need to open file before!");
				_getch();
				break;
			}
			big_memory(arr, &size);//הפעלת הפונקציה שבודקת מי המחשב עם הזכרון הגדול ביותר במאגר
			_getch();
			break;
		case 'd':
			if (status == 0)//סטטוס מצב לבדוק שהמשתמש פתח קודם קובץ
			{
				puts("EROR!! you need to open file before!");
				_getch();
				break;
			}
			after_2014(arr, &size);//הפעלת הפונקציה שבודקת אילו מחשבים יוצרו אחרי שנת 2014
			_getch();
			break;
		case 'p':
			if (status == 0)//סטטוס מצב לבדוק שהמשתמש פתח קודם קובץ
			{
				puts("EROR!! you need to open file before!");
				_getch();
				break;
			}
			print_the_file(arr, &size);//הפעלת הפונקציה של ההדפסה
			_getch();
			break;
		}
	} while (saction != 'q');
	free(arr);//שחרור המערך 
}