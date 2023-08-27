#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef _WIN32
#include <windows.h>
#include <conio.h>
#include <dos.h>

#else
#include <unistd.h>
#include <termios.h>
#include <ncurses.h>

#endif

void menu(void);
void password(void);
void namefun(void);
void searchfun(void);
void listfun(void);
void modifyfun(void);
void deletefun(void);
void exitfun(void);

void gotoxy(float x, float y){
#ifdef _WIN32
	COORD coord;
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
#else
	move(y, x);
#endif
}

void clscr(){
#ifdef _WIN32
	system("cls");
#else
	clear();
	refresh();
#endif
}

void sleep_ms(int ms){
#ifdef _WIN32
	Sleep(ms);
#else
	usleep(ms * 1000);
#endif
}

char getch_mod(){
#ifdef _WIN32
	return (char) getch();
#else
	struct termios oldt, newt;
	int ch;
	tcgetattr(STDIN_FILENO, &oldt);
	newt = oldt;
	newt.c_lflag &= ~(ICANON | ECHO);
	tcsetattr(STDIN_FILENO, TCSANOW, &newt);
	ch = getchar();
	tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
	return (char) ch;
#endif
}

int main(){
#ifndef _WIN32
	initscr();
	start_color();
	// set text color to blue
	printf("\033[34;47m");
#else
	clscr();
	system("color B");
#endif
	password();
	getch_mod();
#ifndef _WIN32
	// reset text color to white
	printf("\033[0m");
	endwin();
#endif
}

void namefun(){
	clscr();
	gotoxy(31,4);
	printf("\xB3\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB NEW SECTION \xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xB3");
	FILE *fptr;
	char name[100];
	char address[100];
	char gmail[100];
	double phone;
	char gender[8];
	fptr=fopen("ebraj.txt","ab+");//ab+ gives us the ability of writing the function and add the second data in the existing one...
	if(fptr==NULL){
		printf("Failed to create the required file.");
	}
	else{
		gotoxy(31,6);
		printf("Name:\t");
		gotoxy(52,6);
		gets(name);
		gotoxy(31,7);
		printf("Address:\t");
		gotoxy(52,7);
		gets(address);
		gotoxy(31,8);
		printf("Gender:\t");
		gotoxy(52,8);
		gets(gender);
		gotoxy(31,9);
		printf("Gmail:\t");
		gotoxy(52,9);
		gets(gmail);
		gotoxy(31,10);
		printf("Phone Number:\t");
		gotoxy(52,10);
		scanf("%lf",&phone);
		fprintf(fptr,"%s %s %s %s %.0lf\n",name,address,gender,gmail,phone);
	}
	fclose(fptr);
	clscr();
	char ch;
	gotoxy(31,4);
	printf("Do you wanna add more datas. Press y for that: ");
	sleep_ms(1000);
	fflush(stdin);
	while((ch=getch_mod())=='y'){
		menu();
	}
}

void searchfun(){
	FILE *fptr;
	int flag=0;
	int res;
	char name[100];
	char address[100];
	char gmail[100];
	double phone;
	char gender[8];
	char name1[100];
	clscr();
	fflush(stdin);
	gotoxy(18,2);
	printf("\xDB\xDB\xDB Enter the name of the person you want to see the detail: ");
	gets(name1);
	fptr=fopen("ebraj.txt","r");
	//fflush(stdin);
	while(fscanf(fptr,"%s %s %s %s %lf\n",name,address,gender,gmail,&phone)!=EOF){
		res=strcmp(name,name1);
		if(res==0){
			gotoxy(39,4);
			printf("\xB3\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB Record Found \xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xB3");
			gotoxy(28,5);
			printf("----------------------------------------");
			gotoxy(31,6.5);
			printf("\xB3\xB2\xB2\xB2 Name:\t%s",name);
			gotoxy(31,7);
			printf("\xB3\xB2\xB2\xB2 Address:\t%s",address);
			gotoxy(31,8);
			printf("\xB3\xB2\xB2\xB2 Gender:\t%s",gender);
			gotoxy(31,9);
			printf("\xB3\xB2\xB2\xB2 Gmail:\t%s",gmail);
			gotoxy(31,10);
			printf("\xB3\xB2\xB2\xB2 Phone Number:\t%.0lf",phone);
			gotoxy(31,11);
			printf("----------------------------------------");
			flag=1;
			sleep_ms(1000);
			gotoxy(18,12);
			printf("Enter y for menu option.");
			while(getch_mod()=='y'){
				menu();
			}
		}
	}
	if(flag==0){
		clscr();
		gotoxy(39,4);
		printf("No record found.");;
		gotoxy(39,6);
		printf("Enter a to enter file again or double y key to open menu section: ");
		if(getch_mod()=='a'){
			clscr();
			searchfun();
		}
	}
	fclose(fptr);
}

