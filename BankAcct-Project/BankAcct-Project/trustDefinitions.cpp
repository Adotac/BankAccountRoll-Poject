#include "BA_header.h"


void displayTrust(char inpuId[], acctDet *aD, Trust* trD, Savings *svD, Time *tiD, FILE *acdb, FILE *trdb, FILE *svdb, FILE *tidb){
	int flag = TRUE;
	
	if(FindIdFileSetter(inpuId, "FA, FR", acdb, aD, trdb, trD) != TRUE){
		printf("\n\n\nError! Corrupted Account");
		getch();
		return;
	}

	do{
		system("cls");
		printf("\n%s %s %s", aD->First, aD->Middle, aD->Last);
		
		printf("\n\n------------ASSETS----------------\n");
		printf("\n     ||DESCRIPTION\t\t||AMOUNT\t\t||DATE\t\t||");
		for(int x = 0; x < PLIMIT; x++){
			if(trD->assetAmtHistory[x] != NULL){
				printf("\n[%2d] %11s\t\t||%6.2f\t\t||%s",x+1, trD->assets[x], trD->assetAmtHistory[x], trD->assetHistDate[x]);
			
			}
		}
		printf("\nTotal Assets: %.2f", trD->assetAmount);

		printf("\n\n\n----------LIABILITIES----------------\n");
		printf("\n     ||DESCRIPTION\t\t||AMOUNT\t\t||DATE\t\t||");
		for(int x = 0; x < PLIMIT; x++){
			if(trD->liabAmtHistory[x] != NULL){
				printf("\n[%2d] %11s\t\t||%6.2f\t\t||%s",x+1, trD->liabilities[x], trD->liabAmtHistory[x], trD->liabAmtHistory[x]);
				
			}
		}
		printf("\nTotal Liabilities: %.2f", trD->liabAmount);
		
		
		if(strcmp(trD->linkedBankAcct, SNULL) != 0){
			if(FindIdFileSetter(trD->linkedBankAcct, "FA", acdb, aD) == TRUE)
				printf("\nLinked Account: %s [%s]", trD->linkedBankAcct, typeIdentifier(trD->linkedtype));
			
			switch(trD->linkedtype){
			case SAVINGS:
				if(FindIdFileSetter(trD->linkedBankAcct, "FS", svdb, svD) == TRUE){
					trD->totalBalance += svD->totalBalance;
				}
				break;
			case TIME:
				if(FindIdFileSetter(trD->linkedBankAcct, "FI", tidb, tiD) == TRUE){
					trD->totalBalance += tiD->totalBalance;
				}
				break;
			}
		}
		else{
			printf("\nLinked Account: NONE");
		}
		
		trD->totalBalance = trD->assetAmount - trD->liabAmount;
		printf("\n\nTotal NetAmount: %.2f\n\n\n", trD->totalBalance);
		switch(optTrust()){
		case 1:
			AddLedger(&trD, inpuId);
			break;
		case 2:
			DeleteLedger(&trD, inpuId);
			break;
		case 3:
			LinkAccount(&trD, aD, acdb);
			break;
		case 4:
			flag = FALSE;
			break;
		}
	}while(flag == TRUE);
}


