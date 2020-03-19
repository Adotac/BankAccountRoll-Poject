#include "BA_header.h"


int main(void){
<<<<<<< HEAD

	char acctId[CHARLIMIT];
	int i=0;// IDENTIFIES THE TYPE OF SAVINGS
=======
	srand(time(NULL));
	int choice = 1;
	int key = UPARROW;
	acctDet *account;
	account = (acctDet*)calloc(sizeof(acctDet), PLIMIT);
	//*account = InitializeAcct();
>>>>>>> efa6f1f... UI DEVELOPED

	do {
		system("cls");
<<<<<<< HEAD
		printf("\n\tNo account yet? Type REGISTER to create an account.");
		printf("\n\n\tAccount ID: ");
		gets_s(acctId);
		toupper(acctId[CHARLIMIT]);
	} while (strcmp(acctId, "REGISTER") != 0);
=======
		printf("\n\t===================== WELCOME TO THE BANK! ======================");
		key = getch();
		switch (choice) {
		case 1:printf("\n\t|                                                               |\n");
			printf("\t|                          ");
			textHighllght("LOG IN");
			printf("                               | \n");

			printf("\t|     ");
			printf("No account yet? Type REGISTER to create an account.");
			printf("\t| ");
			printf("\n\t|                                                               |");
			printf("\n\t|                           ");
			printf("EXIT");
			printf("\t\t\t\t| ");
			printf("\n\t=================================================================");
			break;
		case 2:printf("\n\t|                                                               |\n");
			printf("\t|                          ");
			printf("LOG IN");
			printf("                               | \n");

			printf("\t|     ");
			textHighllght("No account yet? Type REGISTER to create an account.");
			printf("\t| ");
			printf("\n\t|                                                               |");
			printf("\n\t|                           ");
			printf("EXIT");
			printf("\t\t\t\t| ");
			printf("\n\t=================================================================");
			break;
		case 3:
			printf("\n\t|                                                               |\n");
			printf("\t|                          ");
			printf("LOG IN");
			printf("                               | \n");

			printf("\t|     ");
			printf("No account yet? Type REGISTER to create an account.");
			printf("\t| ");
			printf("\n\t|                                                               |");
			printf("\n\t|                           ");
			textHighllght("EXIT");
			printf("\t\t\t\t| ");
			printf("\n\t=================================================================");
			break;
		}
		switch (key) {
		case UPARROW:
			choice--;
			if (choice < 1)
				choice = 1;
			break;
		case DNARROW:
			choice++;
			if (choice > 4)
				choice = 3;
			break;
		}
	} while (key != ENTER);
	if (choice == 3)
		return 0;
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
				printf("\n:::::ACCOUNT ID or PIN doesn't match:::::");
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
	
	
	
>>>>>>> efa6f1f... UI DEVELOPED
	

	i = accountTypeReg(i);

_getch();
return 0;
}