void listfun(){
	FILE *fptr;
	char name[100],address[100],gmail[100],gender[8];
	double phone;
	int f;
	fptr=fopen("ebraj.txt","r");
	clscr();
	gotoxy(31,2);
	printf("\xB3\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB LIST SECTION OPENED \xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xB3");
	printf("\n");
	while(fscanf(fptr,"%s %s %s %s %lf",name,address,gender,gmail,&phone)!=EOF){
		printf("------------------------------------------\n");
		printf("Name:    %s\n",name);
		printf("Address: %s\n",address);
		printf("Gender:  %s\n",gender);
		printf("Gmail:   %s\n",gmail);
		printf("Phone:   %.0lf\n",phone);
		f=1;
		printf("------------------------------------------");
		printf("\n\n");
	}
	sleep_ms(1000);
	printf("Enter y for menu section: ");
	while(getch_mod()=='y'){
		menu();
	}
	fclose(fptr);
}

void modifyfun(){
	FILE *fptr,*fptr1;
	char name[100],address[100],gmail[100],gmail1[100],address1[100],name1[100],gender[8],gender1[8];
	int res,f=0;
	double phone,phone1;
	fptr=fopen("ebraj.txt","r");
	fptr1=fopen("temp.txt","a");
	clscr();
	gotoxy(31,4);
	printf("Enter the name: ");
	gets(name1);
	clscr();
	while(fscanf(fptr,"%s %s %s %s %lf\n",name,address,gender,gmail,&phone)!=EOF){
		res=strcmp(name,name1);
		if(res==0){
			f=1;
			gotoxy(31,4);
			printf("\xB3\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB MODIFY SECTION OPENED \xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xB3");
			gotoxy(31,6);
			printf("Enter the new address: ");
			scanf("%s",address1);
			gotoxy(31,7);
			printf("Enter the gender: ");
			scanf("%s",gender1);
			gotoxy(31,8);
			printf("Enter the new gmail: ");
			scanf("%s",gmail1);
			gotoxy(31,9);
			printf("Enter the new phone number: ");
			scanf("%lf",&phone1);
			fprintf(fptr1,"%s %s %s %s %.0lf\n",name,address1,gender1,gmail1,phone1);
		}else{
			fprintf(fptr1,"%s %s %s %s %.0lf\n",name,address,gender,gmail,phone);
		}
	}
	if(f==0){
		printf("Record Not found.");
	}
	fclose(fptr);
	fclose(fptr1);
	fptr=fopen("ebraj.txt","w");
	fclose(fptr);
	fptr=fopen("ebraj.txt","a");
	fptr1=fopen("temp.txt","r");
	while(fscanf(fptr1,"%s %s %s %s %lf\n",name,address,gender,gmail,&phone)!=EOF){
		fprintf(fptr,"%s %s %s %s %.0lf\n",name,address,gender,gmail,phone);
	}
	fclose(fptr);
	fclose(fptr1);
	fptr1=fopen("temp.txt","w");
	fclose(fptr1);
	printf("\n\nPress y for menu option.");
	fflush(stdin);
	if(getch_mod()=='y'){
		menu();
	}
}

