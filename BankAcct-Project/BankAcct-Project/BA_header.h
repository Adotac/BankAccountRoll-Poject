#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <ctype.h>

#define TRUE 0
#define FALSE 1
#define NA -1

#define CHARLIMIT 50
#define PLIMIT 20
#define IDLIMIT 6

//interest rate percentages 
#define SAVING_INTEREST 5 //annual
#define TIME_INTEREST(days) ( (days<=30)?0.5 : (days<=60)?1 : (days<=180)?1.5 : (days<=360)?3 : 4 ) //depends on days
#define TRUST_INTEREST 3 //annual

//ASCII codes
#define ACCTSELT 3
#define LTARROW 75
#define RTARROW 77
#define ENTER 13

#ifndef BA_header
#define BA_header

const char charGenerator[] = {"0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ"};
typedef enum Account_Type accType;
enum Account_Type {SAVINGS, TIME, TRUST};


typedef struct NAME name;
struct NAME {
	char First[CHARLIMIT];
	char Last[CHARLIMIT];
	char Middle[CHARLIMIT];

};
typedef struct Info info;
struct Info {
	name pname;
	int age;
	char city[CHARLIMIT], address[CHARLIMIT];
};

typedef struct AccountDetails acctDet;
struct AccountDetails{
	accType type;
	info inf;
	char acctID[CHARLIMIT];
	int pin;
	float totalBalance;

	//For savings account
	float balance_history[PLIMIT];
	char branch[PLIMIT][CHARLIMIT];
	char date[PLIMIT][CHARLIMIT];
	

	//For Time account, the number of days
	int termsOfPlacement; 

	//
};

void textHighllght(char[]);

void upperSentence(char[]);
void lowerSentence(char[]);
int accountTypeReg();

int SavingMoneyOpts();
void SavingsAcctHistory(acctDet*, int);
void displaySavings(acctDet*, char[]);

int IdChecker(char[], acctDet*);
void acctIdGenerator(acctDet*);

int getAcctIndex(acctDet*, char[]);
int pinGenerator();
int pinChecker(char[], int, acctDet*);



#endif