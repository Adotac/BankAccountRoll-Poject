#include "BA_header.h"


//UI Functions
void textHighllght(char s[]){
	
	printf("\033[0;33m");
	printf("%s   ", s);
	printf("\033[0m");
}
int optYesNo(){
	char key;
	int iCtr = 1;

	do{

		switch(iCtr){
		case 1:
			textHighllght("[YES]");
			printf("\t");
			printf("[NO]");
			
			break;
		case 2:
			printf("[YES]");
			printf("\t");
			textHighllght("[NO]");
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
			if(iCtr > 2)
				iCtr = 2;
			break;
		case ENTER:
			return iCtr;
			break;
		}
	
	printf("\r%s\r", "                 ");
	
	}while(key != ENTER);
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



void acctGenerator(acctDet *aD){
	int pin, regType;
	int glength = strlen(charGenerator);
	int gIndex = rand() % glength;

	regType = accountTypeReg(); // dont delete, important!

	char gTemp, *arrTemp;
	arrTemp = (char*)calloc(sizeof(char),IDLIMIT);
	
	//genrate ID
	for(int i = 0; i < IDLIMIT; i++){
		gIndex = rand() % glength;
		gTemp = charGenerator[gIndex];

		arrTemp[i] = gTemp;
		
	}

	//search vacant slot
	for(int x = 0; x < PLIMIT; x++){
		if( strcmp(aD[x].acctID, "\0") == 0 ){
			memcpy(aD[x].acctID, arrTemp, IDLIMIT);
			printf("\nYour ACCOUNT ID is: %6s", aD[x].acctID);
			pin = pinGenerator();
			aD[x].pin = pin;
			printf("\nYour ACCOUNT PIN is: %4d", aD[x].pin);
			printf("\nDo not forget it!");
			getch();
			getInfo(aD, x);
			switch(regType){
			case 0://time
				aD[x].type = TIME;
				break;
			case 1://saving
				aD[x].type = SAVINGS;
				break;
			case 2://trust
				aD[x].type = TRUST;
				break;
			}
			
			break;
		}
		else if(x == PLIMIT - 1){
			printf("\nServers are full, please comeback some another day to continue!\n");
			break;
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
	
	if( memcmp(inpId, aD[i].acctID, IDLIMIT) == 0 && i != NA ){
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
void deleteAccount(acctDet *aD, int index){
	
	strcpy(aD[index].acctID, "");
	//info
	strcpy(aD[index].inf.address, "");
	strcpy(aD[index].inf.city, "");
	//name
	strcpy(aD[index].inf.pname.First, "");
	strcpy(aD[index].inf.pname.Last, "");
	strcpy(aD[index].inf.pname.Middle, "");

	//savings
	aD[index].totalBalance = NULL;
	aD[index].pin = NULL;
	for(int i = 0; i < PLIMIT; i++){
		aD[index].savingType.balance_history[i] = NULL;
		strcpy(aD[index].savingType.branch[i], "");
		strcpy(aD[index].savingType.date[i], "");
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

int optTrust(){
	char key;
	int iCtr = 1;

	do{
		
		switch(iCtr){
		case 1:
			textHighllght("[ADD LEDGER]");
			printf("\t");
			printf("[DELETE LEDGER]");
			printf("\t");
			printf("[LINK ACCOUNT]");
			printf("\t");
			printf("[EXIT]");
			break;
		case 2:
			printf("[ADD LEDGER]");
			printf("\t");
			textHighllght("[DELETE LEDGER]");
			printf("\t");
			printf("[LINK ACCOUNT]");
			printf("\t");
			printf("[EXIT]");
			break;
		case 3:
			printf("[ADD LEDGER]");
			printf("\t");
			printf("[DELETE LEDGER]");
			printf("\t");
			textHighllght("[LINK ACCOUNT]");
			printf("\t");
			printf("[EXIT]");
			break;
		case 4:
			printf("[ADD LEDGER]");
			printf("\t");
			printf("[DELETE LEDGER]");
			printf("\t");
			printf("[LINK ACCOUNT]");
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
	
	printf("\r                                                                 \r");
	
	}while(key != ENTER);

}
void displayTrust(acctDet *aD, char inpuId[]){
	int index = getAcctIndex(aD, inpuId);
	int flag = TRUE;
	
	do{
		system("cls");
		printf("\n%s %s %s", aD[index].inf.pname.First, aD[index].inf.pname.Middle, aD[index].inf.pname.Last);
		printf("\n     ||DESCRIPTION\t\t||AMOUNT\t\t||DATE\t\t||");
		printf("\n------------ASSETS----------------\n");
		for(int x = 0; x < PLIMIT; x++){
			if(aD[index].trustType.assetAmtHistory[x] != NULL){
				printf("\n[%2d] %11s\t\t||%6.2f\t\t||%s",x+1, aD[index].trustType.assets[x], aD[index].trustType.assetAmtHistory[x], aD[index].trustType.assetHistDate[x]);
			
			}
		}
		printf("\nTotal Assets: %.2f", aD[index].trustType.assetAmount);

		printf("\n------------LIABILITIES----------------\n");
		for(int x = 0; x < PLIMIT; x++){
			if(aD[index].trustType.liabAmtHistory[x] != NULL){
				printf("\n[%2d] %11s\t\t||%6.2f\t\t||%s",x+1, aD[index].trustType.liabilities[x], aD[index].trustType.liabAmtHistory[x], aD[index].trustType.liabAmtHistory[x]);
				
			}
		}
		printf("\nTotal Assets: %.2f\n\n\n", aD[index].trustType.liabAmount);
		
		switch(optTrust()){
		case 1:
			AddLedger(aD, index);
			break;
		case 2:
			DeleteLedger(aD, index);
			break;
		case 3:
			LinkAccount(aD, index);
			break;
		case 4:
			flag = FALSE;
			break;
		}
	}while(flag == TRUE);
}

int optLedger(){
	char key;
	int iCtr = 1;

	do{
		
		switch(iCtr){
		case 1:
			textHighllght("[ASSETS]");
			printf("\t");
			printf("[LIABILITIES]");
			
			break;
		case 2:
			printf("[ASSETS]");
			printf("\t");
			textHighllght("[LIABILITIES]");
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
			if(iCtr > 2)
				iCtr = 2;
			break;
		case ENTER:
			return iCtr;
			break;
		}
	
	printf("\r%s\r", "                                   ");
	//printf("\r\t\t\t\t\t\t\t\t\t\t\t\t\r");
	}while(key != ENTER);
}
void AddLedger(acctDet *aD, int index){
	int loopChoice = TRUE;
	char scannedAmount[CHARLIMIT];
	printf("\n\n");
	printf("\nWhich Ledger type you want to add?\n");
	switch(optLedger()){
	case 1:
		for(int x = 0; x < PLIMIT && loopChoice == TRUE; x++){
		
		fflush(stdin);
		if(aD[index].trustType.assetAmtHistory[x] == NULL){
				printf("\nInput all your assets you want to entrust\n");
				printf("\nAsset[%d] Description: ", x+1);
				gets(aD[index].trustType.assets[x]);
				printf("\nAsset[%d] netAmount: ", x+1);
				gets(scannedAmount);
				
				strcpy(aD[index].trustType.assetHistDate[x], __DATE__);
				if(scanIfDigits(scannedAmount) == TRUE){
				aD[index].trustType.assetAmtHistory[x] = atof(scannedAmount);
				aD[index].trustType.assetAmount += aD[index].trustType.assetAmtHistory[x];
			
				}
				else{
				printf("\n\nError input, retry...");
					x--;
					break;
				}

			printf("\n\nContinue?\n");
			switch(optYesNo()){
				case 1:
				loopChoice = TRUE;
				break;
				case 2:
					loopChoice = FALSE;
					break;
				}
			}
		}////////
		break;
	case 2:
		for(int x = 0; x < PLIMIT && loopChoice == TRUE; x++){
		system("cls");
		if(aD[index].trustType.liabAmtHistory[x] == NULL){
			printf("\nInput all your liabilities\n");
			printf("\nLiability[%d] Description: ", x+1);
			gets(aD[index].trustType.liabilities[x]);
			printf("\nLiability[%d] netAmount: ", x+1);
			gets(scannedAmount);
		
			strcpy(aD[index].trustType.liabHistDate[x], __DATE__);
			if(scanIfDigits(scannedAmount) == TRUE){
				aD[index].trustType.liabAmtHistory[x] = atof(scannedAmount);
				aD[index].trustType.liabAmount += aD[index].trustType.liabAmtHistory[x];
			}
			else{
				printf("\n\nError input, retry...");
				x--;
				break;
			}
				
			printf("\n\nContinue?\n");
			switch(optYesNo()){
			case 1:
				loopChoice = TRUE;
				break;
			case 2:
				loopChoice = FALSE;
				break;
			}
		}
		}//////////////
		break;
	}
}
void DeleteLedger(acctDet *aD, int index){
	char searched[CHARLIMIT];
	printf("\n\n");
	switch(optLedger()){
	case 1://search asset
		printf("\nCopy the (DETAIL) you want to delete: ");
		gets(searched);
		upperSentence(searched);
		//find asset
		for(int x = 0; x < PLIMIT; x++){
			if(strcmp(aD[index].trustType.assets[x], searched) == 0){
				//re assign
				for(int i = x; i < PLIMIT; i++){
					strcpy(aD[index].trustType.assets[i], aD[index].trustType.assets[i+1]);
				}

				break;
			}
			else{
				printf("\nAsset doesn't exist!");
			}
		}
		break;
	case 2:
		printf("\nCopy the (DETAIL) you want to delete: ");
		gets(searched);
		upperSentence(searched);
		//find asset
		for(int x = 0; x < PLIMIT; x++){
			if(strcmp(aD[index].trustType.assets[x], searched) == 0){
				//re assign
				for(int i = x; i < PLIMIT; i++){
					if(aD[index].trustType.assets[i])
						break;

					strcpy(aD[index].trustType.assets[i], aD[index].trustType.assets[i+1]);
				}

				break;
			}
			else{
				printf("\nLiability doesn't exist!");
			}
		}
		break;
	
	}

}
void LinkAccount(acctDet *aD, int index){
	char inpID[CHARLIMIT];
	printf("\n\n");
	fflush(stdin);
	printf("\nInput the Account ID you want to link: ");
	gets(inpID);
	upperSentence(inpID);
	if(getAcctIndex(aD, inpID) != NA){
		strcpy(aD[index].trustType.linkedBankAcct, inpID);
		printf("\nAccount successfully linked!!");
	}
	else{
		printf("\nAccount doesn't exist and can't link.");
	}

	getch();
}

int optBenefits(){
	char key;
	int iCtr = 1;

	do{

		switch(iCtr){
		case 1:
			textHighllght("[SUCCESSOR]");
			printf("\t");
			printf("[SCHOLARSHIP]");
			printf("\t");
			printf("[RETIREMENT PLAN]");
			printf("\t");
			printf("[EXIT]");
			break;
		case 2:
			printf("[SUCCESSOR]");
			printf("\t");
			textHighllght("[SCHOLARSHIP]");
			printf("\t");
			printf("[RETIREMENT PLAN]");
			printf("\t");
			printf("[EXIT]");
			break;
		case 3:
			printf("[SUCCESSOR]");
			printf("\t");
			printf("[SCHOLARSHIP]");
			printf("\t");
			textHighllght("[RETIREMENT PLAN]");
			printf("\t");
			printf("[EXIT]");
			break;
		case 4:
			printf("[SUCCESSOR]");
			printf("\t");
			printf("[SCHOLARSHIP]");
			printf("\t");
			printf("[RETIREMENT PLAN]");
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
void createTrust(acctDet *aD, int index){
	int benChoice, loopChoice = TRUE;
	char scannedAmount[CHARLIMIT];
	aD[index].trustType.assetAmount = 0;
	aD[index].trustType.liabAmount = 0;
	

	printf("\nTo have a Trust Account, there are following steps needs to be fulfilled...");

	printf("\nPlease select which type of benefits");
	benChoice = optBenefits();


	switch(benChoice){
	case 1://Successor
		aD[index].trustType.benefitType = SUCCESSOR;
		
		break;
	case 2://scholarship
		aD[index].trustType.benefitType = SCHOLARSHIP;

		break;
	case 3://retirement plan
		aD[index].trustType.benefitType = RETIREMENT_PLAN;
		break;
	case 4:
		printf("\n\nCancel account creation.");
		deleteAccount(aD, index);
		return; //exit function
		break;
	}

	printf("\nInput First name of benificiary: ");
	gets(aD[index].trustType.beneficiaryInfo.pname.First);
	printf("\nInput Last name of Beneficiary ");
	gets(aD[index].trustType.beneficiaryInfo.pname.Last);
	printf("\nInput the Middle/Initial name of Beneficiary: ");
	gets(aD[index].trustType.beneficiaryInfo.pname.Middle);

	printf("\nInput the City address: ");
	gets(aD[index].trustType.beneficiaryInfo.city);
	printf("\nInput his/her current address: ");
	gets(aD[index].trustType.beneficiaryInfo.address);
	printf("\nInput his/her age: ");
	scanf(" %d", &aD[index].trustType.beneficiaryInfo.age);

	system("cls");
	fflush(stdout);

	//For assets
	for(int x = 0; x < PLIMIT && loopChoice == TRUE; x++){
		system("cls");
		printf("\nInput all your assets you want to entrust\n");
		printf("\nAsset[%d] Description: ", x+1);
		gets(aD[index].trustType.assets[x]);
		printf("\nAsset[%d] netAmount: ", x+1);
		gets(scannedAmount);
		
		strcpy(aD[index].trustType.assetHistDate[x], __DATE__);
		if(scanIfDigits(scannedAmount) == TRUE){
			aD[index].trustType.assetAmtHistory[x] = atof(scannedAmount);
			aD[index].trustType.assetAmount += aD[index].trustType.assetAmtHistory[x];
		
		}
		else{
			printf("\n\nError input, retry...");
			x--;
			break;
		}

		printf("\n\nContinue?\n");
		switch(optYesNo()){
		case 1:
			loopChoice = TRUE;
			break;
		case 2:
			loopChoice = FALSE;
			break;
		}
	}

	system("cls");
	printf("\nDo you have some Liabilities?\n");
	switch(optYesNo()){
	case 1:
		//Liabilities
		for(int x = 0; x < PLIMIT && loopChoice == TRUE; x++){
		system("cls");
		printf("\nInput all your liabilities\n");
		printf("\nLiability[%d] Description: ", x+1);
		gets(aD[index].trustType.liabilities[x]);
		printf("\nLiability[%d] netAmount: ", x+1);
		gets(scannedAmount);
	
		strcpy(aD[index].trustType.liabHistDate[x], __DATE__);
		if(scanIfDigits(scannedAmount) == TRUE){
			aD[index].trustType.liabAmtHistory[x] = atof(scannedAmount);
			aD[index].trustType.liabAmount += aD[index].trustType.liabAmtHistory[x];
		}
		else{
			printf("\n\nError input, retry...");
			x--;
			break;
		}

		printf("\n\nContinue?\n");
		switch(optYesNo()){
		case 1:
			loopChoice = TRUE;
			break;
		case 2:
			loopChoice = FALSE;
			break;
		}
	}//////////////
		break;
	case 2:
		//nothing
		break;
	}

	printf("\nTrust Account created completely!");

}

void getInfo(acctDet *aD, int index) {

	system("cls");
	printf("\n ===============   Please Input Information Below   ===============");
	fflush(stdin);
	printf("\n\n[First Name]: ");  
	gets(aD[index].inf.pname.First);
	upperSentence(aD[index].inf.pname.First);
	fflush(stdin);
	printf("[Last Name]: ");
	gets(aD[index].inf.pname.Last);
	upperSentence(aD[index].inf.pname.Last);
	fflush(stdin);
	printf("[Middle Name]: ");
	gets(aD[index].inf.pname.Middle);
	upperSentence(aD[index].inf.pname.Middle);
	
	
	fflush(stdin);
	printf("\n[Age]: ");
	scanf(" %d", &aD[index].inf.age);
	fflush(stdin);
	printf("\n[City]: ");
	gets(aD[index].inf.city);
	printf("\n[Address]: ");
	gets(aD[index].inf.address);

	
}

void checkMoney(float *principalMoney)
{
	system("cls");
	int choice;
	if (*principalMoney < DEPOSIT)
	{
		printf ("\nNotice:  \nYour current money is below the expected deposit.\n"
				"You can only withdraw once every month with an interest of 3%%.\n");
	}
	showMoney(principalMoney);
	printf ("\nMenu: \n"
			"1.Deposit Money\n"
			"2.Withraw Money\n"
			"3.Back\n"
			"Choice: ");
	scanf ("%d", &choice);
	switch (choice)
	{
	case 1: depositMoney(principalMoney);
			break;
	case 2: withrawMoney(principalMoney);
			break;
	case 3: break;
	default:
		break;
	}
}

void depositMoney(float *principalMoney)
{
	system("cls");
	float money;
	printf ("Depositing Section\n");
	showMoney(principalMoney);
	printf ("Amount of money to deposit: ");
	scanf ("%f", &money);
	*principalMoney = *principalMoney + money;
	printf ("Success!");
	getch();
	checkMoney(principalMoney);
}

void withrawMoney(float *principalMoney)
{
	system("cls");
	float money,total,interest, totalMoney;
	float withrawM;
	int days;
	printf ("Withraw Section\n");
	showMoney(principalMoney);
	printf ("Amount of money to withraw: ");
	scanf ("%f", &money);
	printf ("Number of days since deposit: ");
	scanf ("%d", &days);
	if (days >= 360)
	{
		printf ("You've already reached the expected date to withraw.\n"
				"You can now get the deposited money with an interest of 3 percent.\n");
		total = *principalMoney + (*principalMoney*INTEREST*TAX);
		*principalMoney = total;
		*principalMoney = *principalMoney - money; 
		printf ("Total money : %.2f \n", *principalMoney);
		printf ("Money withraw : %.2f \n", money);
	}
	else if (days < 360)
	{
		printf ("You've not reached the expected date to withraw.\n"
				"You are not allowed to withraw yet.\n");
	}
	getch();
	checkMoney(principalMoney);
}

void showMoney(float *principalMoney)
{
	printf ("Current Money : %.2f\n", *principalMoney);
}

void calculateTimeDeposit()
{
	system("cls");
	float money, total;
	printf ("Input amount of money: ");
	scanf ("%f", &money);
	total = money + (money*INTEREST*TAX);
	printf ("Money : %.2f\n", money);
	printf ("Interest : %f\n", INTEREST);
	printf ("Tax : %.2f\n", TAX);
	printf ("Total(1 year);: %.2f", total);
	getch();
}

void TimeDeposit(acctDet *aD, int index)
{
	float *principalMoney;
	principalMoney = &aD[index].totalBalance;
	float newTotalBalance;
	int choice, flag = TRUE;
	do{
	system ("cls");
	printf ("Welcome %s, \n", aD[index].acctID);
	printf("\n%s %s %s", aD[index].inf.pname.First, aD[index].inf.pname.Middle, aD[index].inf.pname.Last);
	printf ("\nTime Deposit\n"
			"1. Check money\n"
			"2. Calculate Time Deposit\n"
			"3. Back\n"
			"Choice: ");
	scanf ("%d", &choice);
	switch (choice)
	{
	case 1: checkMoney(principalMoney);
			break;
	case 2: calculateTimeDeposit();
			break;
	case 3: system ("cls");
			return;
	default:
		break;
	}
	newTotalBalance = *principalMoney;
	aD[index].totalBalance = newTotalBalance;
	system("cls");
	}while(flag == TRUE);
}