void deletefun(){
	FILE *fptr,*fptr1;
	char name[100],address[100],gmail[100],gmail1[100],address1[100],name1[100],gender[8];
	int res,f=0;
	double phone,phone1;
	fptr=fopen("ebraj.txt","r");
	fptr1=fopen("temp.txt","a");
	clscr();
	gotoxy(31,4);
	printf("Enter the CONTACT name that you want to delete: ");
	gets(name1);
	clscr();
	while(fscanf(fptr,"%s %s %s %s %lf\n",name,address,gender,gmail,&phone)!=EOF){
		res=strcmp(name,name1);
		if(res==0){
			f=1;
			printf("Record deleted successfully");
		}else{
			fprintf(fptr1,"%s %s %s %s %.0lf\n",name,address,gender,gmail,phone);
		}
	}
	if(f==0){
		printf("Record Not found.");
	}
	fclose(fptr);
	fclose(fptr1);
	fptr=fopen("ebraj.txt","w");
	fclose(fptr);
	fptr=fopen("ebraj.txt","a");
	fptr1=fopen("temp.txt","r");
	while(fscanf(fptr1,"%s %s %s %s %lf\n",name,address,gender,gmail,&phone)!=EOF){
		fprintf(fptr,"%s %s %s %s %.0lf\n",name,address,gender,gmail,phone);
	}
	fclose(fptr);
	fclose(fptr1);
	fptr1=fopen("temp.txt","w");
	fclose(fptr1);
	printf("\n\nPress y for menu option.");
	fflush(stdin);
	if(getch_mod()=='y'){
		menu();
	}
}

void exitfun(){
	clscr();
	gotoxy(31,4);
	printf("\xDB\xDB\xDB\xDB TEAM MEMBERS \xDB\xDB\xDB\xDB");
	gotoxy(31,6);
	printf("\xDB EBRAJ GURUNG.");
	gotoxy(31,8);
	printf("\xDB BEEKASH BASAULA.");
	gotoxy(31,10);
	printf("\xDB SAMUNDRA POUDEL.");
	gotoxy(31,12);
	printf("\xDB SAGAR DHAKAL.");
}

void password(void){
	char passwords[20]={"ebrajdon"};
	gotoxy(22,2);
	int j;
	int z;
	char name[40]="Authorized Person Only";
	z=strlen(name);
	for(j=0;j<=16;j++){
		sleep_ms(50);
		printf("\xDB");
	}
	for(j=0;j<=z;j++){
		sleep_ms(60);
		printf(" %c",name[j]);
	}
	for(j=0;j<=16;j++){
		sleep_ms(50);
		printf("\xDB");
	}
	gotoxy(30,4);
	printf("Password: ");
	char ch,pass[20];
	char w='*';
	int i=0;
	while(ch!=13){
		ch=getch_mod();
		if(ch!=13 && ch!=8){
			printf("%c",w);
			pass[i]=ch;
			i++;
		}
	}
	pass[i]='\0';
	if(strcmp(pass,passwords)==0){
		gotoxy(30,6);
		printf("CORRECT PASSWORD.");
		sleep_ms(1000);
		menu();
	}
	else{
		gotoxy(30,6);
		printf("You entered the wrong password.");
		sleep_ms(700);
		clscr();
		password();
	}
}

void menu(){
	clscr();
	gotoxy(30,1);
	printf("\xB3\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2 PHONEBOOK DIRECTORY \xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB3");
	gotoxy(31,4);
	printf("\xB3\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB 1. Add New");
	gotoxy(31,7);
	printf("\xB3\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB 2. Search");
	gotoxy(31,10);
	printf("\xB3\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB 3. List");
	gotoxy(31,13);
	printf("\xB3\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB 4. Modify");
	gotoxy(31,16);
	printf("\xB3\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB 5. Delete");
	gotoxy(31,19);
	printf("\xB3\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB 6. Exit");
	switch(getch_mod()){
		case '1':
			namefun();
			break;
		case '2':
			searchfun();
			break;
		case '3':
			listfun();
			break;
		case '4':
			modifyfun();
			break;
		case '5':
			deletefun();
			break;
		case '6':
			exitfun();
			break;
		default:
			clscr();
			printf("Invalid Enter.");
			getch_mod();
	}
}
