#include "BA_header.h"

//display savings account
void displaySavings(acctDet *aD, char inpId[]){
	int index = getAcctIndex(aD, inpId);
	int opt = NULL, sFlag = TRUE;


	if(index != NA){
		do{
			system("cls");
			flushall();
			printf("\n%s %s %s", aD[index].inf.pname.First, aD[index].inf.pname.Middle, aD[index].inf.pname.Last);
			SavingsAcctHistory(aD, index);
			opt = SavingMoneyOpts();
			switch(opt){
			case 1://Deposit
				SavingsDeposit(aD, index);
			
				break;
			case 2://Withdraw
				SavingsWithdraw(aD, index);
				
				break;
			case 3:
				MoneyTransfer(aD, index);
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
	
}
// S Money options
int SavingMoneyOpts(){
	char key;
	int iCtr = 1;

	do{

		switch(iCtr){
		case 1:
			textHighllght("[DEPOSIT]");
			printf("\t");
			printf("[WITHDRAW]");
			printf("\t");
			printf("[MONEY TRANSFER]");
			printf("\t");
			printf("[EXIT]");
			break;
		case 2:
			printf("[DEPOSIT]");
			printf("\t");
			textHighllght("[WITHDRAW]");
			printf("\t");
			printf("[MONEY TRANSFER]");
			printf("\t");
			printf("[EXIT]");
			break;
		case 3:
			printf("[DEPOSIT]");
			printf("\t");
			printf("[WITHDRAW]");
			printf("\t");
			textHighllght("[MONEY TRANSFER]");
			printf("\t");
			printf("[EXIT]");
			break;
		case 4:
			printf("[DEPOSIT]");
			printf("\t");
			printf("[WITHDRAW]");
			printf("\t");
			printf("[MONEY TRANSFER]");
			printf("\t");
			textHighllght("[EXIT]");
			break;
		
		}

		key = getch();
		switch(key){
		case LTARROW:
			iCtr--;
			if(iCtr < 1)
				iCtr = 1;
			break;
		case RTARROW:
			iCtr++;
			if(iCtr > 4)
				iCtr = 4;
			break;
		case ENTER:
			return iCtr;
			break;
		}
	
	printf("\r");
	}while(key != ENTER);

}
//Savings Account
void SavingsAcctHistory(acctDet *aD, int accIndex){
	aD[accIndex].totalBalance = 0;
	printf("\n||DEPOSITED AMOUNT\t||BRANCH\t||DATE\n");

	for(int i = 0; i < PLIMIT; i++){
		if(aD[accIndex].savingType.balance_history[i] != NULL){
			printf("\n||%15.2f\t||%10s\t||%5s", aD[accIndex].savingType.balance_history[i], aD[accIndex].savingType.branch[i], aD[accIndex].savingType.date[i]);
			aD[accIndex].totalBalance += aD[accIndex].savingType.balance_history[i];
		}
		else
			break;	
	}
	printf("\n||Total: %15.2f\n\n", aD[accIndex].totalBalance);
	
}
void SavingsDeposit(acctDet *aD, int index){
	char scannedAmount[CHARLIMIT];
	float amount;
	system("cls");
	printf("\nHow much do you want to Deposit: ");
	gets(scannedAmount);

	if(scanIfDigits(scannedAmount) == TRUE){
	amount = atof(scannedAmount);

		//search slot in history
		for(int i = 0; i < PLIMIT; i++){
			if(aD[index].savingType.balance_history[i] == NULL){
				aD[index].savingType.balance_history[i] = amount;
				strcpy(aD[index].savingType.branch[i], currentBranch);
				strcpy(aD[index].savingType.date[i], __DATE__);
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
void SavingsWithdraw(acctDet *aD, int index){
	char scannedAmount[CHARLIMIT];
	float amount;
	system("cls");
	printf("\nHow much do you want to Withdraw: ");
	gets(scannedAmount);
	
	if(scanIfDigits(scannedAmount) == TRUE){
		amount = atof(scannedAmount);
		amount = -amount; //negative

		//search slot in history
		for(int i = 0; i < PLIMIT; i++){
			if(aD[index].savingType.balance_history[i] == NULL){
				aD[index].savingType.balance_history[i] = amount;
				strcpy(aD[index].savingType.branch[i], currentBranch);
				strcpy(aD[index].savingType.date[i], __DATE__);
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

void MoneyTransfer(acctDet *aD, int index){
	char *inputT_ID, scannedAmount[CHARLIMIT];
	inputT_ID = (char*)calloc(sizeof(char), IDLIMIT);
	float transferAmt;
	int t_index;
	system("cls");
	printf("\nEnter the ACCOUNT ID of which you want to Transfer to: ");
	gets(inputT_ID);
	upperSentence(inputT_ID);
	printf("\nHow much amount do you want to Transfer: ");
	gets(scannedAmount);

	
	transferAmt = atof(scannedAmount);

	//search account
	t_index = getAcctIndex(aD, inputT_ID);
	if(t_index != NA){
		
			//search slot in history for user to transfer 
		if(aD[t_index].type == SAVINGS){
			//search slot in history for user
			for(int i = 0; i < PLIMIT; i++){
				if(aD[index].savingType.balance_history[i] == NULL){
					aD[index].savingType.balance_history[i] = (-transferAmt);
					strcpy(aD[index].savingType.branch[i], currentBranch);
					strcpy(aD[index].savingType.date[i], __DATE__);
					break;
				}
			}
			for(int i = 0; i < PLIMIT; i++){
				if(aD[t_index].savingType.balance_history[i] == NULL){
					aD[t_index].savingType.balance_history[i] = transferAmt;
					strcpy(aD[t_index].savingType.branch[i], currentBranch);
					strcpy(aD[t_index].savingType.date[i], __DATE__);
					break;
				}
			}
			printf("\nTransfer Successful!");
			printf("\n%.2f has been tranferred to %s", transferAmt, inputT_ID);
		}
		else if(aD[t_index].type == TIME){
			
			aD[t_index].totalBalance += transferAmt;

			printf("\nTransfer Successful!");
			printf("\n%.2f has been tranferred to %s", transferAmt, inputT_ID);
		//
		}
		else if(aD[t_index].type == TRUST){
		//
			printf("\nCannot Transfer to a Trust Account! Due to some regulations...");
		}
		
	}
	else{
		printf("\nAccount doesn't exist!! ");
	}
	
	getch();
	system("cls");
}