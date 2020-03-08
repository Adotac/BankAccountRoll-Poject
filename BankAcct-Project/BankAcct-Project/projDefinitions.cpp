#include "BA_header.h"
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

int IdChecker(char inpID[], acctDet *aD){
	
	for(int i = 0; i < PLIMIT; i++){
		if( strcmp(inpID, aD[i].acctID) == 0){
			return TRUE;
		}
	
	}
return FALSE; //if account doesnt exist
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


		printf("\n||Total: %15.2f", aD[accIndex].totalBalance);
	}

	
}

//Money options
void SavingMoneyOpts(acctDet *aD){



}

int accountTypeReg(){
	int i = 0;
	char key = LTARROW;

	while (key != ENTER) {
		system("cls");
		printf("\n\t==========	 Welcome!	==========");
		printf("\n\t|\tSelect the following types:\t |\n\t|");

		switch (i) {
		case 0: printf("\033[0;33m");
			printf("%s   ", "[TIME]");
			printf("\033[0m");
			printf("%s   ", "[SAVINGS]");
			printf("%s   ", "[TRUST]");
			printf("%s", "[CANCEL]");
			break;
		case 1:
			printf("%s   ", "[TIME]");
			printf("\033[0;33m");
			printf("%s   ", "[SAVINGS]");
			printf("\033[0m");
			printf("%s   ", "[TRUST]");
			printf("%s", "[CANCEL]");
			break;
		case 2:printf("%s   ", "[TIME]");
			printf("%s   ", "[SAVINGS]");
			printf("\033[0;33m");
			printf("%s   ", "[TRUST]");
			printf("\033[0m");
			printf("%s", "[CANCEL]");
			break;
		case 3:printf("%s   ", "[TIME]");
			printf("%s   ", "[SAVINGS]");
			printf("%s   ", "[TRUST]");
			printf("\033[0;33m");
			printf("%s", "[CANCEL]");
			printf("\033[0m");
			break;
		}
		printf(" |\n\t==========================================");

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