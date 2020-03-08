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
///
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
		if(strcmp(inpId, aD[i].acctID) == 0){
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
			SavingsAcctHistory(aD, index);
			opt = SavingMoneyOpts();
			switch(opt){
			case 1://Deposit

				sFlag = FALSE;
				break;
			case 2://Withdraw

				sFlag = FALSE;
				break;
			case NULL:
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
			printf("[EXIT]");
			break;
		case 2:
			printf("[DEPOSIT]");
			printf("\t");
			textHighllght("[WITHDRAW]");
			printf("\t");
			printf("[EXIT]");
			break;
		case 3:
			printf("[DEPOSIT]");
			printf("\t");
			printf("[WITHDRAW]");
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
			if(iCtr > 3)
				iCtr = 3;
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


		printf("\n||Total: %15.2f\n\n", aD[accIndex].totalBalance);
	}

	
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