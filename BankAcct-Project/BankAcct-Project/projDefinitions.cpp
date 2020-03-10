#include "BA_header.h"


//UI Functions
void textHighllght(char s[]){
	
	printf("\033[0;33m");
	printf("%s   ", s);
	printf("\033[0m");
}

//FUNCTION for strings
void upperSentence(char S_arr[]){
	int length = strlen(S_arr);

	for(int i = 0; i < length; i++){
		if(S_arr[i] == ' ' || S_arr[i] == '\0')
			continue;

		S_arr[i] = toupper(S_arr[i]);
	}

}
void lowerSentence(char S_arr[]){
	int length = strlen(S_arr);

	for(int i = 0; i < length; i++){
		if(S_arr[i] == ' ' || S_arr[i] == '\0')
			continue;

		S_arr[i] = tolower(S_arr[i]);
	}

}

int scanIfDigits(char S_arr[]){
	int slength = strlen(S_arr);
	int ctr = 0;
	for(int i = 0; i < slength; i++){
		if(isdigit(S_arr[i]) != 0){
			ctr++;
		}
	}

	if(ctr == slength)
		return TRUE;
	else
		return FALSE;
}



void acctIdGenerator(acctDet *aD){
	int glength = strlen(charGenerator);
	int gIndex = rand() % glength;

	char gTemp, arrTemp[IDLIMIT];
	//genrate ID
	for(int i = 0; i < IDLIMIT; i++){
		gIndex = rand() % glength;
		gTemp = charGenerator[gIndex];

		arrTemp[i] = gTemp;
		
	}

	//search vacant slot
	for(int x = 0; x < PLIMIT; x++){
		if( aD[x].acctID[0] == '\0' ){
			strcpy(aD[x].acctID, arrTemp);
			printf("\nYour ACCOUNT ID is: %s", aD[x].acctID);
			printf("\nDo not forget it!");
			break;
		}
		else{
			printf("\nServers are full, please comeback some another day to continue!\n");
		
		}
	}

	

}
int pinGenerator(){
	int pin = 0;
	//4 digit code||max		min			min
	pin = rand() % (9999 - 1000 + 1) + 1000;
	return pin;
}

int getAcctIndex(acctDet *aD, char inpId[]){
	for(int i = 0; i < PLIMIT; i++){
		if(strcmp(inpId, aD[i].acctID) == 0 && strcmp(inpId,"\n") != 0){
			return i;
		}
	}
	//if nothing
	return NA;
}
int IdChecker(char inpId[], acctDet *aD){
	int i = getAcctIndex(aD, inpId);
	
	if( strcmp(inpId, aD[i].acctID) == 0 && i != NA ){
		return TRUE;
	}
	
	
return FALSE; //if account doesnt exist
}

int pinChecker(char inpId[], int inPin, acctDet *aD){
	int i = getAcctIndex(aD, inpId);
	
	if(strcmp(inpId, aD[i].acctID) == 0 && i != NA ){
		if(aD[i].pin == inPin){
			return TRUE;
		}
	}
	

	return FALSE;
}

//display savings account
void displaySavings(acctDet *aD, char inpId[]){
	int index = getAcctIndex(aD, inpId);
	int opt = NULL, sFlag = TRUE;


	if(index != NA){
		do{
			flushall();
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
		if(aD[accIndex].balance_history[i] != NULL){
			printf("\n||%15.2f\t||%10s\t||%5s", aD[accIndex].balance_history[i], aD[accIndex].branch[i], aD[accIndex].date[i]);
			aD[accIndex].totalBalance += aD[accIndex].balance_history[i];
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
			if(aD[index].balance_history[i] == NULL){
				aD[index].balance_history[i] = amount;
				strcpy(aD[index].branch[i], currentBranch);
				strcpy(aD[index].date[i], __DATE__);
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
			if(aD[index].balance_history[i] == NULL){
				aD[index].balance_history[i] = amount;
				strcpy(aD[index].branch[i], currentBranch);
				strcpy(aD[index].date[i], __DATE__);
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
	char inputT_ID[IDLIMIT], scannedAmount[CHARLIMIT];
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
		//search slot in history for user
		for(int i = 0; i < PLIMIT; i++){
			if(aD[index].balance_history[i] == NULL){
				aD[index].balance_history[i] = (-transferAmt);
				strcpy(aD[index].branch[i], currentBranch);
				strcpy(aD[index].date[i], __DATE__);
				break;
			}
		}
			//search slot in history for user to transfer 
		if(aD[t_index].type == SAVINGS){
			for(int i = 0; i < PLIMIT; i++){
				if(aD[t_index].balance_history[i] == NULL){
					aD[t_index].balance_history[i] = transferAmt;
					strcpy(aD[t_index].branch[i], currentBranch);
					strcpy(aD[t_index].date[i], __DATE__);
					break;
				}
			}
		}
		else if(aD[t_index].type == TIME){
		
		//
		}
		else if(aD[t_index].type == TRUST){
		//
		}
		printf("\nTransfer Successful!");
		printf("\n%.2f has been tranferred to %s", transferAmt, inputT_ID);
	}
	else{
		printf("\nAccount doesn't exist!! ");
	}
	
	getch();
	system("cls");
}

int accountTypeReg(){
	int i = 0;
	char key = LTARROW;

	while (key != ENTER) {
		system("cls");
		printf("\n\t===============	 Welcome!	================");
		printf("\n\t|\t   Select the following types:		|\n\t|");

		switch (i) {
		case 0: 
			textHighllght("    [TIME]");
			printf("%s   ", "[SAVINGS]");
			printf("%s   ", "[TRUST]");
			printf("%s", "[CANCEL]");
			break;
		case 1:
			printf("    %s   ", "[TIME]");
			textHighllght("[SAVINGS]");
			printf("%s   ", "[TRUST]");
			printf("%s", "[CANCEL]");
			break;
		case 2:
			printf("    %s   ", "[TIME]");
			printf("%s   ", "[SAVINGS]");
			textHighllght("[TRUST]");
			printf("%s", "[CANCEL]");
			break;
		case 3:
			printf("    %s   ", "[TIME]");
			printf("%s   ", "[SAVINGS]");
			printf("%s   ", "[TRUST]");
			textHighllght("[CANCEL]");
			break;
		}
		printf("\t|\n\t================================================");

		key = getch();
		switch (key) {
		case LTARROW:
			i--;
			if (i < 0)
				i = 0;
			break;
		case RTARROW:
			i++;
			if (i == 4)
				i = 3;
			break;
		case ENTER:
			break;
		}
	}
	return i;
}