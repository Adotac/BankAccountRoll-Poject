#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <ctype.h>

#define TRUE 0
#define FALSE 1

#define CHARLIMIT 50
#define PLIMIT 20

#define LTARROW 77
#define RTARROW 75 

#ifndef BA_header
#define BA_header

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
	char city[CHARLIMIT], address[CHARLIMIT];
};

typedef struct AccountDetails acctDet;
struct AccountDetails{
	accType type;
	info inf;
	char acctID[CHARLIMIT];
	int pin;

	float balance_history[PLIMIT];
	char branch[PLIMIT][CHARLIMIT];
	char date[PLIMIT][CHARLIMIT];

	float totalBalance;

	
};

void acctHistory(acctDet*, int);



#endif