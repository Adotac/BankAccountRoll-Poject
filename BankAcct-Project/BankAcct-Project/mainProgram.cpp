#include "BA_header.h"


int main(void){
	srand(time(NULL));
	FILE *acdb;

	acctDet account;
	//account = (acctDet*)calloc(sizeof(acctDet),PLIMIT);
	//*account = InitializeAcct();

	int loginFlag = TRUE, a_index = NULL;
	long int pinInput = NULL;
	
	char *inputId;
	inputId = (char*)calloc(sizeof(char), CHARLIMIT);
	
	if( (acdb = fopen("acdb.dat", "rb+") ) == NULL)
		exit(NULL);	
	else{
		fread(&account, sizeof(acctDet), PLIMIT, acdb);
	//	fclose(acdb);
	//	acdb = fopen("acdb.dat", "rb+");
	}

	
	do {//main loop
		fflush(stdin);
		system("cls");
		
		printf("\n\tNo account yet? Type REGISTER to create an account.");
		printf("\n\n\tAccount ID: ");
		gets(inputId);
		upperSentence(inputId);

		if( strcmp(inputId, "REGISTER") == 0){	
			acctGenerator(account);	
			//dire ang flow sa 1-4
			fwrite(account, sizeof(acctDet), PLIMIT, acdb);
		}
		else if(strcmp(inputId, "ADMINBK") == 0){
			fflush(stdin);
			printf("\n\tPIN: ");
			scanf(" %d", &pinInput);
			if(pinInput == atoi(ADMPASS)){
				//admin funtions
				adminPanel(account);
			}
			

		}
		else if(IdChecker(inputId, account) == TRUE){
			fflush(stdin);
			printf("\n\tPIN: ");
			scanf(" %d", &pinInput);
			//ari na ang pin input
			if(pinChecker(inputId, pinInput, account) == TRUE){
				//ari na sulod tanan after login
				a_index = getAcctIndex(account, inputId);
				switch(account[a_index].type){
				case TIME:
					TimeDeposit(account, a_index);
					break;
				case SAVINGS:
					displaySavings(account, inputId);
					break;
				case TRUST:
					displayTrust(account, inputId);
					break;
				}
			}
			else{
				printf("\nACCOUNT ID or PIN doesn't match");
				getch();
				continue;
			}
			
		

			
		}
		else if(strcmp(inputId, "EXIT") == 0){
			loginFlag = FALSE;
		}
		else{ 
			printf("\n:::::Account doesn't exist!!:::::");
			getch();
		}

		fwrite(account, sizeof(acctDet), PLIMIT, acdb);

	}while(loginFlag == TRUE);
	
	
	
	

	free(account);
	free(inputId);
	fclose(acdb);
	return 0;
}
	

