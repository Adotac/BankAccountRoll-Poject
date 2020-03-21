#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <ctype.h>
#include <stdarg.h>

#define ADMPASS "0"
#define NULL 0
#define CNULL '\0'
#define SNULL "\0"

#define TRUE 1
#define FALSE 0
#define NA -1

#define CHARLIMIT 15
#define PLIMIT 10
#define IDLIMIT 6

//ASCII codes
#define LTARROW 75
#define RTARROW 77
#define UPARROW 72
#define DWARROW 80
#define ENTER 13

#define INTEREST 0.03
#define TAX 0.8

#define MIN_INITIAL 50000

#ifndef BA_header
#define BA_header

const char currentBranch[] = {"Basak"};
const char charGenerator[] = {"0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ"};
typedef enum Account_Type accType;
enum Account_Type {SAVINGS, TIME, TRUST};

typedef enum Trust_Benefits Tbenefits;
enum Trust_Benefits {Null, SUCCESSOR, CHARITY, RETIREMENT};


typedef struct TrustDetails Trust;
struct TrustDetails{
	char acctID[IDLIMIT];

	Tbenefits benefitType;

	char assets[PLIMIT][CHARLIMIT];
	char assetHistDate[PLIMIT][CHARLIMIT];
	float assetAmount;
	float assetAmtHistory[PLIMIT];

	char liabilities[PLIMIT][CHARLIMIT];
	char liabHistDate[PLIMIT][CHARLIMIT];
	float liabAmount;
	float liabAmtHistory[PLIMIT];

	float totalBalance;

	char linkedBankAcct[IDLIMIT]; // Time||savings account
	accType linkedtype;
	
};

typedef struct SavingsDetails Savings;
struct SavingsDetails{
	char acctID[IDLIMIT];
	
	float totalBalance;
	float balance_history[PLIMIT];
	char branch[PLIMIT][CHARLIMIT];
	char date[PLIMIT][CHARLIMIT];
};

typedef struct TimeDetails Time;
struct TimeDetails{
	char acctID[IDLIMIT];

	float totalBalance;
	float interestBalance;
	char branch[CHARLIMIT];
	char date[CHARLIMIT];

};

typedef struct AccountDetails acctDet;
struct AccountDetails{
	/* IMPORTANT!!! 
	Account Id will serve as universal 
	variable for checking all accounts
	*/
	char acctID[IDLIMIT]; 

	int pin;
	accType type;
	
	char First[CHARLIMIT];
	char Last[CHARLIMIT];
	char Middle[CHARLIMIT];
	
	int age;
	char city[CHARLIMIT];
	char address[CHARLIMIT];

	//flag if deleted or not
	int deleted;
};
int LoginScreen();
int optTrust();
int optLedger();
int optBenefits();
int optYesNo();
int optAdmin();

int optTime(acctDet *aD, Time *tiD);
int optW_Money(Time *tiD);
void textHighllght(char[]);
void upperSentence(char[]);
void lowerSentence(char[]);
void dateExtractor(char format, char *date, void *output);
int accountTypeReg();
const char *typeIdentifier(accType);
const char *trustIdentifier(Tbenefits);
void deleteAccount(char userId[], acctDet* aD, FILE *acdb);
void searchDisplay(acctDet *aD, Savings *svD, Time *tiD, Trust *trD);

void getInfo(acctDet*);

void readFiles(acctDet** aD, Time **tiD, Trust **trD, Savings **svD, FILE **trdb, FILE **svdb, FILE **tidb, FILE **acdb);
int FindIdFileSetter(char searchId[], const char *format, ...);
void UpdateFiles(char accID[], const char *format, ...);
long int cursorFileSeeker(char arr[], FILE *fptr, const char format, ...);

//general functions
int IdChecker(char inputID[], acctDet* aD, FILE *acdb);
void acctGenerator(acctDet* aD, Time *tiD, Trust *trD, Savings *svD, FILE *trdb, FILE *svdb, FILE *tidb, FILE *acdb);
int pinGenerator();
int pinChecker(char inputId[], int inPin, acctDet* aD, FILE *acdb);
int scanIfDigits(char[]);


//savings account
int SavingMoneyOpts();
void SavingsAcctHistory(SavingsDetails*);
void displaySavings(char inpId[], Savings* svD, acctDet *aD, Time *tiD, FILE *acdb, FILE *svdb , FILE *tidb);
void SavingsDeposit(SavingsDetails*);
void SavingsWithdraw(SavingsDetails*);
int createSav();

void MoneyTransfer(char userId[], Savings* svD, acctDet *aD, Time *tiD, FILE *acdb, FILE *svdb, FILE *tidb);

//trust account
void createTrust(char userId[], acctDet *aD, Trust* trD);
void displayTrust(char inpuId[], acctDet *aD, Trust* trD, Savings *svD, Time *tiD, FILE *acdb, FILE *trdb, FILE *svdb, FILE *tidb);
void AddLedger(Trust**, char userId[] );
void DeleteLedger(Trust**trD, char userId[]);
void LinkAccount(Trust** trD, acctDet *aD, FILE *acdb);

//Time deposit
void TimeDeposit(char userId[], Savings* svD, acctDet *aD, Time *tiD, FILE *acdb, FILE *svdb , FILE *tidb);
void withrawMoney(Time *tiD);
void moneyWithrawal(Time *tiD);
void calculateTimeDeposit();
void checkMoney(char userId[], Savings* svD, acctDet *aD, Time *tiD, FILE *acdb, FILE *svdb , FILE *tidb);
void depositMoney(Time *tiD);
int createTime();


//admin
void adminPanel(acctDet* aD, Savings *svD, Time *tiD, Trust *trD, FILE *acdb, FILE *svdb, FILE *tidb, FILE *trdb);
void displayAllAcct(acctDet* aD, FILE **acdb);
void displaySavAccts(Savings *svD, FILE **svdb, acctDet* aD, FILE **acdb);
void displayTimeAccts(Time *tiD, FILE **tidb, acctDet* aD, FILE **acdb);
void displayTrustAccts(Trust *trD, FILE **trdb, acctDet *aD, FILE** acdb);
void searchAcct(acctDet* aD, Savings *svD, Time *tiD, Trust *trD, FILE *acdb, FILE *svdb, FILE *tidb, FILE *trdb);

#endif