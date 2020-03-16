#include "BA_header.h"


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