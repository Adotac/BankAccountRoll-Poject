#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <ctype.h>

#define ADMPASS "0987654321"
#define TRUE 0
#define FALSE 1
#define NA -1

#define CHARLIMIT 50
#define PLIMIT 100
#define IDLIMIT 6

//ASCII codes
#define LTARROW 75
#define RTARROW 77
#define UPARROW 72
#define DWARROW 80
#define ENTER 13

#define INTEREST 0.03
#define TAX 0.8
#define DEPOSIT 150000

#ifndef BA_header
#define BA_header

const char currentBranch[] = {"Basak"};
const char charGenerator[] = {"0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ"};
typedef enum Account_Type accType;
enum Account_Type {SAVINGS, TIME, TRUST};

typedef enum Trust_Benefits Tbenefits;
enum Trust_Benefits {Null, SUCCESSOR, SCHOLARSHIP, RETIREMENT_PLAN};

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

typedef struct TrustDetails Trust;
struct TrustDetails{

	Tbenefits benefitType;
	char benefit[CHARLIMIT];
	Info beneficiaryInfo;

	char assets[PLIMIT][CHARLIMIT];
	char assetHistDate[PLIMIT][CHARLIMIT];
	float assetAmount;
	float assetAmtHistory[PLIMIT];

	char liabilities[PLIMIT][CHARLIMIT];
	char liabHistDate[PLIMIT][CHARLIMIT];
	float liabAmount;
	float liabAmtHistory[PLIMIT];

	char linkedBankAcct[IDLIMIT]; // Time||savings account
};

typedef struct SavingsDetails Savings;
struct SavingsDetails{
	float balance_history[PLIMIT];
	char branch[PLIMIT][CHARLIMIT];
	char date[PLIMIT][CHARLIMIT];
};

typedef struct AccountDetails acctDet;
struct AccountDetails{
	accType type;
	info inf;
	char acctID[IDLIMIT];
	int pin;
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
int optAdmin();
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



//general functions
int IdChecker(char[], acctDet*);
void acctGenerator(acctDet*);
int getAcctIndex(acctDet*, char[]);
int pinGenerator();
int pinChecker(char[], int, acctDet*);
int scanIfDigits(char[]);


//Time deposit
void calculateTimeDeposit();
void showMoney(float *principalMoney);
void checkMoney(float *principalMoney);
void depositMoney(float *principalMoney);
void withrawMoney(float *principalMoney);
void TimeDeposit(acctDet *aD, int index);

void deleteAccount(acctDet*, int);

void getInfo(acctDet*, int);


//admin
void adminPanel(acctDet*);

#endif