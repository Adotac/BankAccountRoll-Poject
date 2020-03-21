#include "BA_header.h"


void readFiles(acctDet** aD, Time **tiD, Trust **trD, Savings **svD, FILE **trdb, FILE **svdb, FILE **tidb, FILE **acdb){
	rewind(*acdb);
	rewind(*svdb);
	rewind(*tidb);
	rewind(*trdb);
	fread(*aD, sizeof(struct AccountDetails), 1, *acdb);
	fread(*svD, sizeof(struct SavingsDetails), 1, *svdb);
	fread(*trD, sizeof(struct TrustDetails), 1, *trdb);
	fread(*tiD, sizeof(struct TimeDetails), 1, *trdb);
	fflush(*acdb);
	fflush(*svdb);
	fflush(*tidb);
	fflush(*trdb);
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

void dateExtractor(char format, char *date, void *output){
	char *token;
	int mLength = 0, day = 0;

	switch(toupper(format)){
	case 'M'://month
		token = strtok(date, " ");
		mLength = strlen(token);
		memcpy((char*)output, token, mLength);
		break;
	case 'D'://day
		token = strtok(date, " ");
		token = strtok(NULL, " ");
		*(int*)output = atoi(token);

		break;
	case 'Y'://year
		token = strtok(date, " ");
		token = strtok(NULL, " ");
		token = strtok(NULL, " ");

		*(int*)output = atoi(token);
		break;
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

int pinGenerator(){
	int pin = 0;
	//4 digit code||max		min			min
	pin = rand() % (9999 - 1000 + 1) + 1000;
	return pin;
}
void acctGenerator(acctDet* aD, Time *tiD, Trust *trD, Savings *svD, FILE *trdb, FILE *svdb, FILE *tidb, FILE *acdb){
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
	arrTemp[IDLIMIT] = CNULL;
	

	//search vacant slot
	if(regType == 3){
		return;
	}
	else{
		memcpy(aD->acctID, arrTemp, IDLIMIT);
		fflush(stdout);
		printf("\nYour ACCOUNT ID is: %6s", aD->acctID);
		pin = pinGenerator();
		aD->pin = pin;
		aD->deleted = FALSE;
		printf("\nYour ACCOUNT PIN is: %4d", aD->pin);
		printf("\nDo not forget it!");
		getch();
		getInfo(aD);
		switch(regType){
		case 0://time
			aD->type = TIME;
			memcpy(tiD->acctID , aD->acctID, IDLIMIT);
			strcpy(tiD->date, __DATE__);
			strcpy(tiD->date, currentBranch);

			if(createTime() == NA){
				printf("\nTerminating creation of account due to invalid input...");
				aD->deleted = TRUE;
				getch();
			}
			else{
				tiD->totalBalance += createTime();
			}

			
			fseek(tidb, 0, SEEK_END);
			fwrite(tiD, sizeof(struct TimeDetails), 1, tidb);
			break;
		case 1://saving
			aD->type = SAVINGS;
			memcpy(svD->acctID , aD->acctID, IDLIMIT);

			if(createSav() == NA){
				printf("\nTerminating creation of account due to invalid input...");
				aD->deleted = TRUE;
				getch();
			}
			else{
				svD->totalBalance += createSav();
			}

			fseek(svdb, 0, SEEK_END);
			fwrite(svD, sizeof(struct SavingsDetails), 1, svdb);
			
			break;
		case 2://trust
			aD->type = TRUST;
			memcpy(trD->acctID , aD->acctID, IDLIMIT);
			createTrust(aD->acctID, aD, trD);
			fseek(trdb, 0, SEEK_END);
			fwrite(trD, sizeof(struct TrustDetails), 1, trdb);
			break;
		}
	}

	fseek(acdb, 0, SEEK_END);
	fwrite(aD, sizeof(struct AccountDetails), 1, acdb);
}

void getInfo(acctDet* aD) {

	system("cls");
	printf("\n ===============   Please Input Information Below   ===============");
	fflush(stdin);
	printf("\n\n[First Name]: ");  
	gets(aD->First);
	upperSentence(aD->First);
	fflush(stdin);
	printf("[Last Name]: ");
	gets(aD->Last);
	upperSentence(aD->Last);
	fflush(stdin);
	printf("[Middle Name]: ");
	gets(aD->Middle);
	upperSentence(aD->Middle);
	fflush(stdin);
	printf("\n[Age]: ");
	scanf(" %d", &aD->age);
	fflush(stdin);
	printf("\n[City]: ");
	upperSentence(aD->city);
	gets(aD->city);
	upperSentence(aD->city);
	fflush(stdin);
	printf("\n[Address]: ");
	gets(aD->address);
	upperSentence(aD->address);

	
}


int IdChecker(char inputID[], acctDet* aD, FILE *acdb){

	rewind(acdb);
	while(fread(aD, sizeof(struct AccountDetails), 1, acdb) == 1){
		if(memcmp(inputID, aD->acctID, IDLIMIT) == 0 && aD->deleted == FALSE){
			return TRUE;
		}
	}
	
	
return FALSE; //if account doesnt exist
}

//sets all files to struct's Id
int FindIdFileSetter(char searchId[], const char *format, ...){
	FILE *ftemp = NULL;
	acctDet *actemp = NULL;
	Savings *svtemp = NULL;
	Trust *trtemp = NULL;
	Time *titemp = NULL;

	
	
	va_list args;
	int ctr = 0; int sflag = FALSE;

	va_start(args, format);
	while(format[ctr] != '\0'){
		if(format[ctr] == ',')//distinguish format
			ctr++;
	

		switch(format[ctr]){
		//FILE FORMAT
		case 'F':
			ftemp = va_arg(args, FILE*);
			fseek(ftemp, 0, SEEK_SET);
			break;
		//STRUCT FORMATS
		case 'A'://acct details
			actemp = va_arg(args, acctDet*);
			while(fread(actemp, sizeof(acctDet), 1, ftemp) == 1){
				if(strcmp(searchId, actemp->acctID) == 0 && actemp->deleted == FALSE){
					sflag = TRUE;
					break;
				}
				else
					sflag = FALSE;
			}
			break;
		case 'S'://savings
			svtemp = va_arg(args, SavingsDetails*);
			while(fread(svtemp, sizeof(SavingsDetails), 1, ftemp) == 1){
				if(strcmp(searchId, svtemp->acctID) == 0 && actemp->deleted == FALSE){
					sflag = TRUE;
					break;
				}
				else
					sflag = FALSE;
			}
			break;
		case 'I'://time
			titemp = va_arg(args, TimeDetails*);
			while(fread(titemp, sizeof(TimeDetails), 1, ftemp) == 1){
				if(strcmp(searchId, titemp->acctID) == 0 && actemp->deleted == FALSE){
					sflag = TRUE;
					break;
				}
				else
					sflag = FALSE;
			}
			break;
		case 'R'://trust
			trtemp = va_arg(args, TrustDetails*);
			while(fread(trtemp, sizeof(TrustDetails), 1, ftemp) == 1){
				if(strcmp(searchId, trtemp->acctID) == 0 && actemp->deleted == FALSE){
					sflag = TRUE;
					break;
				}
				else
					sflag = FALSE;
			}
			break;
		}

		ctr++;
	}
	va_end(args);

	return sflag;
}
void UpdateFiles(char accID[], const char *format, ...){
	FILE *ftemp = NULL;
	acctDet *actemp = NULL;
	Savings *svtemp = NULL;
	Trust *trtemp = NULL;
	Time *titemp = NULL;
	
	
	va_list args;
	int ctr = 0; int sflag = FALSE, f_cursor;

	va_start(args, format);
	while(format[ctr] != '\0'){
		if(format[ctr] == ',')//distinguish format
			ctr++;
	

		switch(format[ctr]){
		//FILE FORMAT
		case 'F':
			ftemp = va_arg(args, FILE*);
			fseek(ftemp, 0, SEEK_SET);
			break;
		//STRUCT FORMATS
		case 'A'://acct details
			actemp = va_arg(args, acctDet*);

			f_cursor = cursorFileSeeker(accID, ftemp, 'A', actemp);
			
			fseek(ftemp, f_cursor-(sizeof(acctDet)), SEEK_SET);

			fwrite(actemp, sizeof(acctDet), 1, ftemp);
			break;
		case 'S'://savings
			svtemp = va_arg(args, Savings*);

			f_cursor = cursorFileSeeker(accID, ftemp, 'S', svtemp);
			
			fseek(ftemp, f_cursor-(sizeof(Savings)), SEEK_SET);
		
 			fwrite(svtemp, sizeof(Savings), 1, ftemp);
			break;
		case 'I'://time
			titemp = va_arg(args, Time*);

			f_cursor = cursorFileSeeker(accID, ftemp, 'I', titemp);
		
			fseek(ftemp, f_cursor-(sizeof(Time)), SEEK_SET);

			fwrite(titemp, sizeof(Time), 1, ftemp);
			break;
		case 'R'://trust
			trtemp = va_arg(args, Trust*);

			f_cursor = cursorFileSeeker(accID, ftemp, 'R', trtemp);
		
			fseek(ftemp, f_cursor-(sizeof(Trust)), SEEK_SET);

			fwrite(trtemp, sizeof(Trust), 1, ftemp);
			break;
		}

		ctr++;
	}
	va_end(args);
}
long int cursorFileSeeker(char arr[], FILE *fptr, const char format, ...){
	acctDet actemp;
	Savings svtemp;
	Trust trtemp;
	Time titemp;
	
	va_list args;
	int sflag = FALSE;
	long int length = 0;
	va_start(args, format);
	if(format != '\0'){
		switch(format){
		//STRUCT FORMATS
		case 'A'://acct details
			memcpy(&actemp, va_arg(args, acctDet*), sizeof(acctDet));
			
			while(fread(&actemp, sizeof(acctDet), 1, fptr) == 1){
				if(strcmp(arr, actemp.acctID) == 0 ){
					length = ftell(fptr);
					break;
				}			
			}
			break;
		case 'S'://savings
			memcpy(&svtemp, va_arg(args, Savings*), sizeof(Savings));
			while(fread(&svtemp, sizeof(Savings), 1, fptr) == 1){
				if(strcmp(arr, svtemp.acctID) == 0 ){
					length = ftell(fptr);
					break;
				}			
			}
			break;
		case 'I'://time
			memcpy(&titemp, va_arg(args, Time*), sizeof(Time));
			while(fread(&titemp, sizeof(Time), 1, fptr) == 1){
				if(strcmp(arr, titemp.acctID) == 0 ){
					length = ftell(fptr);
					break;
				}			
			}
			break;
		case 'R'://trust
			memcpy(&trtemp, va_arg(args, Trust*), sizeof(Trust));
			while(fread(&trtemp, sizeof(Trust), 1, fptr) == 1){
				if(strcmp(arr, trtemp.acctID) == 0 ){
					length = ftell(fptr);
					break;
				}			
			}
			break;
		}
	}
	else{
		length = NA;
	}

	va_end(args);
	
	return length;
}

int pinChecker(char inputId[], int inPin, acctDet* aD, FILE *acdb){
	rewind(acdb);
	while(fread(aD, sizeof(struct AccountDetails), 1, acdb) == 1){
		if(strcmp(inputId, aD->acctID) == 0){
			if(inPin == aD->pin)
				return TRUE;
		}
	}
	

	return FALSE;
}


void deleteAccount(char userId[], acctDet* aD, FILE *acdb){
	char *inputId = (char*)malloc(IDLIMIT*sizeof(char));
	inputId[IDLIMIT] = CNULL;
	system("cls");

	if(strcmp(userId, SNULL) == 0){
		//admin function

		printf("\n\nInput the Account ID you want to delete: ");
		fflush(stdin);
		scanf(" %s", inputId);
		upperSentence(inputId);

		if(IdChecker(inputId, aD, acdb) != TRUE){
			printf("\nAccount doesnt exist!");
			getch();
			return;
		}
		else{
			FindIdFileSetter(inputId, "FA", acdb, aD);
			aD->deleted = TRUE;
			UpdateFiles(inputId, "FA", acdb, aD);
		}

	}
	else{
		if(IdChecker(userId, aD, acdb) != TRUE){
			printf("\n\n\nAccount doesn't exist!");
			getch();
			return;
		}
		else{
			FindIdFileSetter(userId, "FA", acdb, aD);
			aD->deleted = TRUE;
			UpdateFiles(userId, "FA", acdb, aD);
		}
	}

	printf("\n\nAccount deleted successfully!");
	getch();
}


//admin functions
void adminPanel(acctDet* aD, Savings *svD, Time *tiD, Trust *trD, FILE *acdb, FILE *svdb, FILE *tidb, FILE *trdb){
	
	do{
		system("cls");
		
		switch(optAdmin()){
		case 1:
			displayAllAcct(aD, &acdb);

			break;
		case 2:
			displaySavAccts(svD, &svdb, aD, &acdb);
			break;
		case 3:
			displayTimeAccts(tiD, &tidb, aD, &acdb);
			break;
		case 4:
			displayTrustAccts(trD, &trdb, aD, &acdb);
			break;
		case 5:
			deleteAccount(SNULL, aD, acdb);
			break;
		case 6:
			searchAcct(aD,svD, tiD, trD, acdb, svdb, tidb, trdb);
			break;
		case 7:
			return;
			break;
		}
		
	}while(TRUE);
}

void searchAcct(acctDet* aD, Savings *svD, Time *tiD, Trust *trD, FILE *acdb, FILE *svdb, FILE *tidb, FILE *trdb){
	char *input = (char*)calloc(CHARLIMIT*CHARLIMIT, sizeof(char));
	char *temp = (char*)calloc(CHARLIMIT*CHARLIMIT, sizeof(char));
	char *token;
	int flag = FALSE;

	
		system("cls");
		printf("\nInput Account Id: ");
		scanf(" %s", input);
		rewind(acdb);
		if(IdChecker(input, aD, acdb) == TRUE && FindIdFileSetter(input, "FA", aD, acdb) == TRUE && aD->deleted == FALSE){
			searchDisplay(aD, svD, tiD, trD);	
		}
		else{
			printf("\nAccount doesn't exist!!");
			
		}
		

	getch();
}
void searchDisplay(acctDet *aD, Savings *svD, Time *tiD, Trust *trD){
	system("cls");
	switch(aD->type){
			case SAVINGS:
				printf("\n%s %s %s", aD->First, aD->Middle, aD->Last);
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
				break;
			case TRUST:
				
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
		
				trD->totalBalance = trD->assetAmount - trD->liabAmount;
				printf("\n\nTotal NetAmount\n\n\n: %.2f", trD->totalBalance);
				break;
			case TIME:
				printf("\n%s %s %s", aD->First, aD->Middle, aD->Last);

				printf("\nCurrent Balance: %.2f", tiD->totalBalance);
				printf("\nInterest Amount: %.2f", tiD->interestBalance);
				printf("\nDate account created: %s", tiD->date);
				break;
			}
}

void displayAllAcct(acctDet* aD, FILE **acdb){
	int ctr = 1;
	system("cls");
	
	printf("ACCOUNTS:");
	printf("\n       %-7s||%-7s||%-7s||%-15s||%-15s||%-15s||%-15s||%-15s||%-15s\n", "ACC_ID", "PIN", "TYPE", "LAST", "FIRST", "MIDDLE", "AGE", "CITY", "ADDRESS");
	fflush(stdin);


	fseek(*acdb, 0, SEEK_SET);
	while(fread(aD, sizeof(struct AccountDetails), 1, *acdb) == 1){
		fflush(stdin);
		if(aD->type == SAVINGS && aD->deleted == FALSE){
		printf("\n[%3d]: %-7s||%-7d||%-7s||%-15s||%-15s||%-15s||%-15d||%-15s||%-15s", ctr, aD->acctID, aD->pin, typeIdentifier(aD->type), aD->Last, aD->First, aD->Middle, aD->age, aD->city, aD->address);
		ctr++;
		}
	}
	printf("\n");
	fseek(*acdb, 0, SEEK_SET);
	while(fread(aD, sizeof(struct AccountDetails), 1, *acdb) == 1){
		fflush(stdin);
		if(aD->type == TRUST && aD->deleted == FALSE){
		printf("\n[%3d]: %-7s||%-7d||%-7s||%-15s||%-15s||%-15s||%-15d||%-15s||%-15s", ctr, aD->acctID, aD->pin, typeIdentifier(aD->type), aD->Last, aD->First, aD->Middle, aD->age, aD->city, aD->address);
		ctr++;
		}
	}
	printf("\n");
	fseek(*acdb, 0, SEEK_SET);
	while(fread(aD, sizeof(struct AccountDetails), 1, *acdb) == 1){
		fflush(stdin);
		if(aD->type == TIME && aD->deleted == FALSE){
		printf("\n[%3d]: %-7s||%-7d||%-7s||%-15s||%-15s||%-15s||%-15d||%-15s||%-15s", ctr, aD->acctID, aD->pin, typeIdentifier(aD->type), aD->Last, aD->First, aD->Middle, aD->age, aD->city, aD->address);
		ctr++;
		}
	}
	getch();
}

void displaySavAccts(Savings *svD, FILE **svdb, acctDet* aD, FILE **acdb){
	int ctr = 1;
	system("cls");
	fseek(*svdb, 0, SEEK_SET);
	
	while(fread(svD, sizeof(struct SavingsDetails), 1, *svdb) == 1 ){

		if(strcmp(svD->acctID, SNULL) != 0 && FindIdFileSetter(svD->acctID, "FA", *acdb, aD) == TRUE && aD->deleted == FALSE){
			fflush(stdin);
			printf("\n\n========================================================");
			printf("\nACCT_ID: %-15s   Current Balance: %-15.2f", svD->acctID, svD->totalBalance);
			printf("\nLatest Transactions:");
			printf("\n||DEPOSITED AMOUNT\t||BRANCH\t||DATE\n");
			for(int i = PLIMIT - 1, mxctr = 0; i >= 0 && mxctr < 5; i--){
				if(svD->balance_history[i] != NULL){
					printf("\n||%15.2f\t||%10s\t||%5s", svD->balance_history[i], svD->branch[i], svD->date[i]);
					mxctr++;
				}
			}
			ctr++;
		}
	}
	printf("\n========================================================");
getch();
}

void displayTimeAccts(Time *tiD, FILE **tidb, acctDet* aD, FILE **acdb){

	int ctr = 1;
	system("cls");
	fseek(*tidb, 0, SEEK_SET);
	printf("\n       %-15s||%-15s||%-15s||%-15s||%-15s", "ACCT_ID", "BALANCE", "INTEREST_BAL", "BRANCH", "DATE");
	while(fread(tiD, sizeof(struct TimeDetails), 1, *tidb) == 1 ){
		if(strcmp(tiD->acctID, SNULL) != 0 && FindIdFileSetter(tiD->acctID, "FA", *acdb, aD) == TRUE && aD->deleted == FALSE){
			fflush(stdin);
			
			printf("\n[%3d]: %-15s||%-15.2f||%-15.2f||%-15s||%-15s", ctr, tiD->acctID, tiD->totalBalance, tiD->interestBalance, tiD->branch, tiD->date);

			ctr++;
		}
	}
	getch();
}

void displayTrustAccts(Trust *trD, FILE **trdb, acctDet *aD, FILE** acdb){

	int ctr = 1;
	system("cls");
	fseek(*trdb, 0, SEEK_SET);
	printf("\n       %-15s||%-15s||%-15s||%-15s||%-15s", "ACCT_ID", "TYPE", "NETWORTH", "ASSETS", "LIABILITIES");
	while(fread(trD, sizeof(struct TrustDetails), 1, *trdb) == 1){
		if(strcmp(trD->acctID, SNULL) != 0 && FindIdFileSetter(trD->acctID, "FA", *acdb, aD) == TRUE && aD->deleted == FALSE){
			fflush(stdin);
			
			printf("\n[%3d]: %-15s||%-15s||%-15.2f||%-15.2f||%-15s||", ctr, trD->acctID, trustIdentifier(trD->benefitType), trD->totalBalance, trD->assetAmount, trD->liabAmount);

			ctr++;
		}
	}
	getch();
}


