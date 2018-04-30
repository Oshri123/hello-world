#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
//************************************
//
// תרגיל מספר 3
//
//************************************
#define YEAR 10// הפרש הגילאים המקסימלי שמאפשרת התאמה
#define GODEL 3// מספר התחומי עניין
#define GODEL2 21// גודל מקסימלי של כל תחום עניין וגודל מקסימילי של כל שם
#define DATA "data.txt"//משתנה גלובלי של שם הקובץ שנשתמש בתוכנית. אם אתה רוצה להשתמש בקובץ אחר תשנה את השם
typedef struct
{
	char name[GODEL2];//שם הלקוח
	char gender;//מין הלקוח
	int age;//גיל הלקוח
	char interests[GODEL][GODEL2];//מערך שבתוכו 3 תחומי עניין של הלקוח
}client;// הגדרת המיבנה
void create_new_file(FILE *file)//פונקציה שמייצרת קובץ טקסט חדש
{
	int age, i;
	char name[GODEL2], gender, interests[GODEL][GODEL2], add_client;
	if ((file = fopen(DATA, "w")) == NULL)// פתיחת הקובץ לכתיבה ובדיקה אם זה מתאפשר
	{
		puts("EROR!! cant write on this file!");
		return;
	}
	puts("If you want to insert client press 'a', to end the file press else key!");
	_flushall();
	scanf("%c", &add_client);
	while (add_client == 'a')//לולאה שמוסיפה אנשים לקובץ 
	{
		puts("enter Name,\tGender (m,f),\tAge\tand 3 interests");
		scanf("%s %c %d", name, &gender, &age);
		fprintf(file,"%s\t %c\t %d", name, gender, age);//הדפסה לקובץ מהנתונים שנקלטו
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
	fclose(file);//סגירת הקובץ
}
client* scan_from_file(FILE *file, int *size)//פונקציה שקולטת מהקובץ למערך ומקצה אותו דינמית
{
	int i = 0, j;
	client *arr = (client*)calloc(*size,sizeof(client));
	if (arr == NULL)
	{
		puts("EROR!!, dont have enough memory!");
		exit(1);
	}
	while (!feof(file))// בדיקה כל עוד לא הגענו לסוף הקובץ
	{

		fscanf(file, "%s %c %d", arr[i].name, &arr[i].gender, &arr[i].age);//קלט מהקובץ למערך הדינמי של המבנים
		for (j = 0; j < GODEL; j++)
		{
			fscanf(file, "%s\n", arr[i].interests[j]);
			fscanf(file, " ");
		}
		fscanf(file, "\n");
		*size = *size + 1;//הגדלת המצביע ב1 בכל סיבוב של הגדלת המערך וקליטת הנתונים
		arr = (client*)realloc(arr, *size*sizeof(client));//הקצאה דינמית חדשה למערך
		if (arr == NULL)
		{
			puts("EROR!! dont have memory!!");
			exit(1);
		}
		i++;
	}
	*size = *size - 1;
	arr = (client*)realloc(arr, *size*sizeof(client));//עדכון סופי לגודל המערך הדינמי המדויק
	fclose(file);
	return arr;//החזרת הכתובת של המערך

}
void print_file(client *arr, int *size)//פונקציה שמדפיסה את הערכים שנקלטו מהקובץ למערך
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
client open_new_client()//פונקציה לפתיחת קליינט חדש שמחפש התאמה מהמאגר
{
	int i;
	client new_client;//הגדרת משתנה מסוג המבנה הקיים
	puts("enter your first Name,\tGender (press 'm' for male,'f' for female),Your age and Enter 3 interests");
	scanf("%s %c %d", new_client.name, &new_client.gender, &new_client.age);//קליטת הפרטים של הלקוח החדש
	for (i = 0; i < GODEL; i++)
		scanf("%s", new_client.interests[i]);
	return new_client;//החזרת הנתונים של הלקוח החדש
}
int interst(client *arr, char new_client[][21], int k)//פונקציה שבודקת אם יש ללקוח החדש תחביבים משותפים עם הלקוחות במאגר. 
{
	int i, j;
	for (i = 0; i < GODEL; i++)
		for (j = 0; j < GODEL; j++)
			if (strcmp(arr[k].interests[j], new_client[i]) == 0)//שימוש בפונקציה לבדיקת מחרוזות כדיי לבדוק התאמה בתחביבים
				return 1;
	return 0;
}
void check_for_adjustment(client *arr, int *size)//פונקציה שבודקת התאמה כוללת של כל פרטיו של הלקוח החדש עם המאגר הקיים
{
	int i = 0, s = 0;
	client new_client = open_new_client();
	for (i = 0; i < *size; i++)//לולאה ראשית שעוברת על כל המאגר
	{
		if ((abs(new_client.age - arr[i].age) <= YEAR) && (new_client.gender != arr[i].gender))//בדיקה לאיזה לקוחות מהמאגר יש מין שונה וההפרש גילאים לא עולה על 10 שנים
		{
			if (interst(arr, new_client.interests, i) == 1)//בדיקה אם יש לפחות תחביב אחד משותף,אם כל התנאים מתקיים מודפסת הודעה מתאימה עם פרטיו של הלקוח שמותאם ללקוח החדש
			{
				puts("*****************************************************************");
				printf("your pairing is: %s\n%c,  %d,  %s,  %s,  %s\n", arr[i].name, arr[i].gender, arr[i].age, arr[i].interests[0], arr[i].interests[1], arr[i].interests[2]);
				puts("*****************************************************************");
				s = 1;
			}

		}
	}
	if (s == 0)//אם לא נמצאה התאמה תודפס הודעה בהתאם
	puts("Sorri, we cant find you any pairing!");
	_getch();
}
char clean_screen()//פונקציה שמנקה את המסך ומציגה את התפריט בכל פעם
{
	char saction;
	_flushall();
	system("cls");//ניקוי המסך בהפעלה חדשה
	puts("***************************************************************");
	puts("\tTo open the file press 'f'");
	puts("\tFor check for adjustment press'c'");
	puts("\tif you want to print the file press 'p'");
	puts("\tFor exit press 'q'");
	puts("***************************************************************");
	scanf("%c", &saction);
	return saction;
}
void main()//התכנית הראשית שבה מוצג למשתמש תפריט
{
	int size = 1, status = 0;
	char saction;
	client *arr=NULL;
	FILE *file=NULL;
	do{
		saction = clean_screen();
		switch (saction)
		{

			//*** כדיי לפתוח קובץ חדש תשחרר את הסימון של case 'a'****

		/*case 'a':
			status = 1;
			create_new_file(file);
			file = fopen(file_name, "r");
			arr = scan_from_file(file, &size);
			_getch();
			break;*/


		case 'f':
			status = 1;
			file = fopen(DATA, "r");//פתיחת הקובץ הקיים לקריאה
			if (file == NULL)
			{
				puts("EROR!! The file canot be found!!");
				exit(1);
			}
			arr = scan_from_file(file, &size);//קריאה לפונקציה שקולטת מהקובץ
			puts("\nyour file opend Correctly,you can use with the file");
			_getch();//הקפאת המסך
			break;
		case 'p'://הדפסת הנתונים שבקובץ
			if (status == 0)
			{
				puts("EROR!! you need to open file before!");
				_getch();
				break;
			}
			print_file(arr, &size);
			_getch();
			break;
		case 'c'://קריאה לפו נקציה שבודקת התאמה בין הלקוח החדש למאגר
			check_for_adjustment(arr, &size);
			break;
		}
	} while (saction != 'q');
	free(arr);//שחרור המערך
}
