#include "BA_header.h"

//display savings account
void displaySavings(char inpId[], Savings* svD, acctDet *aD, Time *tiD, FILE *acdb, FILE *svdb , FILE *tidb){
	
	int opt = NULL, sFlag = TRUE; 

	if(FindIdFileSetter(inpId, "FA, FS", acdb, aD, svdb, svD) != TRUE){
		printf("\n\n\nError! Corrupted Account");
		getch();
		return;
	}

	do{
		system("cls");
		flushall();
		printf("\n%s %s %s", aD->First, aD->Middle, aD->Last);

		SavingsAcctHistory(svD);
		opt = SavingMoneyOpts();

		switch(opt){
		case 1://Deposit
			SavingsDeposit(svD);
		
				break;
		case 2://Withdraw
			SavingsWithdraw(svD);
			
			break;
		case 3:
			MoneyTransfer(inpId, svD, aD, tiD, acdb, svdb, tidb);
			break;
		case 4:
			sFlag = FALSE;
			break;
		default:
			//loop
			break;
			
		}
	}while(sFlag == TRUE);
		
	
	
}


//Savings Account
void SavingsAcctHistory(Savings* svD){
	svD->totalBalance = 0;
	printf("\n||DEPOSITED AMOUNT\t||BRANCH\t||DATE\n");

	for(int i = 0; i < PLIMIT; i++){
		if(svD->balance_history[i] != CNULL){
			printf("\n||%15.2f\t||%10s\t||%5s", svD->balance_history[i], svD->branch[i], svD->date[i]);
			svD->totalBalance += svD->balance_history[i];
		}
		else
			break;	
	}
	printf("\n||Total: %15.2f\n\n", svD->totalBalance);
	
}
void SavingsDeposit(Savings* svD){
	char scannedAmount[CHARLIMIT];
	float amount;
	system("cls");
	printf("\nHow much do you want to Deposit: ");
	gets(scannedAmount);

	if(scanIfDigits(scannedAmount) == TRUE){
	amount = atof(scannedAmount);

		//search slot in history
		for(int i = 0; i < PLIMIT; i++){
			if(svD->balance_history[i] == NULL){
				svD->balance_history[i] = amount;
				strcpy(svD->branch[i], currentBranch);
				strcpy(svD->date[i], __DATE__);
				break;
			}
		}
	}
	else{
		printf("\n\nError input, returning to previous...");
	}
	
	getch();
	system("cls");
	
}
void SavingsWithdraw(Savings* svD){
	char scannedAmount[CHARLIMIT];
	float amount;
	system("cls");
	printf("\nHow much do you want to Withdraw: ");
	gets(scannedAmount);
	
	if(scanIfDigits(scannedAmount) == TRUE){
		amount = atof(scannedAmount);
		if(amount > svD->totalBalance){
			printf("\nYou don't have enough money!!");
			getch();
			return;
		}


		amount = -amount; //negative

		//search slot in history
		for(int i = 0; i < PLIMIT; i++){
			if(svD->balance_history[i] == NULL){
				svD->balance_history[i] = amount;
				strcpy(svD->branch[i], currentBranch);
				strcpy(svD->date[i], __DATE__);
				break;
			}
		}
	}
	else{
		printf("\n\nError input, returning to previous...");
	}
	
	
	getch();
	system("cls");
}

int createSav(){
	float initial = 0;
	system("cls");
	printf("\nOne last step!");
	printf("\nEnter an initial amount(any amount): ");
	scanf(" %f", &initial);

	if(initial < 0){
		return NA;
	}

	return initial;
}


void MoneyTransfer(char userId[], Savings* svD, acctDet *aD, Time *tiD, FILE *acdb, FILE *svdb, FILE *tidb){
	//SNULL if borrow
	
	char *inputT_ID, scannedAmount[CHARLIMIT];
	inputT_ID = (char*)calloc(sizeof(char), IDLIMIT);
	float transferAmt;

	system("cls");

	

	printf("\nEnter the ACCOUNT ID of which you want for Transfer: ");
	gets(inputT_ID);
	upperSentence(inputT_ID);
	printf("\nHow much amount do you want to Transfer: ");
	gets(scannedAmount);

	if(scanIfDigits(scannedAmount) == FALSE){
		printf("\nError in input, try again....");	
		getch();
		return;
	}

	//for time account borrow
	if(strcmp(userId, SNULL) == 0){
		memcpy(userId, inputT_ID, IDLIMIT);
		printf("\n\nEnter your ACCOUNT ID: ");
		fflush(stdin);
		gets(inputT_ID);
		upperSentence(inputT_ID);
	}

	transferAmt = atof(scannedAmount);

	if(IdChecker(inputT_ID, aD, acdb) == TRUE){
		switch(aD->type){
		case SAVINGS:
			
			//transacted account's history
			if(FindIdFileSetter(inputT_ID, "FA,FS", acdb, aD,svdb, svD) == TRUE){
				for(int i = 0; i < PLIMIT; i++){
					if(svD->balance_history[i] == NULL){
						svD->balance_history[i] = transferAmt;
						strcpy(svD->branch[i], currentBranch);
						strcpy(svD->date[i], __DATE__);
						break;
					}
				}
				printf("\nTransfer Successful!");
				printf("\n%.2f has been tranferred to %s", transferAmt, inputT_ID);

				UpdateFiles(inputT_ID, "FS", svdb, svD);
			}

			//reset to user's struct
			//user's history
			if(FindIdFileSetter(userId, "FA,FS", acdb, aD,svdb, svD) == TRUE){
				for(int i = 0; i < PLIMIT; i++){
					if(svD->balance_history[i] == NULL){
						svD->balance_history[i] = (-transferAmt);
						strcpy(svD->branch[i], currentBranch);
						strcpy(svD->date[i], __DATE__);
						break;
					}
				}
			
			}

			UpdateFiles(inputT_ID, "FS", svdb, svD);
			break;
		case TIME:
			if(FindIdFileSetter(inputT_ID, "FA,FI", acdb, aD,tidb, tiD) == TRUE){
				tiD->totalBalance += transferAmt;

				printf("\nTransfer Successful!");
				printf("\n%.2f has been tranferred to %s", transferAmt, inputT_ID);
				UpdateFiles(inputT_ID, "FI", tidb, tiD);
			}
			
			break;
		case TRUST:

			printf("\nCannot Transfer to a Trust Account! Due to some regulations...");
			break;
		}
	}
	else{
		printf("\nAccount doesn't exist!! ");
	}
	
	getch();
	system("cls");
}