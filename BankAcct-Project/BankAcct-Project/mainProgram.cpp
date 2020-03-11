#include "BA_header.h"


int main(void){
	srand(time(NULL));

	acctDet *account;
	account = (acctDet*)calloc(sizeof(acctDet), PLIMIT);
	//*account = InitializeAcct();

	int loginFlag = TRUE, pinInput = NULL, a_index = NULL;
	
	char *inputId;
	inputId = (char*)calloc(sizeof(char), CHARLIMIT);
	
	//temporary account dont delete
	strcpy(account[0].acctID, "ADMIN");
	account[0].type = TIME;
	account[0].savingType.balance_history[0] = 50000;
	strcpy(account[0].savingType.branch[0], "basak");
	strcpy(account[0].savingType.date[0], __DATE__);
	

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

		

	}while(loginFlag == TRUE);
	
	
	
	

	free(account);
	free(inputId);
	return 0;
}
	

