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

#define ROWCOL 10 //account type 

#define ACCTSELT 3
#define LTARROW 75
#define RTARROW 77
#define ENTER 10

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
<<<<<<< HEAD
=======
	float totalBalance;

	//IF TYPE IS X ->
	//X = savings account
	Savings savingType;
	//X = Time account
	Trust trustType;
};
int optTrust();
int optLedger();
int optBenefits();
int optYesNo();
void textHighllght(char[]);
void upperSentence(char[]);
void lowerSentence(char[]);
int accountTypeReg();


//savings account
int SavingMoneyOpts();
void SavingsAcctHistory(acctDet*, int);
void displaySavings(acctDet*, char[]);
void SavingsDeposit(acctDet*, int);
void SavingsWithdraw(acctDet*, int);
void MoneyTransfer(acctDet*, int);

//trust account
void createTrust(acctDet*, int);
void displayTrust(acctDet*, char[]);
void AddLedger(acctDet *aD, int index);
void DeleteLedger(acctDet *aD, int index);
void LinkAccount(acctDet *aD, int index);

>>>>>>> d3997c5... Functions being arranged

	float balance_history[PLIMIT];
	char branch[PLIMIT][CHARLIMIT];
	char date[PLIMIT][CHARLIMIT];

<<<<<<< HEAD
	float totalBalance;
=======
//general functions
int IdChecker(char[], acctDet*);
void acctGenerator(acctDet*);
int getAcctIndex(acctDet*, char[]);
int pinGenerator();
int pinChecker(char[], int, acctDet*);
int scanIfDigits(char[]);

>>>>>>> d3997c5... Functions being arranged

	
};
int accountTypeReg(int);

void acctHistory(acctDet*, int);



#endif