void AddLedger(Trust** trD, char userId[]){
	int loopChoice = TRUE;
	char scannedAmount[CHARLIMIT];
	printf("\n\n");
	printf("\nWhich Ledger type you want to add?\n");
	switch(optLedger()){
	case 1:
		for(int x = 0; x < PLIMIT && loopChoice == TRUE; x++){
		
		fflush(stdin);
		if((*trD)->assetAmtHistory[x] == NULL){
				printf("\nInput all your assets you want to entrust\n");
				printf("\nAsset[%d] Description: ", x+1);
				gets((*trD)->assets[x]);
				printf("\nAsset[%d] netAmount: ", x+1);
				gets(scannedAmount);
				
				strcpy((*trD)->assetHistDate[x], __DATE__);
				if(scanIfDigits(scannedAmount) == TRUE){
				(*trD)->assetAmtHistory[x] = atof(scannedAmount);
				(*trD)->assetAmount += (*trD)->assetAmtHistory[x];
			
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
		if((*trD)->liabAmtHistory[x] == NULL){
			printf("\nInput all your liabilities\n");
			printf("\nLiability[%d] Description: ", x+1);
			gets((*trD)->liabilities[x]);
			printf("\nLiability[%d] netAmount: ", x+1);
			gets(scannedAmount);
		
			strcpy((*trD)->liabHistDate[x], __DATE__);
			if(scanIfDigits(scannedAmount) == TRUE){
				(*trD)->liabAmtHistory[x] = atof(scannedAmount);
				(*trD)->liabAmount += (*trD)->liabAmtHistory[x];
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
void DeleteLedger(Trust**trD, char userId[]){
	char searched[CHARLIMIT];
	printf("\n\n");
	switch(optLedger()){
	case 1://search asset
		printf("\nCopy the (DETAIL) you want to delete: ");
		gets(searched);
		upperSentence(searched);
		//find asset
		for(int x = 0; x < PLIMIT; x++){
			if(strcmp((*trD)->assets[x], searched) == 0){
				//re assign
				for(int i = x; i < PLIMIT; i++){
					strcpy((*trD)->assets[i], (*trD)->assets[i+1]);
					strcpy((*trD)->assetHistDate[i], (*trD)->assetHistDate[i+1]);
					(*trD)->assetAmtHistory[i] = (*trD)->assetAmtHistory[i+1];
					
				}

				break;
			}
			else if(x == PLIMIT - 1){
				printf("\nAsset doesn't exist!");
			}
		}
		break;
	case 2:
		printf("\nCopy the (DETAIL) you want to delete: ");
		gets(searched);
		upperSentence(searched);
		//find liability
		for(int x = 0; x < PLIMIT; x++){
			if(strcmp((*trD)->liabilities[x], searched) == 0){
				//re assign
				for(int i = x; i < PLIMIT; i++){
					strcpy((*trD)->liabilities[i], (*trD)->liabilities[i+1]);
					strcpy((*trD)->liabHistDate[i], (*trD)->liabHistDate[i+1]);
					(*trD)->liabAmtHistory[i] = (*trD)->liabAmtHistory[i+1];
				}

				break;
			}
			else if(x == PLIMIT - 1){
				printf("\Liability doesn't exist!");
			}
		}
		break;
	
	}

}
void LinkAccount(Trust** trD, acctDet *aD, FILE *acdb){
	char inpID[CHARLIMIT];
	printf("\n\n");
	fflush(stdin);
	printf("\nInput the Account ID you want to link: ");
	scanf(" %s", inpID);
	upperSentence(inpID);

	if(IdChecker(inpID, aD, acdb) == TRUE && aD->deleted == FALSE){
		if(aD->type != TRUST){
			memcpy((*trD)->linkedBankAcct, inpID, IDLIMIT);
			(*trD)->linkedtype = aD->type;
		}
		else{
			printf("\nLinked account shoudn't be a Trust Account");
		}
	}
	else{
		printf("\n\nAccount doesn't exist!");
	}
	

	getch();
}


void createTrust(char userId[], acctDet *aD, Trust* trD){
	int benChoice, loopChoice = TRUE;
	char scannedAmount[CHARLIMIT];
	trD->assetAmount = 0;
	trD->liabAmount = 0;
	

	printf("\n\nTo have a Trust Account, there are following steps needs to be fulfilled...");

	printf("\nPlease select which type of benefits\n");
	benChoice = optBenefits();


	switch(benChoice){
	case 1://Successor
		trD->benefitType = SUCCESSOR;
		
		break;
	case 2://scholarship
		trD->benefitType = CHARITY;

		break;
	case 3://retirement plan
		trD->benefitType = RETIREMENT;
		break;
	case 4:
		printf("\n\nCancel account creation.");
		aD->deleted = TRUE;
		getch();
		return; //exit function
		break;
	}


	system("cls");
	fflush(stdout);

	//For assets
	for(int x = 0; x < PLIMIT && loopChoice == TRUE; x++){
		system("cls");
		printf("\nInput all your assets you want to entrust\n");
		printf("\nAsset[%d] Description: ", x+1);
		gets(trD->assets[x]);
		printf("\nAsset[%d] netAmount: ", x+1);
		gets(scannedAmount);
		
		
		if(scanIfDigits(scannedAmount) == TRUE){
			trD->assetAmtHistory[x] = atof(scannedAmount);
			trD->assetAmount += trD->assetAmtHistory[x];
			strcpy(trD->assetHistDate[x], __DATE__);
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
	loopChoice = TRUE;
	switch(optYesNo()){
	case 1:
		//Liabilities
		for(int x = 0; x < PLIMIT && loopChoice == TRUE; x++){
		system("cls");
		printf("\nInput all your liabilities\n");
		printf("\nLiability[%d] Description: ", x+1);
		gets(trD->liabilities[x]);
		printf("\nLiability[%d] netAmount: ", x+1);
		gets(scannedAmount);
	
		
		if(scanIfDigits(scannedAmount) == TRUE){
			trD->liabAmtHistory[x] = atof(scannedAmount);
			trD->liabAmount += trD->liabAmtHistory[x];
			strcpy(trD->liabHistDate[x], __DATE__);
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
	}

	printf("\nTrust Account created completely!");

}