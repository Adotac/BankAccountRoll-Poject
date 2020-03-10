#include "BA_header.h"


int main(void){
	srand(time(NULL));

	acctDet *account;
	account = (acctDet*)calloc(sizeof(acctDet), PLIMIT);
	int loginFlag = TRUE, regType, pinInput;;
	
	char *inputId;
	inputId = (char*)calloc(sizeof(char), CHARLIMIT);
	
	//temporary account dont delete
	strcpy(account[0].acctID, "ADMIN");
	account[0].balance_history[0] = 50000;
	strcpy(account[0].branch[0], "basak");
	strcpy(account[0].date[0], __DATE__);
	

	do {//main loop
		fflush(stdout);
		system("cls");
		
		printf("\n\tNo account yet? Type REGISTER to create an account.");
		printf("\n\n\tAccount ID: ");
		gets_s(inputId, CHARLIMIT);
		upperSentence(inputId);

		if( strcmp(inputId, "REGISTER") == 0){
			regType = accountTypeReg(); // dont delete, important!
			

			//dire ang flow sa 1-4
		}
		else if(IdChecker(inputId, account) == TRUE){
			
			//ari na ang pin input
			//if(pinChecker(inputId, pinInput, account) == TRUE){
				//ari na sulod tanan after login
			//}
			displaySavings(account, inputId);
		

			//loginFlag = FALSE;
		}
		else{ 
			printf("\n:::::Account doesn't exist!!:::::");
			getch();
		}

		

	}while(loginFlag == TRUE);
	
	
	
	

	free(account);
	free(inputId);
	///////////////////////////Reserve this line for a function dont delete
	//account[0].balance_history[0] = 50000;
	//strcpy(account[0].branch[0], "basak");
	//strcpy(account[0].date[0], __DATE__);
	//acctHistory(account, 0);
	getch();
	return 0;
}
	

