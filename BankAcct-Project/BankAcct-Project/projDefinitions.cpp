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
		if(regType == 3){
			break;
		}
		else if( strcmp(aD[x].acctID, "\0") == 0 ){
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
	
	if(i != NA && memcmp(inpId, aD[i].acctID, IDLIMIT) == 0){
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

//admin functions
void adminPanel(acctDet *aD){
	system("cls");

	
	
	switch(optAdmin()){
	case 1:
		break;
	case 2:
		break;
	case 3:
		break;
	case 4:
		break;
	case 5:
		break;
	case 6:
		break;
	}

}

void displayAllAcct(){


}
